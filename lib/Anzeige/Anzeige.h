#ifndef ANZEIGE_H
#define ANZEIGE_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPIFFS.h>

#define OLED_RESET 4

typedef enum
    {   
        DSP_START,
        DSP_INFO,
        DSP_ON_OFF,
        DSP_SEN_VORLAUF,
        DSP_SEN_RUECKLAUF,
        DSP_SEN_AUSSEN,
    } DSP_STATE_TYPE;

class Anzeige
{
    private:
        /* data */
        DSP_STATE_TYPE DisplayStatus = DSP_START;
        Adafruit_SSD1306 *display;
                
    public:
        
        Anzeige();
        ~Anzeige();

        void Zeige_Startbildschirm ();
        void draw_Bitmap(String name, int x, int y, int width, int height);

};

#endif