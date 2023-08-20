// https://duwiarsana.com/membuat-penyiram-tanaman-otomatis/
#include<Wire.h>
#include<Arduino.h>

#include <LiquidCrystal_I2C.h> // Memanggil library LCD dengan I2C
LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C(0x27) LCD dan Jenis LCD (20x4)
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"
#include <SPI.h>

RTC_DS3231 rtc;
int pompa = A9; //NO relay ke pompa

const DateTime m_start = DateTime(2000, 1, 1, 19, 58, 0); ///< time when realy turn on
const DateTime m_stop = DateTime(2000, 1, 1, 20, 05, 0); ///< time when realy turn off
const int r_output_pin = A8; ///< com pin connected relay to relay
const uint8_t m_min_in_h = 60; ///< minutes in an hour
const unsigned long m_refresh_time_ms = 1000; ///< time of repeting check time is in range and sending message
char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
uint16_t min_calculate(const DateTime& time)
{
  uint16_t time_minute = time.hour() * m_min_in_h;
  time_minute += time.minute();
  return time_minute;
}
bool is_in_range(const DateTime& current, const DateTime& start, const DateTime& end)
{
  auto current_minute = min_calculate(current);
  auto start_minute = min_calculate(start);
  auto end_minute = min_calculate(end);
  return ((current_minute >= start_minute) && (current_minute < end_minute));
}

void readjam()
{
  static unsigned long last_loop_time = 0;
  unsigned long loop_time = millis();
  if (loop_time - last_loop_time > m_refresh_time_ms)
  {
    DateTime now = rtc.now();
    Serial.print(now.hour(), DEC);
    Serial.print(":");
    Serial.print(now.minute(), DEC);
    Serial.print(":");
    Serial.println(now.second(), DEC);
    last_loop_time = millis();
    
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.setCursor(0,1);
    lcd.print("Jam:");
    lcd.setCursor(5,1);
    lcd.print(now.hour(), DEC); 
    lcd.setCursor(7,1);
    lcd.print(":"); 
    lcd.setCursor(8,1);
    lcd.print(now.minute(), DEC);
    lcd.setCursor(10,1);
    lcd.print(":");
    lcd.setCursor(11,1);
    lcd.print(now.second(), DEC);
    // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
    DateTime future (now + TimeSpan(7,12,30,6));
    
    static bool is_turn_on = true;
    if (is_in_range(now, m_start, m_stop) && !is_turn_on)
    {
      Serial.println("Start");
      lcd.clear();lcd.setCursor(0,3);lcd.print("Pompa On");
      digitalWrite(r_output_pin, LOW);
      is_turn_on = true;
    }
    else if (!is_in_range(now, m_start, m_stop) && is_turn_on)
    {
      Serial.println("Stop");
      lcd.clear();lcd.setCursor(0,3);lcd.print("Pompa Off");
      digitalWrite(r_output_pin, HIGH);
      is_turn_on = false;
    }
  }  
}


void readsoil()
{
int soil =analogRead(A7);
delay(2000);
Serial.println(soil);

if(soil<=250)
{
  digitalWrite(pompa,LOW);
// onsiram
}
else{
  digitalWrite(pompa,HIGH);
  // offsiram
}
}



void setup() {
  // put your setup code here, to run once:
// Serial.begin(9600);
Serial.begin(57600);
  lcd.init();             // instruksi untuk memulai LCD
  lcd.begin(20,4);        // instruksi untuk menggunakan lcd 20x4
  lcd.backlight();        // instruksi untuk mengaktifkan lampu latar LCD
  lcd.setCursor(3,0);
  lcd.print("Hello, world!");
  lcd.setCursor(4,1);
  lcd.print("TEST PROJECT");
  lcd.setCursor(3,2);
  lcd.print("Project Juan");
  lcd.setCursor(3,3);
  lcd.print("SOLAR TRACKER");
  delay(500);
if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 pinMode(r_output_pin, OUTPUT);
 pinMode(pompa, OUTPUT);
// pinMode(pompa,OUTPUT);
}

void loop() {
  unsigned long waktusekarang1=millis(); //task SensorINA219B
  unsigned long waktusebelumnya1=0;

  if(waktusekarang1-waktusebelumnya1>0)
{
    readjam();
    readsoil();
    waktusebelumnya1=waktusekarang1;
}      
  
}