#include <Arduino.h>
#include <Wire.h>              // Memanggil library wire.h
#include <LiquidCrystal_I2C.h> // Memanggil library LCD dengan I2C
LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C(0x27) LCD dan Jenis LCD (20x4)
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
void readjam()
{
  DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

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

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");

    Serial.println();
    delay(3000);
}

void setup () {
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
// #ifndef ESP8266
//   while (!Serial); // wait for serial port to connect. Needed for native USB
// #endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
}

void loop () {
    readjam();
}
