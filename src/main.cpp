#include <Arduino.h>
#include <FS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <ArduinoOTA.h>

#include <Bedienfeld.h>
#include <Daten.h>
#include <Temperatursensoren.h>
#include <SerOut.h>

const char* ssid     = "Schragen2.4";
const char* password = "warpdrive";
const char* host = "esp32";
AsyncWebServer server(80);

Daten Steuerungsdaten();
SerOut Ausgabe();
Temperatursensoren Sensoren();

void setup() 
{
  Serial.begin(115200); 
  // Connect to Wi-Fi network with SSID and password
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
  /*use mdns for host name resolution*/
  if (!MDNS.begin(host)) 
  { //http://esp32.local
    Serial.println("Error setting up MDNS responder!");
    while (1) 
    {
      delay(1000);
    }
  };
  Serial.println("mDNS responder started");

  
  //ArduinoOTA.setPort(3232);
  //ArduinoOTA.setPassword("admin");
  //ArduinoOTA.setHostname(host);
  //ArduinoOTA.begin();
  //Setup_Bedienfeld ();
};

void loop() 
{
    ArduinoOTA.handle();
}