#ifndef __COMMSBASE__
#define __COMMSBASE__
#include <Arduino.h>
#include "SBDInformation.h"
#include "ConfigurationInformation.h"

class CommsBase
{
public:
    CommsBase(ConfigurationInformation& _configuration, SBDInformation& _sbdInformation) : configuration(_configuration), sbdInformation(_sbdInformation) {};

    TaskHandle_t* getTaskPtr() { return &taskHandle; };
    SBDInformation& getSBDInformation() { return sbdInformation; };
    ConfigurationInformation& getConfigurationInformation() { return configuration; };

protected:
    ConfigurationInformation& configuration;
    SBDInformation& sbdInformation;
    TaskHandle_t taskHandle;
};

#endif //__COMMSBASE__