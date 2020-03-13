#ifndef JPeg_h
#define JPeg_h

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <SPIFFS.h>
//#include <ArduinoJson.h>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <JPEGDecoder.h>

class JPeg
{
    private:
        String filename;
        boolean decoded = false;   
        fs::File jpgFile;
        
    public:
        JPeg (const char *name);
        ~JPeg();

        void Draw(Adafruit_ST7735 &tft, int xpos, int ypos);
};

#endif