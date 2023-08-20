#include <Arduino.h>
#include <Wire.h>              // Memanggil library wire.h
#include <LiquidCrystal_I2C.h> // Memanggil library LCD dengan I2C
LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C(0x27) LCD dan Jenis LCD (20x4)
#define LDRU A2                 // Deklarasi LDR pada pin A0
#define LDRS A3

// pembacaan LDR
int nilaildru;
int nilaildrs;

// nilai LDR
int U=500;
int S=500;



int PWMR2 = 9;//utara
int PWML2 = 8;//selatan


void utara () {
// utara
analogWrite(PWMR2, 0);
analogWrite(PWML2, 255);
}

void selatan () {
// selatan
analogWrite(PWMR2, 255);
analogWrite(PWML2, 0);
}

void stop () {
  //stop
  analogWrite(PWMR2, 0);
  analogWrite(PWMR2, 0);
}

void bacaLDR()
{
nilaildru=analogRead(LDRU);
nilaildrs=analogRead(LDRS);

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
  pinMode(LDRU,INPUT);
  pinMode(LDRS,INPUT);
  pinMode(PWMR2, OUTPUT);
  pinMode(PWML2, OUTPUT);
}
void loop() {
    bacaLDR();  
    lcd.clear();
    lcd.setCursor(0,2);
    lcd.print("Utara");
    lcd.setCursor(11,2);
    lcd.print("Selatan");
    lcd.setCursor(0,3);
    lcd.print("NA: "); 
    lcd.print(nilaildru);
    lcd.setCursor(11,3);
    lcd.print("NA: "); 
    lcd.print(nilaildrs);

    delay(1000);
    
    Serial.print("nilai LDR Utara: ");Serial.print(nilaildru);
    Serial.print("nilai LDR Selatan: ");Serial.println(nilaildrs); 
    
    if (nilaildru>=U)
    {
        selatan();
    }
    else if (nilaildrs>=S)
    {
        utara();
    }
    else if (nilaildru>U && nilaildrs>S)
    {
        stop();
    }
    else 
    {
        stop();
    }
} 