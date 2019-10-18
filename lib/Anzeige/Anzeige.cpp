#include <Anzeige.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

#define SDAPIN  12
#define SCLPIN  14

void Anzeige::Zeige_Startbildschirm ()
{   
    display->clearDisplay();
    drawBitmap (1,1,"Startbildschirm");
	display->display();
    delay (5000);
};

void Anzeige::drawBitmap(int x, int y, String name)
{   
    File file;
    try
    {
        if (!SPIFFS.begin()) 
            throw "SPIFFS not mounted";
        
        name = "/"+name+"json";
        if (!SPIFFS.exists(name))
            throw name + "existiert nicht"; 
        
        file = SPIFFS.open(name, "r");                 // Open it
        if (!file)
            throw "konnte datei nicht öffnen";
        DynamicJsonDocument doc(1024);

        DeserializationError error = deserializeJson(doc, file);
        if (error)
            throw "JSON Fehler";
        int width = doc["WIDTH"];
        int height = doc["HEIGHT"];
        
        String data = doc["BITMAP"];
        const char* data1 = data.c_str();

        display->drawBitmap(x, y, (uint8_t*) data1, width, height, 1);
        display->display();     
    }
    catch(char* s)
    {
        Serial.println ("Anzeige:: drawBitmap - "+*s);
    }

    file.close(); 
    SPIFFS.end ();    
}

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