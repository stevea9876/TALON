#include "SBDInformation.h"

const uint32_t ROCKSTAR_NO_LATITUDE = 4194304;
const uint32_t ROCKSTAR_NO_LONGITUDE = 8388608;
const uint32_t ROCKSTAR_OFFSET_LATITUDE = 8388607;
const uint32_t ROCKSTAR_OFFSET_LONGITUDE = 16777215;
const double ROCKSTAR_LATITUDE_SCALING = 90.0 / ROCKSTAR_NO_LATITUDE;
const double ROCKSTAR_LONGITUDE_SCALING = 180.0 / ROCKSTAR_NO_LONGITUDE;

byte messageGPSFix[] = { 0x06, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte messageNoGPSFix[] = { 0x06, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte wbgtInformation[] = { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
byte wbgtBluetoothInformation[] = { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const uint32_t daysInMonths[] = { 31, 0, 31, 0, 31, 0, 31, 0, 30, 0, 30, 0 };

SBDInformation::SBDInformation()
{
    mutex = xSemaphoreCreateMutex();
    valid = false;
    timeValid = false;
    messageUpdateRate = SECONDS_IN_10MINUTES;
    Init();
}

void SBDInformation::Init()
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    lastValidFix = 0;
    Battery = 0;
    BatterySensor = 0;
    secondsSinceMidnight = 0;
    secondsSinceMidnightOffset = 0;
    latitude = 0;
    longitude = 0;
    speed = 0;
    altitude = 0;
    course = 0;
    WBGTValidity = WBGT_DATA_PRESENT;
    WT = 0;
    DT = 0;
    GT = 0;
    WBGTi = 0;
    WBGTo = 0;
    WBGTA = 0;
    humidity = 0;
    Heat = 0;
    flow = 0;

    // Release the mutex
    xSemaphoreGive(mutex);
}


void SBDInformation::setValid(bool _valid)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    valid = _valid;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setTimeValid(bool _timeValid)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    timeValid = _timeValid;
    
    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setLastValidFix(uint32_t _lastValidFix)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    lastValidFix = _lastValidFix;
    
    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setBattery(uint8_t _Battery)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

   Battery =_Battery;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setBatterySensor(uint16_t _BatterySensor)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    BatterySensor = _BatterySensor;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setSecondsSinceMidnight(uint32_t _secondsSinceMidnight)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    secondsSinceMidnight = _secondsSinceMidnight;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setTime(int hour, int minute, int second)
{
    uint32_t currentTime = (hour * SECONDS_IN_HOUR) + (minute * SECONDS_IN_MINUTE) + second;

    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    timeValid = true;
    secondsSinceMidnight = currentTime;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setSecondsSinceMidnightOffset(uint32_t _secondsSinceMidnightOffset)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    secondsSinceMidnightOffset = _secondsSinceMidnightOffset;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setLatitude(float _latitude)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    latitude = _latitude;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setLongitude(float _longitude)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    longitude = _longitude;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setSpeed(float _speed)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    speed = _speed;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setAltitude(float _altitude)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    altitude = _altitude;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setCourse(float _course)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    course = _course;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setDay(int _month, int _day)
{
    int epochMonth = _month % 2;

    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    day = epochMonth == 0 ? _day : daysInMonths[_month - 1] + _day;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setPositionAndTime(float _latitude, float _longitude, float _speed, float _altitude, float _course, int _month, int _day, int _hour, int _minute, int _second, uint32_t _lastValidFix)
{
    uint32_t currentTime = (_hour * SECONDS_IN_HOUR) + (_minute * SECONDS_IN_MINUTE) + _second;
    int epochMonth = _month % 2;

    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    timeValid = true;
    secondsSinceMidnight = currentTime;
    latitude = _latitude;
    longitude = _longitude;
    speed = _speed;
    altitude = _altitude;
    course = _course;
    day = epochMonth == 0 ? _day : daysInMonths[_month - 1] + _day;
    lastValidFix = _lastValidFix;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setWBGTValidity(uint8_t _WBGTValidity)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    WBGTValidity = _WBGTValidity;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setWT(uint16_t _WT)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    WT = _WT;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setDT(uint16_t _DT)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    DT = _DT;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setGT(uint16_t _GT)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    GT = _GT;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setWBGTi(uint16_t _WBGTi)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    WBGTi = _WBGTi;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setWBGTo(uint16_t _WBGTo)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    WBGTo = _WBGTo;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setWBGTA(uint16_t _WBGTA)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    WBGTA = _WBGTA;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setHumidity(uint16_t _humidity)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    humidity = _humidity;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setHeat(uint16_t _Heat)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    Heat = _Heat;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setFlow(uint16_t _flow)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    flow = _flow;

    // Release the mutex
    xSemaphoreGive(mutex);
}

void SBDInformation::setMessageUpdateRate(uint32_t _messageUpdateRate)
{
    // Take the mutex
    xSemaphoreTake(mutex, portMAX_DELAY);

    messageUpdateRate = _messageUpdateRate;

    // Release the mutex
    xSemaphoreGive(mutex);
}

byte* SBDInformation::PackSBDMessage(int &packetSize)
{
    wbgtInformation[0] = 0xFF;
    wbgtInformation[1] = (byte)WBGTValidity;
    wbgtInformation[2] = (byte)(WT >> 8);
    wbgtInformation[3] = (byte)(WT & 0x00FF);
    wbgtInformation[4] = (byte)(DT >> 8);
    wbgtInformation[5] = (byte)(DT & 0x00FF);
    wbgtInformation[6] = (byte)(GT >> 8);
    wbgtInformation[7] = (byte)(GT & 0x00FF);
    wbgtInformation[8] = (byte)(WBGTi >> 8);
    wbgtInformation[9] = (byte)(WBGTi & 0x00FF);
    wbgtInformation[10] = (byte)(WBGTo >> 8);
    wbgtInformation[11] = (byte)(WBGTo & 0x00FF);
    wbgtInformation[12] = (byte)(humidity >> 8);
    wbgtInformation[13] = (byte)(humidity & 0x00FF);
    wbgtInformation[14] = (byte)(WBGTA >> 8);
    wbgtInformation[15] = (byte)(WBGTA & 0x00FF);
    wbgtInformation[16] = (byte)(Heat >> 8);
    wbgtInformation[17] = (byte)(Heat & 0x00FF);
    wbgtInformation[18] = (byte)(flow >> 8);
    wbgtInformation[19] = (byte)(flow & 0x00FF);
    wbgtInformation[20] = (byte)(Battery);
    byte* message = &messageGPSFix[0];
    int size = sizeof(messageGPSFix);
    if (valid && ((millis() - lastValidFix) < MILLISECONDS_IN_MINUTE))
    {
        uint32_t latitude = (uint32_t)(latitude / ROCKSTAR_LATITUDE_SCALING);
        if (latitude < 0.0)
        {
            latitude = (uint32_t)((latitude / ROCKSTAR_LATITUDE_SCALING) + ROCKSTAR_OFFSET_LATITUDE);
        }
        uint32_t longitude = (uint32_t)(longitude / ROCKSTAR_LONGITUDE_SCALING);
        if (longitude < 0.0)
        {
            longitude = (uint32_t)((longitude / ROCKSTAR_LONGITUDE_SCALING) + ROCKSTAR_OFFSET_LONGITUDE);
        }
        uint32_t course = (uint32_t)min((int)course, 360);
        messageGPSFix[2] = (byte)((latitude >> 15) & 0xFF);
        messageGPSFix[3] = (byte)((latitude >> 7) & 0xFF);
        messageGPSFix[4] = (byte)((latitude & 0x7F) << 1);
        messageGPSFix[4] = (byte)(messageGPSFix[4] | ((course >> 8) & 0x01));
        messageGPSFix[5] = (byte)(course & 0xFF);
        messageGPSFix[6] = (byte)((longitude >> 16) & 0xFF);
        messageGPSFix[7] = (byte)((longitude >> 8) & 0xFF);
        messageGPSFix[8] = (byte)(longitude & 0xFF);
        uint32_t time = (uint32_t)min((int)secondsSinceMidnight, 86399);
        messageGPSFix[9] = (byte)((time >> 9) & 0xFF);
        messageGPSFix[10] = (byte)((time >> 1) & 0xFF);
        messageGPSFix[11] = (byte)((time & 0x01) << 7);
        messageGPSFix[11] = (byte)(messageGPSFix[11] | (Battery & 0x7F));
        uint32_t speed = (uint32_t)(speed * 10);
        messageGPSFix[12] = (byte)(messageGPSFix[12] | 0x80);
        messageGPSFix[12] = (byte)(messageGPSFix[12] | ((speed >> 2) & 0x7F));
        messageGPSFix[13] = (byte)((speed & 0x03) << 6);
        uint32_t alt = (uint32_t)min((int)altitude, 16383);
        messageGPSFix[13] = (byte)(messageGPSFix[13] | ((alt >> 8) & 0x3F));
        messageGPSFix[14] = (byte)(alt & 0xFF);
    }
    else
    {
        messageNoGPSFix[2] = (byte)((Battery & 0x7F) << 1);
        float fahrenheit = (float)WBGTA / 100.0;
        float celcius = fahrenheit * 1.8 + 32;
        uint32_t temperature = round(celcius);
        messageNoGPSFix[2] |= (byte)((temperature >> 6) & 0x01);
        messageNoGPSFix[3] |= (byte)((temperature & 0x3F) << 2);
        messageNoGPSFix[3] |= (byte)((secondsSinceMidnight >> 15) & 0x03);
        messageNoGPSFix[4] = (byte)((secondsSinceMidnight >> 7) & 0xFF);
        messageNoGPSFix[5] = (byte)((secondsSinceMidnight & 0x7F) << 1);
        messageNoGPSFix[5] |= (byte)((day >> 5) & 0x01);
        messageNoGPSFix[6] = (byte)((day & 0x1F) << 3);
        message = &messageNoGPSFix[0];
        size = sizeof(messageNoGPSFix);
    }
    packetSize = size + sizeof(wbgtInformation);
    byte* sbdMessage = new byte[size];
    memcpy(sbdMessage, message, size);
    memcpy(&sbdMessage[size], &wbgtInformation[0], sizeof(wbgtInformation));
    return sbdMessage;
}

byte* SBDInformation::PackBluetoothMessage(int& packetSize)
{
    // WBGT Bluetooth information
    wbgtBluetoothInformation[0] = 0xFF;
    wbgtBluetoothInformation[1] = sizeof(wbgtBluetoothInformation);
    uint32_t time = secondsSinceMidnight; 
    wbgtBluetoothInformation[2] = (byte)((time >> 16) & 0xFF); 
    wbgtBluetoothInformation[2] = timeValid ? wbgtBluetoothInformation[2] | 0x80 : wbgtBluetoothInformation[2];
    wbgtBluetoothInformation[3] = (byte)((time >> 8) & 0xFF); 
    wbgtBluetoothInformation[4] = (byte)(time & 0xFF); 
    wbgtBluetoothInformation[5] = (byte)WBGTValidity;
    wbgtBluetoothInformation[6] = (byte)(WT >> 8);
    wbgtBluetoothInformation[7] = (byte)(WT & 0x00FF);
    wbgtBluetoothInformation[8] = (byte)(DT >> 8);
    wbgtBluetoothInformation[9] = (byte)(DT & 0x00FF);
    wbgtBluetoothInformation[10] = (byte)(GT >> 8);
    wbgtBluetoothInformation[11] = (byte)(GT & 0x00FF);
    wbgtBluetoothInformation[12] = (byte)(WBGTi >> 8);
    wbgtBluetoothInformation[13] = (byte)(WBGTi & 0x00FF);
    wbgtBluetoothInformation[14] = (byte)(WBGTo >> 8);
    wbgtBluetoothInformation[15] = (byte)(WBGTo & 0x00FF);
    wbgtBluetoothInformation[16] = (byte)(humidity >> 8);
    wbgtBluetoothInformation[17] = (byte)(humidity & 0x00FF);
    wbgtBluetoothInformation[18] = (byte)(WBGTA >> 8);
    wbgtBluetoothInformation[19] = (byte)(WBGTA & 0x00FF);
    wbgtBluetoothInformation[20] = (byte)(Heat >> 8);
    wbgtBluetoothInformation[21] = (byte)(Heat & 0x00FF);
    wbgtBluetoothInformation[22] = (byte)(flow >> 8);
    wbgtBluetoothInformation[23] = (byte)(flow & 0x00FF);
    wbgtBluetoothInformation[24] = (byte)(Battery);

    packetSize = sizeof(wbgtBluetoothInformation);
    return &wbgtBluetoothInformation[0];
}
