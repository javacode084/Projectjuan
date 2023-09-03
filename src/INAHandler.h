#include <Arduino.h>
#include <Adafruit_INA219.h>

struct INA219
{
    uint8_t addr;
    float shuntvoltage;
    float busvoltage;
    float current_mA;
    float power_mW;
    Adafruit_INA219 *ina219 = new Adafruit_INA219(addr);

    INA219(uint8_t _addr = 0x40)
    {
        addr = _addr;
    } // constructor

    bool begin();
    void read();
    void serialprint();
};

bool INA219::begin()
{
    ina219->begin();
    return true;
}

void INA219::read()
{
    shuntvoltage = ina219->getShuntVoltage_mV();
    busvoltage = ina219->getBusVoltage_V();
    current_mA = ina219->getCurrent_mA();
    power_mW = ina219->getPower_mW();
}

void INA219::serialprint()
{
    Serial.print("Bus Voltage :   ");
    Serial.print(busvoltage);
    Serial.println(" V");
    Serial.print("Shunt Voltage : ");
    Serial.print(shuntvoltage);
    Serial.println(" mV");
    Serial.print("Current 1:       ");
    Serial.print(current_mA);
    Serial.println(" mA");
    Serial.print("Power 1:         ");
    Serial.print(power_mW);
    Serial.println(" mW");
}