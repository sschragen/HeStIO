#include "Anzeige.h"

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST); 

#define BTN_LE_X 40
#define BTN_LE_Y 106

#define BTN_OK_X 70
#define BTN_OK_Y 106

#define BTN_RI_X 100
#define BTN_RI_Y 106

void Anzeige::print (String zeile)
{
    Serial.println (zeile);
    if (AktZeile == 8) 
    {
        //Jetzt zuerst Scrollen um die 8te Zeile Frei zu machen 
        AktZeile--;
    }
    // jetzt in Akt Zeile Schreiben
    LOG[AktZeile] = zeile;
    
    tft.setTextColor(WHITE);
    tft.setTextSize(1);
       
    for (int i=0;i<8;i++)
    {
        tft.setCursor(20,30+(i*8));
        tft.print(LOG[i]);
    }
    AktZeile++;
};

void Anzeige::drawJPEG (int x, int y,const char *name)
{
    if (!Busy)
    {
        Busy = true;
        JPeg *Bild = new JPeg(name);     
        Bild->Draw (tft,x,y);
        delete Bild;
    };
    Busy = false;
};

void Anzeige::drawStatusLeiste ()
{   
    if (!Busy)
    {
        Busy = true;
        tft.drawFastHLine(0,104,160,WHITE);
    };
    Busy = false;

    drawButtonLeft(BLACK);
    drawButtonOK(BLACK);
    drawButtonRight(BLACK);
};



void Anzeige::drawBackground ()
{
    
    //drawJPEG (0,  0,"/bg_oben.jpg");
    drawJPEG (0, 19,"/bg_mitte_oben.jpg");
    //drawJPEG (0, 69,"/bg_mitte_unten.jpg");
    drawJPEG (0,109,"/bg_unten.jpg");
    
    drawStatusLeiste ();
};

void Anzeige::drawStartbildschirm ()
{   
    if (!Busy)
    {
        Busy = true;
        tft.initR(INITR_BLACKTAB);      // Init ST7735S chip, black tab
        tft.setRotation(1);
        tft.setFont();
    }
    Busy = false;

    drawBackground ();  
    //drawJPEG (40,0,"/Flamme.jpg");
};

void Anzeige::drawTitle ()
{
    if (!Busy)
    {
        Busy = true;
        tft.setFont(&FreeMonoBoldOblique12pt7b);
        tft.setCursor(2,15);  
        tft.setTextColor(GREEN);   // change the text color to foreground color
        tft.print("HeStIO v0.1");  
        tft.setFont();
    }
    Busy = false;
};

void Anzeige::drawUpdateScreen ()
{
    if (!Busy)
    {
        drawJPEG (0, 19,"/bg_mitte_oben.jpg");

        Busy = true;
        tft.setFont();
        tft.setTextColor(WHITE);
        tft.setTextSize(1);
        tft.setCursor(20,30);  
        tft.print("Upadate gestarted ...");
        tft.drawRect(29,58,102,12,RED);
    }
    Busy = false;
};

void Anzeige::updateUpdateScreen (int percent)
{
    if (!Busy)
    {
        Busy = true;
        tft.drawRect(30,59,percent,10,GREEN);
    }
    Busy = false;
};

void Anzeige::drawButtonRight( uint16_t color)
{
    if (!Busy)
    {
        Busy = true;
        tft.fillTriangle( BTN_RI_X, BTN_RI_Y, BTN_RI_X+20,BTN_RI_Y+10,BTN_RI_X,BTN_RI_Y+20, color);
        tft.drawTriangle( BTN_RI_X, BTN_RI_Y, BTN_RI_X+20,BTN_RI_Y+10,BTN_RI_X,BTN_RI_Y+20, WHITE);
    }
    Busy = false;
}; 

void Anzeige::drawButtonLeft ( uint16_t color)
{   
    if (!Busy)
    {
        Busy = true;
        tft.fillTriangle( BTN_LE_X,BTN_LE_Y+10, BTN_LE_X+20, BTN_LE_Y, BTN_LE_X+20,BTN_LE_Y+20, color);
        tft.drawTriangle( BTN_LE_X,BTN_LE_Y+10, BTN_LE_X+20, BTN_LE_Y, BTN_LE_X+20,BTN_LE_Y+20, WHITE);
    }
    Busy = false;
};

void Anzeige::drawButtonOK   (uint16_t color)
{
    if (!Busy)
    {
        Busy = true;
        tft.drawRect (BTN_OK_X,BTN_OK_Y,20,20,WHITE);
        tft.fillRect (BTN_OK_X+1,BTN_OK_Y+1,18,18,color);
    }
    Busy = false;
};

Anzeige::Anzeige()
{   
    Serial.print("Anzeige() running on core ");
    
    drawStartbildschirm ();
    
}

Anzeige::~Anzeige()
{
    //delete Display;
    
}