#include <Arduino.h>
#include <Wire.h>
// pin Arduino to BTS7960
// motor X(TImur-Barat)
int PWMA1 = 6;
int PWMA2 = 7;
int ENA1 = 21;
int ENA2 = 23;
int R1   = 22;
int L1   = 24;


//motor Y(Utara_Selatan)
int PWMB1 = 8;
int PWMB2 = 9;
int ENB1 = 25;
int ENB2 = 27;
int R2   = 26;
int L2   = 28;


void setup() {
  // put your setup code here, to run once:
  pinMode(PWMA1, OUTPUT);
  pinMode(PWMA2, OUTPUT);
  pinMode(PWMB1, OUTPUT);
  pinMode(PWMB2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(ENA1, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(ENB1, OUTPUT);
  pinMode(ENB2, OUTPUT);


}

void loop() {
  // arah posisi pergerakan mengikuti pembacaan LCD dan RTC

}

void posMotor_timur()
{
  analogWrite(PWMA1, 100);
  analogWrite(PWMA2, 0);
  digitalWrite(ENA1,HIGH);
  digitalWrite(ENA2,HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(L1, LOW);
}

void posMotor_barat()
{
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 100);
  digitalWrite(ENA1,HIGH);
  digitalWrite(ENA2,HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(L1, HIGH);
}

void posMotor_utara()
{
  analogWrite(PWMB1, 100);
  analogWrite(PWMB2, 0);
  digitalWrite(ENB1,HIGH);
  digitalWrite(ENB2,HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(L2, LOW);
}

void posMotor_selatan()
{
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 100);
  digitalWrite(ENB1,HIGH);
  digitalWrite(ENB2,HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L2, HIGH);
}

