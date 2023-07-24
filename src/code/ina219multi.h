#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219a;
Adafruit_INA219 ina219b (0x44);
Adafruit_INA219 ina219c (0x41);

void read_219a()
{
  float shuntvoltage1 = 0;
  float busvoltage1 = 0;
  float current_mA1 = 0;
  float loadvoltage1 = 0;
  float power_mW1 = 0;

  shuntvoltage1 = ina219a.getShuntVoltage_mV();
  busvoltage1 = ina219a.getBusVoltage_V();
  current_mA1 = ina219a.getCurrent_mA();
  power_mW1 = ina219a.getPower_mW();
  loadvoltage1 = busvoltage1 + (shuntvoltage1 / 1000);
  
  Serial.print("Bus Voltage 1:   "); Serial.print(busvoltage1); Serial.println(" V");
  Serial.print("Shunt Voltage 1: "); Serial.print(shuntvoltage1); Serial.println(" mV");
  Serial.print("Load Voltage 1:  "); Serial.print(loadvoltage1); Serial.println(" V");
  Serial.print("Current 1:       "); Serial.print(current_mA1); Serial.println(" mA");
  Serial.print("Power 1:         "); Serial.print(power_mW1); Serial.println(" mW");
  Serial.println("");

  delay(2000);
}

void read_219b()
{
  float shuntvoltage2 = 0;
  float busvoltage2 = 0;
  float current_mA2 = 0;
  float loadvoltage2 = 0;
  float power_mW2 = 0;

  shuntvoltage2 = ina219b.getShuntVoltage_mV();
  busvoltage2 = ina219b.getBusVoltage_V();
  current_mA2 = ina219b.getCurrent_mA();
  power_mW2 = ina219b.getPower_mW();
  loadvoltage2 = busvoltage2 + (shuntvoltage2 / 1000);
  
  Serial.print("Bus Voltage 2:   "); Serial.print(busvoltage2); Serial.println(" V");
  Serial.print("Shunt Voltage 2: "); Serial.print(shuntvoltage2); Serial.println(" mV");
  Serial.print("Load Voltage 2:  "); Serial.print(loadvoltage2); Serial.println(" V");
  Serial.print("Current 2:       "); Serial.print(current_mA2); Serial.println(" mA");
  Serial.print("Power 2:         "); Serial.print(power_mW2); Serial.println(" mW");
  Serial.println("");

  delay(2000);
}

void read_219c()
{
  float shuntvoltage3 = 0;
  float busvoltage3 = 0;
  float current_mA3 = 0;
  float loadvoltage3 = 0;
  float power_mW3 = 0;

  shuntvoltage3 = ina219c.getShuntVoltage_mV();
  busvoltage3 = ina219c.getBusVoltage_V();
  current_mA3 = ina219c.getCurrent_mA();
  power_mW3 = ina219c.getPower_mW();
  loadvoltage3 = busvoltage3 + (shuntvoltage3 / 1000);
  
  Serial.print("Bus Voltage 3:   "); Serial.print(busvoltage3); Serial.println(" V");
  Serial.print("Shunt Voltage 3: "); Serial.print(shuntvoltage3); Serial.println(" mV");
  Serial.print("Load Voltage 3:  "); Serial.print(loadvoltage3); Serial.println(" V");
  Serial.print("Current 3:       "); Serial.print(current_mA3); Serial.println(" mA");
  Serial.print("Power 3:         "); Serial.print(power_mW3); Serial.println(" mW");
  Serial.println("");

  delay(2000);
}


void setup(void) 
{
  Serial.begin(115200);
  while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
  }

  // uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219a.begin();
  ina219b.begin();
  ina219c.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  Serial.println("Measuring voltage and current with INA219 ...");
}

void loop() 
{
read_219a();
read_219b();
read_219c();  
}
