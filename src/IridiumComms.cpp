#include <IridiumComms.h>

IridiumSBD* modemLocal = NULL;

IridiumComms::IridiumComms(ConfigurationInformation& _configuration, SBDInformation& _sbdInformation, IridiumSBD& _modem) :
    CommsBase(_configuration, _sbdInformation),
    modem(_modem)
{
    modemLocal = &modem;
}

int IridiumComms::begin()
{
    modem.setPowerProfile(IridiumSBD::USB_POWER_PROFILE);

    int status = modem.begin();
    if (status != ISBD_SUCCESS)
    {
        Serial.print("Couldn't begin modem operations. Error: ");
        Serial.println(status);
        return status;
    }
    
    // Check the signal quality (optional)
    int signalQuality = -1;
    int err = modem.getSignalQuality(signalQuality);
    if (err != 0)
    {
        Serial.print("SignalQuality failed: Error ");
        Serial.println(err);
        return ISBD_SERIAL_FAILURE;
    }

    Serial.print("Signal quality is ");
    Serial.println(signalQuality);
    return status;    
}

void IridiumComms::thread(void* parameter)
{
    IridiumComms& iridium = *((IridiumComms*)parameter);
    Serial.println("Running Iridium Thread");

    // Setup the Iridium modem
    int status = iridium.begin();

    uint32_t signalQualityCheck = 0;
    for(;;){
        if (status != ISBD_SUCCESS) {
            delay(MILLISECONDS_IN_MINUTE);
            status = iridium.begin();
        }
        else {
            uint32_t currentTime = millis();

            if ((currentTime - signalQualityCheck) >= MILLISECONDS_IN_10SECONDS)
            {
                int signalQuality = -1;
                int err = iridium.modem.getSignalQuality(signalQuality);
                if (err != 0)
                {
                    Serial.print("SignalQuality failed: error ");
                    Serial.println(err);
                }

                Serial.print("Signal quality is ");
                Serial.println(signalQuality);    
                signalQualityCheck = currentTime;

                struct tm time;
                err = iridium.modem.getSystemTime(time);
                if (err == 0)
                {
                    Serial.print("System Time:");
                    Serial.printf("%02d:%02d:%02d\n", time.tm_hour, time.tm_min, time.tm_sec);
                }
                else
                {
                    Serial.print("SystemTime failed: error ");
                    Serial.println(err);
                }
            }
        }
    }     
}

void ISBDConsoleCallback(IridiumSBD *device, char c)
{
    Serial.write(c);
}

void ISBDDiagsCallback(IridiumSBD *device, char c)
{
    Serial.write(c);
}

bool ISBDCallback()
{
    if (modemLocal != NULL)
    {

    }
    return true;
}
