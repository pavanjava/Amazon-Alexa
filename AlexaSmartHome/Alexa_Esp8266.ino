/**********************************************************************************
* Home Automation with Alexa and NodeMCU
* WeMos smart devices emulation using FAUXMOESP Library
*
* Code based on the great open source lib & example code at: 
* http://tinkerman.cat/emulate-wemo-device-esp8266/
* which is based off of the Python example code by: 
* https://github.com/makermusings/fauxmo
* 
* Also, thanks to Sid for Sid's E Classroom
* https://www.youtube.com/c/SidsEClassroom
* 
* fauxmoESP is a library for ESP8266-based devices that emulates a Belkin WeMo device 
* and thus allows you to control them using this protocol, in particular from 
* Alexa-powered devices like the Amazon Echo or the Dot.
*  
* 7 devices to be discovered:
*  
*  4 Simple WeMo devices
*   ==> Light1    ==> Relay 1 ==> NodeMCU D5
*   ==> Light2    ==> Relay 3 ==> NodeMCU D7
*   ==> Outlet1   ==> Relay 2 ==> NodeMCU D6 
*   ==> Outlet2   ==> Relay 4 ==> NodeMCU D8
*  
*  3 Groups of devices
*   ==> All Devices 
*   ==> Living Room (Light1 and Outlet1)
*   ==> Bed Room (Light2 and Outlet2)
*   
*  To discovery devices for the first time, use voice commnad: 
*  "Computer (or Alexa), discovery devices"
*  
*  To activate a device or a gropu of devices, you should use voice commands, like: 
*  "Computer (or Alexa), turn on Light1" or "..., turn off Light1"
*  "Computer (or Alexa), turn on Living Room" or "..., turn off Living Room"
*  "Computer (or Alexa), turn on All Devices" or "..., turn off All Devices"
*
*  Developed by Marcelo Rovai on 19Aug17
*  Visit my blog: https://MJRoBot.org 
  *********************************************************************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"

/* Network credentials */
#define WIFI_SSID "" // your WiFi SSID
#define WIFI_PASS "" // your WiFi Password   

#define SERIAL_BAUDRATE 115200

/* Belkin WeMo emulation */
fauxmoESP fauxmo;

/* Set Relay Pins */
#define RELAY_1 D1
#define RELAY_2 D2

void setup() 
{
   Serial.begin(SERIAL_BAUDRATE);
   //setup and wifi connection
   wifiSetup();
 
   //Set relay pins to outputs
   pinMode(RELAY_1, OUTPUT);
   pinMode(RELAY_2, OUTPUT);

   //Set each relay pin to HIGH ====== NOTE THAT THE RELAYS USE INVERSE LOGIC =====
   digitalWrite(RELAY_1, LOW);   
   delay(500);
   digitalWrite(RELAY_2, LOW);  
   delay(500);
   
   // Device Names for Simulated Wemo switches
   fauxmo.addDevice("Light");
   fauxmo.addDevice("Fan");
   fauxmo.addDevice("All Devices");
   fauxmo.onMessage(callback); 
}

void loop() 
{
  fauxmo.handle();
}

/* ---------------------------------------------------------------------------
 Device Callback
 ----------------------------------------------------------------------------*/
void callback(uint8_t device_id, const char * device_name, bool state) 
{
  Serial.print("Device "); Serial.print(device_name); 
  Serial.print(" state: ");
  if (state) 
  {
    Serial.println("ON");
  } 
  else 
  {
    Serial.println("OFF");
  }
  
  //Switching action on detection of device name
  
  if ( (strcmp(device_name, "Light") == 0) ) 
  {
    if (!state) 
    {
      digitalWrite(RELAY_1, LOW);
    } 
    else 
    {
       digitalWrite(RELAY_1, HIGH);
    }
  }

  if ( (strcmp(device_name, "Fan") == 0) ) 
  {
    if (!state) 
    {
       digitalWrite(RELAY_2, LOW);
    } 
    else 
    {
      digitalWrite(RELAY_2, HIGH);
    }
  }
  
 
  if ( (strcmp(device_name, "All Devices") == 0) ) 
  {
    if (!state) 
    {
      digitalWrite(RELAY_1, LOW);
      digitalWrite(RELAY_2, LOW);
    } 
    else 
    {
      digitalWrite(RELAY_1, HIGH);
      digitalWrite(RELAY_2, HIGH);
    }
  }
}
    
/* -----------------------------------------------------------------------------
 Wifi Setup
 -----------------------------------------------------------------------------*/
void wifiSetup() 
{
   // Set WIFI module to STA mode
   WiFi.mode(WIFI_STA);

   // Connect
   Serial.println ();
   Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
   Serial.println();
   WiFi.begin(WIFI_SSID, WIFI_PASS);

   // Wait
   while (WiFi.status() != WL_CONNECTED) 
   {
      Serial.print(".");
      delay(100);
   }
   Serial.print(" ==> CONNECTED!" );
   Serial.println();

   // Connected!
   Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
   Serial.println();
}
