#include <Arduino.h>
#include "code/maintask.h"
#include "main_app.h"
// #include "code/LDR_PID.h"
// #include "code/LDR.h"
// #include "code/LDR_MOTOR.h"
// #include "code/LDR_MOTOR2.h"
// #include "code/rtc.h"
// #include "code/lcd.h"
// #include "code/bts7960.h"
// #include "code/ina219multi.h"
// #include "code/maintes.h"
// #include "code/ina219a.h" 
// #include "code/ina219b.h"
// #include "code/soilRTC.h"

//GABUNGAN:
// 1. Pembacaan LDR timur,barat,selatan,utara dengan PID kontrol
// 2. Pembacaan sensor tegangan dan arus untuk pompa_SensorA(0x40)
// 3. Setting Pompa sesuai RTC dan kelembaban tanah
//    Jadwal On: 17.00 selama 30 menit(On progress)
// 4. Kontrol driver motor:
//    (timur dan barat)(selatan dan utara)
//