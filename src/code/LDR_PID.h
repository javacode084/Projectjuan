#include <Arduino.h>
#include <Wire.h>
#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Alamat I2C(0x27) LCD dan Jenis LCD (20x4)

// INPUT PIN
#define LDR1 A1 
#define LDR2 A2 
#define LDR3 A3 
#define LDR4 A4 
//Timur= A1+A2 TOP Vertikal
//Barat= A3+A4 BOTTOM
//Utara= A1+A3 LEFT Horizontal
//Selatan= A2+A4 RIGHT

// OUTPUT PIN
#define PWMR1 2
#define PWMR2 3

#define PWMR3 4
#define PWMR4 5


int ldr1,ldr2,ldr3,ldr4; //nilai pembacaaan LDr
int difVer,difHor; //rata-rata nilai untuk error

// int pwm1,pwm2,pwm3,pwm4; //nilai pwm motor


float Kp = 10;
float Ki = 1;
float Kd = 1;
float error1 = 0, P1 = 0, I1 = 0, D1 = 0, PID_value1 = 0;
float previous_error1 = 0, previous_I1 = 0;
float error2 = 0, P2 = 0, I2 = 0, D2 = 0, PID_value2 = 0;
float previous_error2 = 0, previous_I2 = 0;


void mbarat () {
// barat
analogWrite(PWMR1, 255);
analogWrite(PWMR2, 0);
}

void mtimur () {
// timur
analogWrite(PWMR1, 0);
analogWrite(PWMR2, 255);
}

void mutara () {
// utara
analogWrite(PWMR3, 0);
analogWrite(PWMR4, 255);
}

void mselatan () {
// selatan
analogWrite(PWMR3, 255);
analogWrite(PWMR4, 0);
}

void mstop1 () {
  //stop motor timur barat
  analogWrite(PWMR1, 0);
  analogWrite(PWMR1, 0);
}

void mstop2 () {
  //stop utara selatan
  analogWrite(PWMR2, 0);
  analogWrite(PWMR2, 0);
}


void bacaLDR()
{
ldr1=analogRead(LDR1);
ldr2=analogRead(LDR2);
ldr3=analogRead(LDR3);
ldr4=analogRead(LDR4);

    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("LDR1:");
    lcd.setCursor(6,1);
    lcd.print(ldr1);
    lcd.setCursor(10,1);
    lcd.print("LDR2:");
    lcd.setCursor(16,1);
    lcd.print(ldr2);
    // delay(2000);
    lcd.setCursor(0,2);  
    lcd.print("LDR3:");
    lcd.setCursor(6,2);
    lcd.print(ldr3);
    lcd.setCursor(10,2);
    lcd.print("LDR4:");
    lcd.setCursor(16,2);
    lcd.print(ldr4);
    delay(2000);
    
    Serial.print("nilai LDR 1: ");Serial.print(ldr1);
    Serial.print("nilai LDR 2: ");Serial.println(ldr2); 
    Serial.print("nilai LDR 3: ");Serial.print(ldr3);
    Serial.print("nilai LDR 4: ");Serial.println(ldr4); 
    
    int avgTop = (ldr1 + ldr2) / 2;
    int avgBot = (ldr3 + ldr4) / 2;
    int avgLeft = (ldr1 + ldr3) / 2;
    int avgRight = (ldr2 + ldr4) / 2;

    difVer = avgTop - avgBot;
    difHor = avgRight - avgLeft;

}

void calculatePID()
{ // Motor1
  error1 = difHor;
  P1 = error1;
  I1 = I1 + previous_I1;
  D1 = error1 - previous_error1;

  PID_value1 = (Kp * P1) + (Ki * I1) + (Kd * D1);

  previous_I1 = I1;
  previous_error1 = error1;

  // Motor2
  error2 = difVer;
  P2 = error2;
  I2 = I2 + previous_I2;
  D2 = error2 - previous_error2;

  PID_value2 = (Kp * P2) + (Ki * I2) + (Kd * D2);

  previous_I2 = I2;
  previous_error2 = error2;
}



void setup()
{
Serial.begin(115200);
lcd.init();
lcd.backlight();
}

void loop()
{
bacaLDR();
Serial.print(difVer);
Serial.println(difHor);
calculatePID(); 
Serial.print(PID_value1 );
Serial.println(PID_value2);

}

