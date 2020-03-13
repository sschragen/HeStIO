#ifndef ANZEIGE_H
#define ANZEIGE_H

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <FS.h>
#include <JPEGDecoder.h>
#include "JPeg\JPeg.h"

#include <Fonts/FreeMonoBoldOblique12pt7b.h>

#define LED_BUILTIN 2
#define LED_PIN     2

#define TFT_CS      5
#define TFT_RST     4    // you can also connect this to the Arduino reset
#define TFT_DC      22
#define TFT_SCLK    18    // set these to be whatever pins you like!
#define TFT_MOSI    23    // set these to be whatever pins you like!

extern Adafruit_ST7735 tft; 

#define SCREEN_WIDTH 160 // OLED display width, in pixels
#define SCREEN_HEIGHT 128// OLED display height, in pixels
// The colors we actually want to use
// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF


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
        //JPeg *Hintergrund;

        uint16_t AktZeile = 0;
        String LOG[8];

        void drawJPEG (int x, int y,const char *name);
             
    public:
         
        boolean Busy = false;

        Anzeige();
        ~Anzeige();

        void print (String zeile);

        void drawStartbildschirm ();

        void drawButtonRight( uint16_t color);
        void drawButtonLeft ( uint16_t color);
        void drawButtonOK   ( uint16_t color);

        void drawTitle ();
        void drawStatusLeiste ();
        void drawBackground ();

        void drawUpdateScreen();
        void updateUpdateScreen (int percent);

};

#endif