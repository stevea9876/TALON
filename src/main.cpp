#include <Arduino.h>
#include <WiFi.h>
#include <crypto.h>
#include <SparkFun_Ublox_Arduino_Library.h> //http://librarymanager/All#SparkFun_Ublox_GPS

#include "OTAUpdate.h"
#include "ConfigurationInformation.h"
#include "IridiumComms.h"

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial
#define IridiumSerial Serial2

#define STACK_SIZE 4096
#define DEFAULT_PRIORITY 9
#define DEFAULT_CORE 1

ConfigurationInformation configuration;
SBDInformation sbdInformation;
IridiumSBD modem(IridiumSerial);
IridiumComms iridium(configuration, sbdInformation, modem);
OTAUpdate UpdateServer(configuration, sbdInformation);
// Declare the GPS object
SFE_UBLOX_GPS GPS;

void setup() {
  SerialMon.begin(115200);
  IridiumSerial.begin(19200, SERIAL_8N1, 47, 48);

  byte error, address;
  int nDevices;
  Serial.println("Scanning...");
  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknow error at address 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
  {
    Serial.println("No I2C devices found\n");
  }
  else
  {
    Serial.println("done\n");
  }
  delay(5000);

  // Serial.println(F("Connecting to the GPS receiver..."));
  // if (GPS.begin() == false) // Connect to the Ublox module using Wire port
  // {
  //   Serial.println(F("Ublox GPS not detected at default I2C address. Please check wiring. Freezing."));
  //   while (1)
  //     ;
  // }
  // Load configuration information
  configuration.Load();

  SerialMon.println(F("Starting Update Server Thread"));
  xTaskCreatePinnedToCore(UpdateServer.thread, "Update Server Thread", STACK_SIZE, (void *)&UpdateServer, DEFAULT_PRIORITY, UpdateServer.getTaskPtr(), DEFAULT_CORE);
  SerialMon.println(F("Starting Iridium Thread"));
  xTaskCreatePinnedToCore(iridium.thread, "Iridium Thread", STACK_SIZE, (void *)&iridium, DEFAULT_PRIORITY, iridium.getTaskPtr(), DEFAULT_CORE);
}

void loop() {
  // put your main code here, to run repeatedly:
}