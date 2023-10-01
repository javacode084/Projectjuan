#include <Arduino.h>

#define LDR1 A1
#define LDR2 A2
#define LDR3 A3
#define LDR4 A4
/*
Timur= A1+A2 TOP Vertikal
Barat= A3+A4 BOTTOM
Utara= A1+A3 LEFT Horizontal
Selatan= A2+A4 RIGHT
*/

#define PWMR1 2
#define PWMR2 3
#define PWMR3 4
#define PWMR4 5

// Solar Tracker Variable
int ldr1, ldr2, ldr3, ldr4; // nilai pembacaaan LDr
int difVer, difHor;         // rata-rata nilai untuk error
float Kp = 10;
float Ki = 1;
float Kd = 1;
float error1 = 0, P1 = 0, I1 = 0, D1 = 0, PID_value1 = 0;
float previous_error1 = 0, previous_I1 = 0;
float error2 = 0, P2 = 0, I2 = 0, D2 = 0, PID_value2 = 0;
float previous_error2 = 0, previous_I2 = 0;
int stopZone = 1700;

void mbarat()
{
    // barat
    analogWrite(PWMR1, 255);
    analogWrite(PWMR2, 0);
}

void mtimur()
{
    // timur
    analogWrite(PWMR1, 0);
    analogWrite(PWMR2, 255);
}

void mutara()
{
    // utara
    analogWrite(PWMR3, 0);
    analogWrite(PWMR4, 255);
}

void mselatan()
{
    // selatan
    analogWrite(PWMR3, 255);
    analogWrite(PWMR4, 0);
}

void mstop1()
{
    // stop motor timur barat
    analogWrite(PWMR1, 0);
    analogWrite(PWMR2, 0);
}

void mstop2()
{
    // stop utara selatan
    analogWrite(PWMR3, 0);
    analogWrite(PWMR4, 0);
}

void bacaLDR()
{
    ldr1 = analogRead(LDR1);
    ldr2 = analogRead(LDR2);
    ldr3 = analogRead(LDR3) - 110;
    ldr4 = analogRead(LDR4) - 120;

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
void solarTracker()
{
    bacaLDR();
    calculatePID();

    // Serial.print("LDR 1:");
    // Serial.print(ldr1);
    // Serial.print(" LDR 2:");
    // Serial.print(ldr2);
    // Serial.print(" LDR 3:");
    // Serial.print(ldr3);
    // Serial.print(" LDR 4:");
    // Serial.print(ldr4);
    // Serial.print(" PID1:");
    // Serial.print(PID_value1);
    // Serial.print(" PID2:");
    // Serial.println(PID_value2);

    if (PID_value1 > -stopZone && PID_value1 < stopZone)
    {
        mstop1();
    }
    else
    {
        if (PID_value1 > 0)
            mtimur();
        if (PID_value1 < 0)
            mbarat();
    }

    if (PID_value2 > -stopZone && PID_value2 < stopZone)
    {
        mstop2();
    }
    else
    {

        if (PID_value2 > 0)
            mselatan();
        if (PID_value2 < 0)
            mutara();
    }
}