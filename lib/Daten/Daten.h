#ifndef DATEN_H
#define DATEN_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

typedef enum
{
    AUS,
    AN,
    FROSTSCHUTZ,
    SCHORNSTEINFEGER,
    FEHLER
} STATUS_STEUERUNG;

typedef enum
{
    AUS,
    AN,
    FEHLER
} STATUS_BRENNER;

typedef enum
{
    AUS,
    AN,
    FEHLER              // not used
} STATUS_PUMPE;

typedef struct 
{
    /* data */
    STATUS_STEUERUNG    Steuerung;
    STATUS_BRENNER      Brenner;
    STATUS_PUMPE        Pumpe;

    bool Error;

    int Temp_Vorlauf;
    int Temp_Ruecklauf;
    int Temp_Aussen;

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