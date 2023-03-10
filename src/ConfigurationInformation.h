#ifndef __CONFIGURATIONINFORMATION__
#define __CONFIGURATIONINFORMATION__
#include <Arduino.h>

#define CONFIGURATION_INITIALISED 0xA5

static const int TRANSMIT_FREQUENCY[] = { 10, 300, 600, 900, 1200, 1800, 3600, 5400, 7200, 10800, 14400, 21600, 28800, 43200, 600, 60, 120, 180, 240, 86400, 360, 480, 720, 15, 30 };
static const int DEFAULT_WEBSERVER_PORT = 80;
static const String DEFAULT_APN = "three.co.uk";
static const String DEFAULT_USERNAME = "";
static const String DEFAULT_PASSWORD = "";
static const String DEFAULT_PIN = "";
static const String DEFAULT_IV = "";
static const String DEFAULT_KEY = "";
static const String DEFAULT_WIFISSID = "WBGT";
static const String DEFAULT_WIFIPASSWORD = "12345678";
static const String DEFAULT_IP = "10.10.42.1";
static const String DEFAULT_SUBNET = "255.255.255.240";
static const String DEFAULT_GATEWAY = "10.10.42.1";

class ConfigurationInformation
{
public:
    enum UPDATE_RATE { TFContinuous = 0, TFMins5 = 1, TFMins10 = 2 , TFMins15 = 3, TFMins20 = 4, TFMins30 = 5, TFMins60 = 6, TFMins90 = 7, TFMins120 = 8,
                        TFMins180 = 9, TFMins240 = 10, TFMins360 = 11, TFMins480 = 12, TFMins720 = 13, TFBurst = 14, TFMin1 = 15, TFMin2 = 16, TFMin3 = 17,
                        TFMin4 = 18, TFHours24 = 19, TFMin6 = 20, TFMin8 = 21, TFMin12 = 22, TFSeconds15 = 23, TFSeconds30 = 24 };

    ConfigurationInformation()
    {
        Init();
    };

    void Init()
    {
        initialised = false;
        updateRate = UPDATE_RATE::TFMins10;
        APN = DEFAULT_APN;
        Username = DEFAULT_USERNAME;
        Password = DEFAULT_PASSWORD;
        PIN = DEFAULT_PIN;
        IV = DEFAULT_IV;
        Key = DEFAULT_KEY;
        WIFISSID = DEFAULT_WIFISSID;
        WIFIPassword = DEFAULT_WIFIPASSWORD;
        webserverPort = DEFAULT_WEBSERVER_PORT;
        IPAddress = DEFAULT_IP;
        IPSubnet = DEFAULT_SUBNET;
        IPGateway = DEFAULT_GATEWAY;
    };

    void Load();

    bool getInitialised() { return initialised; }
    int getUpdateRate() { return (int)updateRate; }
    int getWebserverPort() { return webserverPort; }
    String getAPN() { return APN; };
    String getUsername() { return Username; }
    String getPassword() { return Password; }
    String getPIN() { return PIN; }
    String getIV() { return IV; }
    String getKey() { return Key; }
    String getWIFISSID() { return WIFISSID; }
    String getWIFIPassword() { return WIFIPassword; }
    String getIPAddress() { return IPAddress; }
    String getIPSubnet() { return IPSubnet; }
    String getIPGateway() { return IPGateway; }

    void setInitialised(bool _initialised) { initialised = _initialised; };
    void setUpdateRate(int _updateRate) { updateRate = (UPDATE_RATE)_updateRate; }
    void setWebserverPort(int _webserverPort) { webserverPort = _webserverPort; }
    void setAPN(String _APN) { APN = _APN; };
    void setUsername(String _Username) { Username = _Username; };
    void setPassword(String _Password) { Password = _Password; };
    void setPIN(String _PIN) { PIN = _PIN; };
    void setIV(String _IV) { IV = _IV; };
    void setKey(String _Key) { Key = _Key; };
    void setWIFISSID(String _WIFISSID) { WIFISSID = _WIFISSID; };
    void setWIFIPassword(String _WIFIPassword) { WIFIPassword = _WIFIPassword; };
    void setIPAddress(String _IPAddress) { IPAddress = _IPAddress; };
    void setIPSubnet(String _IPSubnet) { IPSubnet = _IPSubnet; };
    void setIPGateway(String _IPGateway) { IPGateway = _IPGateway; };

private:
    bool initialised;
    UPDATE_RATE updateRate;
    int webserverPort;
    String APN;
    String Username;
    String Password;
    String PIN;
    String IV;
    String Key;
    String WIFISSID;
    String WIFIPassword;
    String IPAddress;
    String IPSubnet;
    String IPGateway;

    bool Tracking;
    int TrackingTransmitFrequency;
    int TrackingBrstFix;
    int TrackingBurstFixTransmission;
    int TrackingDistressTransmitFrequency;
    int TrackingDistressBrstFix;
    int TrackingDistressBurstFixTransmission;
    bool TrackingSignalLossChecking;
    int MailboxCheckFrequency;
    bool MailboxCheck;
    int BluetoothStatus;
    int BLuetoothBeaconID;
    bool BluetoothRaw;
    int BluetoothScannerSensitivity;
    int SystemLoggingMode;
    bool SystemFactoryReset;
    bool SystemClearMessageStore;
    bool SystemDeleteLogFile;
    bool SystemDeactivate;
    bool GPSHot;
    int GPSMode;
    int GPSRequiredFixes;
    int GPSEarlyWakeup;
    bool ScreenLock;
    bool ScreenPIN;
    bool GPSLoggingNewSegment;
    bool GPSLoggingClearFile;
    bool GPSLogging;
    int GPSLoggingPeriod;
    String UserCustomisation;
    int FactorySerialNumber;
};

#endif // __CONFIGURATIONINFORMATION__