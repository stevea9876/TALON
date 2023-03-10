#ifndef __IRIDIUMCOMMS__
#define __IRIDIUMCOMMS__
#include <Arduino.h>
#include <IridiumSBD.h>
#include "CommsBase.h"
#include "ConfigurationInformation.h"
#include "SBDInformation.h"

#define IRIDIUM_BAUD        19200
#define IRIDIUM_PIN_TX      21
#define IRIDIUM_PIN_RX      22

class IridiumComms : public CommsBase
{
public:
    IridiumComms(ConfigurationInformation& _configuration, SBDInformation& _sbdInformation, IridiumSBD& _modem); 
    int begin();

    static void thread(void* parameter);

private:
    IridiumSBD& modem;
};
#endif // __IRIDIUMCOMMS__
