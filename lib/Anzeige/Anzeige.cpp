#include <Anzeige.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SDAPIN  12
#define SCLPIN  14

void Anzeige::Zeige_Startbildschirm ()
{   
    
    display->setTextColor(WHITE);
	display->setTextSize(1);
	display->setCursor(1,0);
	display->println("Display init ...");
	display->display();
};

void Anzeige::Zeige_Bitmap(String name, int x, int y, int width, int height)
{   
    // LOAD FILESYSTEM
    if (!SPIFFS.begin()) 
    {
        Serial.println("Failed to mount file system");
    }
    File f = SPIFFS.open("/"+name+".mono", "r");
    if (f) 
    {
        int s = f.size();
        Serial.printf("File Opened , Size=%d\r\n", s);
        String data = f.readString();
        //Serial.println(data);
        const char* bitmap = data.c_str();
        f.close();
        display->drawXBitmap(x,y,(const uint8_t*) bitmap,width,height,1); 
        display->display();
    } 
    else 
    {
        Serial.println("File Not Opened");
    }

};

Anzeige::Anzeige()
{   
    // Display initialisieren
    //configure i2c
    Wire.begin(SDAPIN, SCLPIN); 
    display = new Adafruit_SSD1306 (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    
    display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display->display();
    delay(2000); // Pause for 2 seconds
    display->clearDisplay();
	
    // Zeige Startbildschirm
    Zeige_Startbildschirm (); 

    // Eventhandler einrichten

    // Zeige ersten Statusbildschirm   
}

Anzeige::~Anzeige()
{
    delete display;
}