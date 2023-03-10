#ifndef __SBDMESSAGES__
#define __SBDMESSAGES__

#include <Arduino.h>

#define MAX_TEXT_MESSAGE_SIZE 321
#define MAX_NAME_SIZE 42

typedef struct SBDHeaderWord1 {   // This word is never encrypted.  If encryption is used only SBDHeaderWord2 onwards are encrypted.
    byte SoftwareVersion : 6;
    byte ManualReport : 1;
    byte Encrypted : 1;
} SBD_HEADER_WORD1;

typedef struct SBDHeaderWord2 {
    byte AdditionalData : 5;
    byte PositionPresent : 1;
    byte ShortReport : 1;
    byte AlertFlag : 1;
} SBD_HEADER_WORD2;

typedef struct Report16Byte {
    SBD_HEADER_WORD1 Word1; // Word 0
    SBD_HEADER_WORD2 Word2; // Word 1

    // Words 2 to 5
    uint32_t Latitude : 23;
    uint32_t Course : 9;

    // Words 6 to 9
    uint32_t Longitude : 24;
    uint32_t SecondsToMidnightLSB : 8;

    // Words 10 to 13
    uint32_t SecondsToMidnightMSB : 9;
    uint32_t Battery : 7;
    uint32_t Speed : 9;
    uint32_t SpeedResolution : 1;
    uint32_t AltitudeLSB : 6;

    // Words 14 and 15
    uint16_t AltitudeMSB : 6;
    uint16_t AltitudeResolition : 1;
    uint16_t DayOfYear : 9;
} REPORT_16_BYTE;

typedef struct Report10Byte {
    SBD_HEADER_WORD1 Word1; // Word 0
    SBD_HEADER_WORD2 Word2; // Word 1

    // Words 2 to 5
    uint32_t Latitude : 20;
    uint32_t LatitudeLSB : 12;

    // Words 6 to 9
    uint32_t LongitudeMSB : 9;
    uint32_t SecondsToMidnight : 17;
    uint32_t Battery : 6;
} REPORT_10_BYTE;

typedef struct Report7Byte {
    SBD_HEADER_WORD1 Word1; // Word 0
    SBD_HEADER_WORD2 Word2; // Word 1

    // Words 2 to 5
    uint32_t Battery : 7;
    uint32_t SecondsToMidnight : 17;
    uint32_t DayOfYearLSB : 8;

    // Word 6
    uint8_t DayOfYearMSB : 1;
    uint8_t Spare : 7;
} REPORT_7_BYTE;

typedef struct TextMessage {   // Additional Data type 1
    // byte 0
    byte Encodeing : 2;
    byte Spare : 5;
    byte Acknowledge : 1;

    // bytes 1 to 322
    byte Message[MAX_TEXT_MESSAGE_SIZE];
} TEXT_MESSAGE;

typedef struct DelteMessage {   // Additional Data type 2
    // byte 0
    byte BurstTiming : 4;
    byte Spare : 4;
} DELTA_MESSAGE;

typedef struct DelteMessageBlockType {
    // byte 1
    union {
        struct {
            byte HorizontalBlockSize : 2;
            byte Spare : 6;
        };
        byte NoFix; // Value will always be 0xFF
    };
} DELTA_MESSAGE_BLOCK_TYPE;

typedef struct DelteMessageHorizontal2 {
    uint16_t HorizontalBlockSize : 2;
    uint16_t Latitude : 11;
    uint16_t Longitude : 11;

} DELTA_MESSAGE_HORIZONTAL2;

typedef struct DelteMessageHorizontal4 {
    uint32_t HorizontalBlockSize : 2;
    uint32_t Latitude : 15;
    uint32_t Longitude : 15;
} DELTA_MESSAGE_HORIZONTAL4;

typedef struct DelteMessageHorizontal6 {
    uint32_t HorizontalBlockSize : 2;
    uint32_t Latitude : 23;
    uint32_t LongitudeLSB : 7;

    uint16_t LongitudeMSB;
} DELTA_MESSAGE_HORIZONTAL6;

typedef struct DelteMessageVertical1 {
    uint8_t VerticalBlockSize : 1;
    uint8_t Altitude : 7;
} DELTA_MESSAGE_VERTICAL1;

typedef struct DelteMessageVertical2 {
    uint16_t VerticalBlockSize : 1;
    uint16_t Altitude : 15;
} DELTA_MESSAGE_VERTICAL2;

typedef struct iBeaconMessage {   // Additional Data type 3
    uint16_t Major;
    uint16_t Minor;
} DELTA_MESSAGE;

typedef struct WBGTValidity {
    uint8_t WetTemperatureValid : 1;
    uint8_t DryTemperatureValid : 1;
    uint8_t GlobeTemperatureValid : 1;
    uint8_t WBGTIOAValid : 1;
    uint8_t HumidityValid : 1;
    uint8_t HeatValid : 1;
    uint8_t FlowValid : 1;
    uint8_t WBGTInformationPresent : 1;
} WBGT_VALIDITY;

typedef struct WBGTInformation {   // Additional Data type 9
    WBGT_VALIDITY WBGT;
    int16_t WetTemperature;
    int16_t DryTemperature;
    int16_t GlobeTemperature;
    int16_t WBGTiTemperature;
    int16_t WBGToTemperature;
    int16_t Humidity;
    int16_t WBGTAverageTemperature;
    int16_t Heat;
    int16_t Flow;
    uint8_t Battery;
} WBGT_INFORMATION;

typedef struct HumanAcknowledgement {   // Additional Data type 10
    uint16_t ID;
} HUMAN_ACKNOWLEDGEMENT;

typedef struct AutoAcknowledgement {   // Additional Data type 11
    uint16_t ID;
} AUTO_ACKNOWLEDGEMENT;

typedef struct ConfigurationType {
    uint8_t ElementID : 4;
    uint8_t Spare : 4;
} CONFIGURATION_TYPE;

typedef struct TrackingSettings {  // Configuration Element ID 1
    uint32_t ElementID : 4;
    uint32_t RequestPosition : 1;
    uint32_t Tracking : 2;
    uint32_t TransmitFrequency : 5;
    uint32_t BurstFix : 4;
    uint32_t BurstTransmissionFrequency : 4;
    uint32_t DistressTransmitFrequency : 5;
    uint32_t DistressBurstFix : 4;
    uint32_t DistressBurstTransmitFrequencyLSB : 3;

    uint8_t DistressBurstTransmitFrequencyMSB : 1;
    uint8_t SignalLossChecking : 2;
    uint8_t Spare : 5;
} TRACKING_SETTINGS;

typedef struct MailboxSettings {  // Configuration Element ID 2
    uint16_t ElementID : 4;
    uint16_t MailboxCheckFrequency : 4;
    uint16_t Check : 2;
    uint16_t Spare : 6;
} MAILBOX_SETTINGS;

typedef struct BluetoothSettings {  // Configuration Element ID 3
    uint16_t ElementID : 4;
    uint16_t Status : 3;
    uint16_t Spare : 1;
    uint16_t BeaconID : 8;
    uint8_t BLWRaw : 2;
    uint8_t ScannerSensitivity : 3;
    uint8_t Spare : 3;
} BLUETOOTH_SETTINGS;

typedef struct SystemSettings {  // Configuration Element ID 4
    uint16_t ElementID : 4;
    uint16_t LoggingMode : 3;
    uint16_t FactoryReset : 1;
    uint16_t ClearMessageStore : 1;
    uint16_t DeleteLogFile : 1;
    uint16_t Spare : 5;
    uint16_t Deactivate : 1;
} SYSTEM_SETTINGS;

typedef struct GPSSettings {  // Configuration Element ID 5
    uint16_t ElementID : 4;
    uint16_t GPSHot : 2;
    uint16_t GPSMode : 2;
    uint16_t FixesRequired : 3;
    uint16_t EarlyWakeup : 3;
    uint16_t Spare : 2;
} GPS_SETTINGS;

typedef struct ScreenLockSettings {  // Configuration Element ID 6
    uint8_t ElementID : 4;
    uint8_t ScreenLock : 2;
    uint8_t Spare : 2;
    uint16_t PIN;
} SCREEN_LOCK_SETTINGS;

typedef struct GPSLoggingSettings {  // Configuration Element ID 7
    uint16_t ElementID : 4;
    uint16_t NewSegment : 1;
    uint16_t ClearFile : 1;
    uint16_t GPSLogging : 2;
    uint16_t GPSLoggingPeriod : 7;
    uint16_t Spare : 1;
} GPS_LOGGING_SETTINGS;

typedef struct UserCustomisationSettings {  // Configuration Element ID 8
    uint8_t ElementID : 4;
    uint8_t Spare : 4;
    uint8_t Name[MAX_NAME_SIZE];
} USER_CUSTOMISATION_SETTINGS;

typedef struct FactorySettings {  // Configuration Element ID 9
    uint8_t ElementID : 4;
    uint8_t Spare : 4;
    uint16_t SerialNumber;
} FACTORY_SETTINGS;

typedef struct ConfigurationReport {
    SBD_HEADER_WORD1 Word1; // Word 0
    SBD_HEADER_WORD2 Word2; // Word 1

    union {
        CONFIGURATION_TYPE Type;
        TRACKING_SETTINGS Tracking;  // Configuration Element ID 1
        MAILBOX_SETTINGS Mailbox;  // Configuration Element ID 2
        BLUETOOTH_SETTINGS Bluetooth;  // Configuration Element ID 3
        SYSTEM_SETTINGS System;  // Configuration Element ID 4
        GPS_SETTINGS GPS;  // Configuration Element ID 5
        SCREEN_LOCK_SETTINGS ScreenLock;  // Configuration Element ID 6
        GPS_LOGGING_SETTINGS GPSLogging;  // Configuration Element ID 7
        USER_CUSTOMISATION_SETTINGS UserCustomisation;  // Configuration Element ID 8
        FACTORY_SETTINGS Factory;  // Configuration Element ID 9
    };
} CONFIGURATION_REPORT;

#endif // __SBDMESSAGES__
