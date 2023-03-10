#ifndef __SBDINFORMATION__
#define __SBDINFORMATION__
#include <Arduino.h>

#define MILLISECONDS_IN_SECOND 1000
#define MILLISECONDS_IN_2SECONDS 2000
#define MILLISECONDS_IN_10SECONDS 10000
#define MILLISECONDS_IN_MINUTE 60000
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_5MINUTES 300
#define SECONDS_IN_10MINUTES 600
#define SECONDS_IN_A_DAY 86400

class SBDInformation
{
public:
    SBDInformation();

    void Init();

    bool getValid() { return valid; }
    bool getTimeValid() { return timeValid; }
    uint8_t getBattery() { return Battery; }
    uint16_t getBatterySensor() { return BatterySensor; }
    uint32_t getSecondsSinceMidnight() { return secondsSinceMidnight; }
    uint32_t getSecondsSinceMidnightOffset() { return secondsSinceMidnightOffset; }
    float getLatitude() { return latitude; };
    float getLongitude() { return longitude; };
    float getSpeed() { return speed; };
    float getAltitude() { return altitude; };
    float getCourse() { return course; };
    int getDay() { return day; };
    uint8_t getWBGTValidity() { return WBGTValidity; }
    uint16_t getWT() { return WT; }
    uint16_t getDT() { return DT; }
    uint16_t getGT() { return GT; }
    uint16_t getWBGTi() { return WBGTi; }
    uint16_t getWBGTo() { return WBGTo; }
    uint16_t getWBGTA() { return WBGTA; }
    uint16_t getHumidity() { return humidity; };
    uint16_t getHeat() { return Heat; }
    uint16_t getFlow() { return flow; }
    uint32_t getMessageUpdateRate() { return messageUpdateRate; }

    void setValid(bool _valid);
    void setTimeValid(bool _timeValid);
    void setLastValidFix(uint32_t _lastValidFix);
    void setBattery(uint8_t _Battery);
    void setBatterySensor(uint16_t _BatterySensor);
    void setSecondsSinceMidnight(uint32_t _secondsSinceMidnight);
    void setTime(int hour, int minute, int second);
    void setSecondsSinceMidnightOffset(uint32_t _secondsSinceMidnightOffset);
    void setLatitude(float _latitude);
    void setLongitude(float _longitude);
    void setSpeed(float _speed);
    void setAltitude(float _altitude);
    void setCourse(float _course);
    void setDay(int _month, int _day);
    void setPositionAndTime(float _latitude, float _longitude, float _speed, float _altitude, float _course, int _month, int _day, int _hour, int _minute, int _second, uint32_t _lastValidFix);
    void setWBGTValidity(uint8_t _WBGTValidity);
    void setWT(uint16_t _WT);
    void setDT(uint16_t _DT);
    void setGT(uint16_t _GT);
    void setWBGTi(uint16_t _WBGTi);
    void setWBGTo(uint16_t _WBGTo);
    void setWBGTA(uint16_t _WBGTA);
    void setHumidity(uint16_t _humidity);
    void setHeat(uint16_t _Heat);
    void setFlow(uint16_t _flow);
    void setMessageUpdateRate(uint32_t _messageUpdateRate);

    byte* PackSBDMessage(int &packetSize);
    byte* PackBluetoothMessage(int &packetSize);

private:
    static const byte WBGT_DATA_PRESENT = 0x80;
    SemaphoreHandle_t mutex;

    bool valid;
    bool timeValid;
    uint32_t lastValidFix;

    uint32_t messageUpdateRate;
    uint8_t Battery;
    uint16_t BatterySensor;
    uint32_t secondsSinceMidnight;
    uint32_t secondsSinceMidnightOffset;
    float latitude;
    float longitude;
    float speed;
    float altitude;
    float course;
    int day;
    uint8_t WBGTValidity;
    uint16_t WT;
    uint16_t DT;
    uint16_t GT;
    uint16_t WBGTi;
    uint16_t WBGTo;
    uint16_t WBGTA;
    uint16_t humidity;
    uint16_t Heat;
    uint16_t flow;
};

#endif // __SBDINFORMATION__