#include "OTAUpdate.h"
#include <Update.h>

/*
 * Login page
 */

const char* loginIndex =
 "<form name='loginForm'>"
    "<table width='20%' bgcolor='A09F9F' align='center'>"
        "<tr>"
            "<td colspan=2>"
                "<center><font size=4><b>ESP32 Login Page</b></font></center>"
                "<br>"
            "</td>"
            "<br>"
            "<br>"
        "</tr>"
        "<tr>"
             "<td>Username:</td>"
             "<td><input type='text' size=25 name='userid'><br></td>"
        "</tr>"
        "<br>"
        "<br>"
        "<tr>"
            "<td>Password:</td>"
            "<td><input type='Password' size=25 name='pwd'><br></td>"
            "<br>"
            "<br>"
        "</tr>"
        "<tr>"
            "<td><input type='submit' onclick='check(this.form)' value='Login'></td>"
        "</tr>"
    "</table>"
"</form>"
"<script>"
    "function check(form)"
    "{"
    "if(form.userid.value=='admin' && form.pwd.value=='admin')"
    "{"
    "window.open('/serverIndex')"
    "}"
    "else"
    "{"
    " alert('Error Password or Username')/*displays error message*/"
    "}"
    "}"
"</script>";

/*
 * Server Index Page
 */

const char* serverIndex =
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
   "<input type='file' name='update'>"
        "<input type='submit' value='Update'>"
    "</form>"
 "<div id='prg'>progress: 0%</div>"
 "<script>"
  "$('form').submit(function(e){"
  "e.preventDefault();"
  "var form = $('#upload_form')[0];"
  "var data = new FormData(form);"
  " $.ajax({"
  "url: '/update',"
  "type: 'POST',"
  "data: data,"
  "contentType: false,"
  "processData:false,"
  "xhr: function() {"
  "var xhr = new window.XMLHttpRequest();"
  "xhr.upload.addEventListener('progress', function(evt) {"
  "if (evt.lengthComputable) {"
  "var per = evt.loaded / evt.total;"
  "$('#prg').html('progress: ' + Math.round(per*100) + '%');"
  "}"
  "}, false);"
  "return xhr;"
  "},"
  "success:function(d, s) {"
  "console.log('success!')"
 "},"
 "error: function (a, b, c) {"
 "}"
 "});"
 "});"
 "</script>";

static WebServer* sOTAServer = NULL;

OTAUpdate::OTAUpdate(ConfigurationInformation& _configuration, SBDInformation _sbdInformation) :
    CommsBase(_configuration, _sbdInformation),
    OTAServer(configuration.getWebserverPort())
{
    sOTAServer = &OTAServer;
}

OTAUpdate::~OTAUpdate()
{
    sOTAServer = NULL;
}

// Configure the AP
void OTAUpdate::ConfigureWifi()
{
    /* Put IP Address details */
    LocalIP.fromString(configuration.getIPAddress());
    Gateway.fromString(configuration.getIPGateway());
    Subnet.fromString(configuration.getIPSubnet());

    // Create Wifi access point
    SSID = configuration.getWIFISSID();
    Password = configuration.getWIFIPassword();
    WiFi.softAP(SSID.c_str(), Password.c_str());
    WiFi.softAPConfig(LocalIP, Gateway, Subnet);
    delay(100);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.print(IP);
    Serial.print("/");
    Serial.println(WiFi.softAPSubnetCIDR());
}

// Configure the update server
void OTAUpdate::ConfigureServerResponse()
{
    /*return index page which is stored in serverIndex */
    OTAServer.on("/", HTTP_GET, []()
    {
        if (sOTAServer != NULL)
        {
            sOTAServer->sendHeader("Connection", "close");
            sOTAServer->send(200, "text/html", loginIndex);
        } 
    });
    OTAServer.on("/serverIndex", HTTP_GET, []()
    {
        if (sOTAServer != NULL)
        {
            sOTAServer->sendHeader("Connection", "close");
            sOTAServer->send(200, "text/html", serverIndex); 
        }
    });
    // Allow reboot
    OTAServer.on("/reboot", HTTP_GET, []()
    {
        if (sOTAServer != NULL)
        {
            sOTAServer->sendHeader("Connection", "close");
            sOTAServer->send(200, "text/html", loginIndex);
        }
        Serial.println("Remote reboot");
        ESP.restart();
    });
    /*handling uploading firmware file */
    OTAServer.on("/update", HTTP_POST, []()
    {
        if (sOTAServer != NULL)
        {
            sOTAServer->sendHeader("Connection", "close");
            sOTAServer->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
            ESP.restart();
        }
    }, []()
    {
        if (sOTAServer != NULL)
        {
            HTTPUpload &upload = sOTAServer->upload();
            if (upload.status == UPLOAD_FILE_START)
            {
                Serial.printf("Update: %s\n", upload.filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN))
                { // start with max available size
                    Update.printError(Serial);
                }
            }
            else if (upload.status == UPLOAD_FILE_WRITE)
            {
                /* flashing firmware to ESP*/
                if (Update.write(upload.buf, upload.currentSize) != upload.currentSize)
                {
                    Update.printError(Serial);
                }
            }
            else if (upload.status == UPLOAD_FILE_END)
            {
                if (Update.end(true))
                { // true to set the size to the current progress
                    Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
                }
                else
                {
                    Update.printError(Serial);
                }
            }
        }
    });
}

void OTAUpdate::begin(uint16_t port)
{
    ConfigureWifi();
    ConfigureServerResponse();
    OTAServer.begin(port);
}

void OTAUpdate::handleClient()
{
    OTAServer.handleClient();
}

void OTAUpdate::thread(void* parameter)
{
    OTAUpdate& UpdateServer = *((OTAUpdate *)parameter);

    UpdateServer.begin();

    while (true)
    {
        UpdateServer.handleClient();
        // taskYIELD();
    }
}
