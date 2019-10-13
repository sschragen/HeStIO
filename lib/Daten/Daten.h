#ifndef DATEN_H
#define DATEN_H

#include <Arduino.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

typedef enum
{
    STEUERUNG_AUS,
    STEUERUNG_AN,
    STEUERUNG_FROSTSCHUTZ,
    STEUERUNG_SCHORNSTEINFEGER,
    STEUERUNG_FEHLER
} STATUS_STEUERUNG;

typedef enum
{
    BRENNER_AUS,
    BRENNER_AN,
    BRENNER_FEHLER
} STATUS_BRENNER;

typedef enum
{
    PUMPE_AUS,
    PUMPE_AN,
    PUMPE_FEHLER              // not used
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