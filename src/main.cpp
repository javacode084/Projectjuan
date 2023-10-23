#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RTCHandler.h>
#include <SolarTracker.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219a(0x40);
Adafruit_INA219 ina219b(0x41);
RTC rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C(0x27) LCD dan Jenis LCD (20x4)

#define SOIL A7
#define POMPA A15

// RTC & pompa Variable
DateTime now;
const DateTime m_start = DateTime(2000, 1, 1, 17, 0, 0); ///< time when relay turn on
const DateTime m_stop = DateTime(2000, 1, 1, 17, 30, 0); ///< time when relay turn off
bool isPompa = false;
int soil;

// INA Sensor variable
float shuntvoltage1;
float busvoltage1;
float current_mA1;
float power_mW1;
float shuntvoltage2;
float busvoltage2;
float current_mA2;
float power_mW2;

void solarTracker();
void displayHandler();
void jadwalSiram();
void ina219aRead();
void ina219bRead();
void setup()
{
    Serial.begin(115200);
    lcd.init();       // instruksi untuk memulai LCD
    lcd.begin(20, 4); // instruksi untuk menggunakan lcd 20x4
    lcd.backlight();  // instruksi untuk mengaktifkan lampu latar LCD

    rtc.begin();
    ina219a.begin();
    ina219b.begin();

    pinMode(POMPA, OUTPUT);
    pinMode(SOIL, INPUT);

    Serial.println("Measuring voltage and current with INA219 ...");
}

unsigned long millisDisplay = 0;
unsigned long millisRTC = 0;
void loop()
{
    if (millis() - millisDisplay > 1000) // update display tiap 1000ms
    {
        millisDisplay = millis();
        displayHandler();
    }

    jadwalSiram();
    solarTracker();
    ina219aRead();
    ina219bRead();
}

void ina219aRead()
{
    shuntvoltage1 = ina219a.getShuntVoltage_mV();
    busvoltage1 = ina219a.getBusVoltage_V();
    current_mA1 = ina219a.getCurrent_mA();
    power_mW1 = ina219a.getPower_mW();
}
void ina219bRead()
{
    shuntvoltage2 = ina219b.getShuntVoltage_mV();
    busvoltage2 = ina219b.getBusVoltage_V();
    current_mA2 = ina219b.getCurrent_mA();
    power_mW2 = ina219b.getPower_mW();
}
void displayHandler()
{
    // Hari, jam
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(rtc.daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.setCursor(7, 0);
    lcd.print("Jam:");
    lcd.setCursor(11, 0);
    lcd.print(now.hour(), DEC);
    lcd.setCursor(13, 0);
    lcd.print(":");
    lcd.setCursor(14, 0);
    lcd.print(now.minute(), DEC);
    lcd.setCursor(16, 0);
    lcd.print(":");
    lcd.setCursor(17, 0);
    lcd.print(now.second(), DEC);

    // Kondisi Tanah
    lcd.setCursor(0, 1);
    soil > 400 ? lcd.print("Tanah Kering") : lcd.print("Tanah Basah");
    lcd.setCursor(13, 1);
    lcd.print("Pompa:");
    lcd.print(isPompa);

    // INA 1
    lcd.setCursor(0, 2);
    lcd.print("V:");
    lcd.setCursor(2, 2);
    lcd.print(busvoltage1, 2);
    lcd.setCursor(6, 2);
    lcd.print("I:");
    lcd.setCursor(8, 2);
    lcd.print(current_mA1 / 1000, 1);
    lcd.setCursor(13, 2);
    lcd.print("W:");
    lcd.setCursor(15, 2);
    lcd.print(power_mW1 / 1000, 1);

    // INA 2
    lcd.setCursor(0, 3);
    lcd.print("V:");
    lcd.setCursor(2, 3);
    lcd.print(busvoltage2, 2);
    lcd.setCursor(6, 3);
    lcd.print("I:");
    lcd.setCursor(8, 3);
    lcd.print(current_mA2 / 1000, 1);
    lcd.setCursor(13, 3);
    lcd.print("W:");
    lcd.setCursor(15, 3);
    lcd.print(power_mW2 / 1000, 1);
}

void jadwalSiram()
{
    soil = analogRead(SOIL);

    if (millis() - millisRTC > 1000) // update time now tiap 1000ms
    {
        now = rtc.now();
        millisRTC = millis();

        // calculate a date which is 7 days, 12 hours, 30 minutes, 6 seconds into the future
        DateTime future(now + TimeSpan(7, 12, 30, 6));

        if (rtc.is_in_range(now, m_start, m_stop))
        {
            if (soil >= 400) // Pompa hanya menyala jika keadaan tanah kering
            {
                digitalWrite(POMPA, LOW);
                isPompa = true;
            }
            else
            {
                digitalWrite(POMPA, HIGH);
                isPompa = false;
            }
        }
        else if (!rtc.is_in_range(now, m_start, m_stop))
        {
            digitalWrite(POMPA, HIGH);
            isPompa = false;
        }
    }
}
