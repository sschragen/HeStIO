#ifndef DATEN_H
#define DATEN_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

typedef struct 
{
    /* data */
    int Temp_Vorlauf;
    int Temp_Ruecklauf;
    int Temp_Aussen;

    bool Brenner_An;
    bool Pumpe_An;

    bool Error;

    float Neigung;
    float Niveau;

    
} DATEN;

class Daten
{
    private:
        /* data */
        DATEN Sollwert;
        DATEN Istwert;
                        
    public:
        Daten();
        ~Daten();

        void SollwerteSpeichern ();
        void SollwerteLaden ();
};

#endif