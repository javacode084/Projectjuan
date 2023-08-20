#include <Arduino.h>
#include <Wire.h>
// pin Arduino to BTS7960
// motor X(TImur-Barat)
int PWMR1 = 6;//barat
int PWML1 = 7;//timur

void barat () {
// barat
analogWrite(PWMR1, 255);
analogWrite(PWML1, 0);
}

void timur () {
// timur
analogWrite(PWMR1, 0);
analogWrite(PWML1, 255);
}

void stop () {
  //stop
  analogWrite(PWMR1, 0);
  analogWrite(PWMR1, 0);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PWMR1, OUTPUT);
  pinMode(PWML1, OUTPUT);

}

void loop() {
  // arah posisi pergerakan mengikuti pembacaan LCD dan RTC





}




