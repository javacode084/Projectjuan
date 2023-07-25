#include <Arduino.h>
#include <Wire.h>              // Memanggil library wire.h
#include <LiquidCrystal_I2C.h> // Memanggil library LCD dengan I2C
LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C(0x27) LCD dan Jenis LCD (20x4)
#define LDR A0                 // Deklarasi LDR pada pin A0
int nilai;

void bacaLDR()
{
nilai=analogRead(LDR);
}


void setup() {
  Serial.begin(9600);     // Baud komunikasi serial pada 9600
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
  pinMode(LDR,INPUT);
}
void loop() {
    bacaLDR();  
    lcd.clear();
    lcd.setCursor(6,2);
    lcd.print("Baca LDR");
    lcd.setCursor(0,3);
    lcd.print("Nilai Analog: "); 
    lcd.print(nilai);
    delay(1000);
    
    Serial.print("nilai LDR: ");Serial.println(nilai);   
} 