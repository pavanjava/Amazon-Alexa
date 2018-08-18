/**********************************************************************************
  Home Automation with Alexa and NodeMCU
  WeMos smart devices emulation using FAUXMOESP Library

  Code based on the great open source lib & example code at:
  http://tinkerman.cat/emulate-wemo-device-esp8266/
  which is based off of the Python example code by:
  https://github.com/makermusings/fauxmo

  Also, thanks to Sid for Sid's E Classroom
  https://www.youtube.com/c/SidsEClassroom

  fauxmoESP is a library for ESP8266-based devices that emulates a Belkin WeMo device
  and thus allows you to control them using this protocol, in particular from
  Alexa-powered devices like the Amazon Echo or the Dot.

  7 devices to be discovered:

   4 Simple WeMo devices
    ==> Light1    ==> Relay 1 ==> NodeMCU D5
    ==> Light2    ==> Relay 3 ==> NodeMCU D7
    ==> Outlet1   ==> Relay 2 ==> NodeMCU D6
    ==> Outlet2   ==> Relay 4 ==> NodeMCU D8

   3 Groups of devices
    ==> All Devices
    ==> Living Room (Light1 and Outlet1)
    ==> Bed Room (Light2 and Outlet2)

   To discovery devices for the first time, use voice commnad:
   "Computer (or Alexa), discovery devices"

   To activate a device or a gropu of devices, you should use voice commands, like:
   "Computer (or Alexa), turn on Light1" or "..., turn off Light1"
   "Computer (or Alexa), turn on Living Room" or "..., turn off Living Room"
   "Computer (or Alexa), turn on All Devices" or "..., turn off All Devices"

   Developed by Marcelo Rovai on 19Aug17
   Visit my blog: https://MJRoBot.org
  *********************************************************************************/
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include <SPI.h>

/* Network credentials */
#define WIFI_SSID "*********" // your WiFi SSID
#define WIFI_PASS "************" // your WiFi Password

/* Belkin WeMo emulation */
fauxmoESP fauxmo;

char buff_1[] = "TV ON\n";
char buff_2[] = "TV OFF\n";
char buff_3[] = "VOLUME UP\n";
char buff_4[] = "VOLUME DOWN\n";
char buff_5[] = "HOME\n";
char buff_6[] = "RIGHT\n";
char buff_7[] = "LEFT\n";
char buff_8[] = "DOWN\n";
char buff_9[] = "UP\n";
char buff_10[] = "ENTER\n";
char buff_11[] = "MUTE\n";

void setup()
{
  Serial.begin(9600);
  SPI.begin();

  //setup and wifi connection
  wifiSetup();

  // Device Names for Simulated Wemo switches
  fauxmo.addDevice("TV ON");
  fauxmo.addDevice("TV OFF");
  fauxmo.addDevice("VOLUME UP");
  fauxmo.addDevice("VOLUME DOWN");
  fauxmo.addDevice("HOME");
  fauxmo.addDevice("RIGHT");
  fauxmo.addDevice("LEFT");
  fauxmo.addDevice("DOWN");
  fauxmo.addDevice("UP");
  fauxmo.addDevice("ENTER");
  fauxmo.addDevice("MUTE");
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
  Serial.println(state);
  //Switching action on detection of device name

  if ( (strcmp(device_name, "TV ON") == 0) )
  {
    for (int i = 0; i < sizeof buff_1; i++) /* transfer buff data per second */
      SPI.transfer(buff_1[i]);
  }

  if ( (strcmp(device_name, "TV OFF") == 0) )
  {
    for (int i = 0; i < sizeof buff_2; i++) /* transfer buff data per second */
      SPI.transfer(buff_2[i]);
  }

  if ( (strcmp(device_name, "VOLUME UP") == 0) )
  {
    for (int i = 0; i < sizeof buff_3; i++) 
      SPI.transfer(buff_3[i]);
  }

  if ( (strcmp(device_name, "VOLUME DOWN") == 0) )
  {
    for (int i = 0; i < sizeof buff_4; i++) 
      SPI.transfer(buff_4[i]);
  }

  if ( (strcmp(device_name, "HOME") == 0) )
  {
    for (int i = 0; i < sizeof buff_5; i++) 
      SPI.transfer(buff_5[i]);
  }

   if ( (strcmp(device_name, "RIGHT") == 0) )
  {
    for (int i = 0; i < sizeof buff_6; i++) 
      SPI.transfer(buff_6[i]);
  }

   if ( (strcmp(device_name, "LEFT") == 0) )
  {
    for (int i = 0; i < sizeof buff_7; i++) 
      SPI.transfer(buff_7[i]);
  }

   if ( (strcmp(device_name, "DOWN") == 0) )
  {
    for (int i = 0; i < sizeof buff_8; i++) 
      SPI.transfer(buff_8[i]);
  }

  if ( (strcmp(device_name, "UP") == 0) )
  {
    for (int i = 0; i < sizeof buff_5; i++) 
      SPI.transfer(buff_9[i]);
  }

  if ( (strcmp(device_name, "ENTER") == 0) )
  {
    for (int i = 0; i < sizeof buff_10; i++) 
      SPI.transfer(buff_10[i]);
  }

  if ( (strcmp(device_name, "MUTE") == 0) )
  {
    for (int i = 0; i < sizeof buff_10; i++) 
      SPI.transfer(buff_11[i]);
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
