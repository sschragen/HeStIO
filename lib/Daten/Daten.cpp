#include <Daten.h>


void Daten::SollwerteSpeichern ()
{
    if (SPIFFS.begin())
    {
        DynamicJsonDocument doc(1024);
    
        doc["Vorlauf" ] = Sollwert.Temp_Vorlauf;
        doc["Rücklauf"] = Sollwert.Temp_Ruecklauf;

        File File = SPIFFS.open("/Sollwerte.ini", "w");
        serializeJsonPretty(doc, File); 
        File.close();

    }
    else
    { 
        Serial.println ("SollwerteSpeichern: SPIFFS not mountet ...");
        
    }
    SPIFFS.end();
};

void Daten::SollwerteLaden ()
{ 
    if (SPIFFS.begin())
    {
        if (SPIFFS.exists("Sollwerte.ini")) 
        {
            File file = SPIFFS.open("Sollwerte.ini", "r");                 // Open it
            DynamicJsonDocument doc(1024);

            DeserializationError error = deserializeJson(doc, file);
            if (error)
                return;
            Sollwert.Temp_Vorlauf = doc["Vorlauf"];
            Sollwert.Temp_Ruecklauf = doc["Ruecklauf"];
            
            file.close();                                       // Then close the file again
        }
        else 
        {
            Serial.println("\tFile Not Found");
            //Standardsollwerte setzten
            // ...
        }
        SPIFFS.end ();
    }
    else
    { 
        Serial.println ("SollwerteLaden: SPIFFS not mountet ...");
        
    }
};

Daten::Daten()
{
    Sollwert.Temp_Vorlauf = 65;
    Sollwert.Temp_Ruecklauf = 55;
    Sollwert.Brenner = BRENNER_AUS;
    Sollwert.Pumpe = PUMPE_AN;
    Sollwert.Niveau = 1;
    Sollwert.Neigung = 1;
};

Daten::~Daten()
{

};