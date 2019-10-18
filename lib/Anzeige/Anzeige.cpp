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
<<<<<<< HEAD

    if (!SPIFFS.begin()) 
    {
        Serial.println("Failed to mount file system");
    }

    File f;
    
    // OPEN FILE (ENTER FILE WITH PATH WIRH SLASH IN FRONT)
    f = SPIFFS.open("/Start128x64.MONO", "r");

    if (f) 
    {
        int s = f.size();
        Serial.printf("File Opened , Size=%d\r\n", s);

        String data = f.readString();
        //Serial.println(data);

        const char* data1 = data.c_str();
        f.close();

        display->drawBitmap(0, 0, (uint8_t*) data1, 128, 64, 1);
        display->display();
    }
    else 
    {
        Serial.println("File Not Opened");
    }
    delay (5000);

    display->setTextColor(WHITE);
	display->setTextSize(1);
	display->setCursor(1,0);
	display->println("HeStIO v0.0.1");
	display->setCursor(14,56);
	display->println("(c) Stephanus Schragen)");
	display->setTextSize(2);
	display->setCursor(34,15);
	display->println("Willkommen");
	
    display->display();
    delay (5000);
=======
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

>>>>>>> 3bbcca630040da71d5e1ab6fe08243f5106878f5
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