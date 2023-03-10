#ifndef __OTAUPDATE__
#define __OTAUPDATE__

#include <Arduino.h>
#include <WebServer.h>
#include "CommsBase.h"

class OTAUpdate : public CommsBase
{
public:
    OTAUpdate(ConfigurationInformation& _configuration, SBDInformation _sbdInformation);
    virtual ~OTAUpdate();

    void ConfigureWifi();
    void ConfigureServerResponse();

    void begin(uint16_t port = DEFAULT_WEBSERVER_PORT);
    void handleClient();

    static void thread(void* parameter);

private:
    /* Put IP Address details */
    IPAddress LocalIP;
    IPAddress Gateway;
    IPAddress Subnet;

    String SSID;
    String Password;

    WebServer OTAServer;
};

#endif // __OTAUPDATE__