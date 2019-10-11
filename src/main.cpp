#include <Arduino.h>
#include <FS.h>

#include "Bedienfeld/Bedienfeld.h"
#include "Daten/Daten.h"
#include "Sensoren/Temperatursensoren.h"
#include "Kommunikation/SerOut.h"

Daten Steuerungsdaten();
SerOut Ausgabe();
Temperatursensoren Sensoren();

void setup() 
{
  Serial.begin(115200); 
  
  //Setup_Bedienfeld ();
};

void loop() 
{
  
}