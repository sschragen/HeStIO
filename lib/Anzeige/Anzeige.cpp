#include <Anzeige.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SDAPIN  12
#define SCLPIN  14

void Anzeige::Zeige_Startbildschirm ()
{   
    display->clearDisplay();
    draw_Bitmap ("HESTIO - Startbildschirm.mono",1,1,128,64);
	display->display();
};

void Anzeige::draw_Bitmap(String name, int x, int y, int width, int height)
{   
    try
    {   
        if (!SPIFFS.begin()) 
            throw "Failed to mount file system";
        File file = SPIFFS.open("/"+name+".mono", "r");
        if (!file) 
            throw "File /" + name +".mono Not Opened";
        
        String data = file.readString();
        file.close();

        const uint8_t* bitmap = (uint8_t*) data.c_str();
        
        display->drawXBitmap(x,y,bitmap,width,height,1); 
    }
    catch (char *s) 
    {
        Serial.println("Anzeige::ZeigeBitmap - "+*s);
    }

};

Anzeige::Anzeige()
{   
    // Display initialisieren
    //configure i2c
    Wire.begin(SDAPIN, SCLPIN); 
    display = new Adafruit_SSD1306 (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    
    display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    // Zeige Startbildschirm
    Zeige_Startbildschirm (); 
    delay (5000);

    // Eventhandler einrichten

    // Zeige ersten Statusbildschirm   
}

Anzeige::~Anzeige()
{
    delete display;
}