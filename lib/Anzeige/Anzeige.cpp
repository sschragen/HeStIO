#include <Anzeige.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SDAPIN  12
#define SCLPIN  14

void Anzeige::Zeige_Startbildschirm ()
{   
    display->clearDisplay();
    draw_Bitmap ("Startbildschirm",1,1,128,64);
	display->display();
    delay (5000);
    display->clearDisplay();
    DrawJsonBitmap ("Startbildschirm",1,1);
	display->display();
};

void Anzeige::DrawJsonBitmap (String filename, int x, int y)
{ 
    filename = "/"+filename+".json";
    try
    {
        if (!SPIFFS.begin())
            throw "SPIFFS kann nicht gestartet werden";

        if (!SPIFFS.exists(filename)) 
            throw filename+" kann nicht geöffnet werden";

        File file = SPIFFS.open(filename, "r"); 

        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, file);
        if (error)
            throw "JSON Error";
        int width = doc["WIDTH"];
        int height = doc["HEIGHT"];
        String data = doc["MONO"];
        const uint8_t* bitmap = (uint8_t*) data.c_str();
        
        file.close(); 

        display->drawXBitmap(x,y,bitmap,width,height,1); 
    }
    catch(char *s)
    {
        Serial.println("Anzeige::DrawJsonBitmap - "+*s);
    }
    SPIFFS.end ();
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