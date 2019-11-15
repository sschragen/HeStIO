#include <Anzeige.h>
#include <StreamUtils.h>
extern "C" {
#include "crypto/base64.h"
}

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST); 

void Anzeige::drawBitmap(int x, int y, String name)
{   
    File file;
    try
    {
        if (!SPIFFS.begin()) 
            throw "SPIFFS not mounted";
        Serial.println("OK 1");
        name = "/"+name+".json";
        Serial.println(name);
        Serial.println("OK 1.1");
        if (!SPIFFS.exists(name))
            throw name + "existiert nicht"; 
        Serial.println("OK 2");
        file = SPIFFS.open(name, "r");                 // Open it
        if (!file)
            Serial.print("konnte datei nicht öffnen");
        Serial.println("OK 3");
        ReadLoggingStream loggingStream(file, Serial);
        DynamicJsonDocument doc(4024);

        DeserializationError error = deserializeJson(doc, loggingStream);
        if (error != DeserializationError::Ok)
            Serial.println(error.c_str());
        Serial.println("OK 4");
        int width = doc["WIDTH"];
        int height = doc["HEIGHT"];
        
        String data = doc["BITMAP"];
        const char* data1 = data.c_str();
        size_t outputLength;

        unsigned char *decoded = base64_decode((const unsigned char *)data1, strlen(data1), &outputLength);


        tft.drawBitmap(x,y,(uint8_t*)decoded,width,height,RED);

        free(decoded);
        //Display->drawBitmap(x, y, (uint8_t*) data1, width, height, 1);
           
    }
    catch(char* s)
    {
        Serial.println ("Anzeige:: drawBitmap - "+*s);
    }
    Serial.println("OK end");
    file.close(); 
    SPIFFS.end ();    
}

void Anzeige::drawStatusLeiste ()
{   
    tft.drawFastHLine(0,96,160,WHITE);
    drawButtonLeft(BLACK);
    drawButtonOK(BLACK);
    drawButtonRight(BLACK);
};

void Anzeige::drawStartbildschirm ()
{   
    tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
    tft.setRotation(3);
    tft.setFont();
    tft.fillScreen(Display_Color_Black);
    
    drawBitmap (1,22,"Startbildschirm");

    drawTitle();  
    drawStatusLeiste ();    
};

void Anzeige::drawTitle ()
{
    tft.fillRect(0,0,160,20,Display_Color_White);
    //tft.setTextSize(2);
    tft.setFont(&FreeMonoBoldOblique12pt7b);
    tft.setCursor(2,14);  
    tft.setTextColor(Display_Color_Black);   // change the text color to foreground color
    tft.print("HeStIO v0.1");  
    tft.setFont();
};

void Anzeige::drawUpdateScreen ()
{
    tft.setFont();
    tft.fillScreen(Display_Color_Black);
    tft.setTextColor(Display_Color_White);
    tft.setTextSize(1);
    tft.setCursor(0,0);  
    tft.print("Upadate Started ...");
    tft.drawRect(0,10,102,12,Display_Color_Red);
};

void Anzeige::updateUpdateScreen (int percent)
{
    tft.drawRect(2,11,percent,10,(uint16_t)Display_Color_Green);
};

void Anzeige::drawButtonRight( uint16_t color)
{
    tft.fillTriangle(100, 98,120,108,100,118, color);
    tft.drawTriangle(100, 98,120,108,100,118, (uint16_t)Display_Color_White);
};

void Anzeige::drawButtonLeft ( uint16_t color)
{   
    tft.fillTriangle( 40,108, 60, 98, 60,118, color);
    tft.drawTriangle( 40,108, 60, 98, 60,118, (uint16_t)Display_Color_White);
};

void Anzeige::drawButtonOK   ( uint16_t color)
{
    tft.fillRect (70,98,20,20,color);
    tft.drawRect (70,98,20,20,(uint16_t)Display_Color_White);
};

Anzeige::Anzeige()
{   Serial.print("Anzeige() running on core ");
    //tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
    //tft.setRotation(3);
    //drawButtonLeft(BLACK);
    //drawButtonOK(BLACK);
    //drawButtonRight(BLACK);
 
}

Anzeige::~Anzeige()
{
    //delete Display;
}