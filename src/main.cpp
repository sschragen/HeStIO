#include <Arduino.h>
#include <FS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <Update.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <Bedienfeld.h>
#include <Daten.h>
#include <Temperatursensoren.h>
#include <SerOut.h>

#include <TouchButton.h>

const char* host = "esp32";
const char* ssid = "Schragen2.4";               // your WiFi name
const char* password =  "warpdrive";            // your WiFi password
const char* mqttServer = "prodesk.fritz.box";   // Adresse vom MQTT Server
const int   mqttPort = 1883;                    // Port vom MQTT Server
const char* mqttUser = "TempLogger";            // MQTT Anmeldename
const char* mqttPassword = "none";              // MQTT Passwort
WiFiClient espClient;
PubSubClient MQTT(espClient);

AsyncWebServer server(80);

//Daten Steuerungsdaten();
//SerOut Ausgabe();
//Temperatursensoren Sensoren();
Bedienfeld *InOut;

void scanI2C ()
{
  #define SDA1 21
  #define SCL1 22
  TwoWire I2Cone = TwoWire(0);
  I2Cone.begin(SDA1,SCL1,400000);
  Serial.println("Scanning I2C Addresses Channel 1");
  uint8_t cnt=0;
  for(uint8_t i=0;i<128;i++){
  I2Cone.beginTransmission(i);
  uint8_t ec=I2Cone.endTransmission(true);
  if(ec==0){
      if(i<16)Serial.print('0');
      Serial.print(i,HEX);
      cnt++;
  }
  else Serial.print("..");
  Serial.print(' ');
  if ((i&0x0f)==0x0f)Serial.println();
  }
  Serial.print("Scan Completed, ");
  Serial.print(cnt);
  Serial.println(" I2C Devices found.");
}

void setup_MQTT ()
{
  MQTT.setServer(mqttServer, mqttPort);

  while (!MQTT.connected()) 
  {
    Serial.println("Connecting to MQTT...");
    if (MQTT.connect("ESP32Client", mqttUser, mqttPassword )) 
    {
      Serial.println("connected");
      MQTT.publish("HeStIO/IP", WiFi.localIP().toString().c_str()); 
    } 
    else 
    {
      Serial.print("failed with state ");
      Serial.print(MQTT.state());
      delay(2000);
    }
  }
};

void setup_OTA ()
{
  ArduinoOTA.onStart([]() 
  {
    Serial.println("Start");
    Serial.print ("[          ]");
  });

  ArduinoOTA.onEnd([]() 
  {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) 
  {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    Serial.println();
  });

  ArduinoOTA.onError([](ota_error_t error) 
  {
    Serial.printf("Error[%u]: ", error);
    switch (error)
    {
      case OTA_AUTH_ERROR:
        Serial.println("Begin Failed");
        break;
      case OTA_CONNECT_ERROR:
        Serial.println("Connect Failed");
        break;
      case OTA_RECEIVE_ERROR:
        Serial.println("Receive Failed");
        break;
      case OTA_END_ERROR:
        Serial.println("End Failed");
        break;
      
      default:
        break;
    }
  });
  ArduinoOTA.setHostname("TempLogger");
  ArduinoOTA.begin();  
};

void setup_WIFI ()
{
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
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
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
};

void setup() 
{
  Serial.begin(115200); 
  // Connect to Wi-Fi network with SSID and password
  
  setup_WIFI ();
  setup_MQTT ();
  setup_OTA ();

  delay(1000);
  InOut = new Bedienfeld();
  
  //scanI2C();
};

void loop() 
{
  ArduinoOTA.handle();
  
  if( ButtonsQueue != 0 )
  { 
    BTN_Button Message;
    xQueueReceive(ButtonsQueue,&Message, portMAX_DELAY);
    Serial.print(Message.Name);
    Serial.print("-");
    Serial.println(Message.State);
  }   
}