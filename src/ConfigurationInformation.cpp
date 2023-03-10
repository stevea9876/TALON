#include "ConfigurationInformation.h"

#include <Arduino.h>
#include <EEPROM.h>

struct ConfigurationStructure
{
    byte configurationInitialised;
    uint32_t updateRate;
    int webserverPort;
    byte apnLength;
    char APN[64];
    byte usernameLength;
    char Username[64];
    byte passwordLength;
    char Password[64];
    byte pinLength;
    char PIN[4];
    byte ivLength;
    char IV[16];
    byte keyLength;
    char Key[64];
    byte wifissidLength;
    char WIFISSID[64];
    byte wifipasswordLength;
    char WIFIPassword[64];
    byte ipaddressLength;
    char IPAddress[15];
    byte ipsubnetLength;
    char IPSubnet[15];
    byte ipgatewayLength;
    char IPGateway[15];
} CONFIGURATION_STRUCTURE;

void ConfigurationInformation::Load()
{
    // Read configuration information from EEPROM
    ConfigurationStructure config;
    memset(&config, 0, sizeof(ConfigurationStructure));
    EEPROM.begin(sizeof(ConfigurationStructure));
    EEPROM.get(0, config);
    if (config.configurationInitialised != CONFIGURATION_INITIALISED)
    {
        config.configurationInitialised = CONFIGURATION_INITIALISED;
        config.updateRate = TRANSMIT_FREQUENCY[(int)UPDATE_RATE::TFMins10];
        EEPROM.put(0, config);
        EEPROM.commit();
        Serial.println("Configuration Initialised.");
    }
    Serial.print("Update Rate:");
    Serial.println(config.updateRate);
}
