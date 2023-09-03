#include <Arduino.h>
#include "RTClib.h"

struct RTC
{
    RTC_DS3231 *Rtc = new RTC_DS3231;
    const uint8_t m_min_in_h = 60; ///< minutes in an hour
    char daysOfTheWeek[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

    bool begin();

    uint16_t min_calculate(const DateTime &time);

    bool is_in_range(const DateTime &current, const DateTime &start, const DateTime &end);

    void readjam();

    DateTime now();
};

bool RTC::begin()
{
    if (!Rtc->begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1)
            delay(10);
    }

    if (Rtc->lostPower())
    {
        Serial.println("RTC lost power, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        Rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    // When time needs to be re-set on a previously configured device, the
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    return true;
}

uint16_t RTC::min_calculate(const DateTime &time)
{
    uint16_t time_minute = time.hour() * m_min_in_h;
    time_minute += time.minute();
    return time_minute;
}

bool RTC::is_in_range(const DateTime &current, const DateTime &start, const DateTime &end)
{
    auto current_minute = min_calculate(current);
    auto start_minute = min_calculate(start);
    auto end_minute = min_calculate(end);
    return ((current_minute >= start_minute) && (current_minute < end_minute));
}

DateTime RTC::now()
{
    return Rtc->now();
}