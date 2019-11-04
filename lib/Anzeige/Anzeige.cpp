#include <Anzeige.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)

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
    //Wire.begin(SDAPIN, SCLPIN); 

    #define SDA1 21
    #define SCL1 22
    TwoWire I2Cone = TwoWire(0);
    I2Cone.begin(SDA1,SCL1,400000);
    Serial.println("Scanning I2C Addresses Channel 1");
    uint8_t cnt=0;
    for(uint8_t i=0;i<128;i++){
    I2Cone.beginTransmission(i);
    uint8_t ec=I2Cone.endTransmission(true);
    if(ec==0){
        if(i<16)Serial.print('0');
        Serial.print(i,HEX);
        cnt++;
    }
    else Serial.print("..");
    Serial.print(' ');
    if ((i&0x0f)==0x0f)Serial.println();
    }
    Serial.print("Scan Completed, ");
    Serial.print(cnt);
    Serial.println(" I2C Devices found.");

    Serial.println("Wire gestartet");
    display = new Adafruit_SSD1306 (SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
    Serial.println("Display ADA gestartet A");
    
    display->begin(SSD1306_SWITCHCAPVCC, 0x3C,false);
    if (display) 
        Serial.println("Display ADA gestartet B");
    else
        {
             Serial.println("Display ADA NICHT gestartet B");    
        }
    
    display->clearDisplay();
    display->setTextSize(1);             // Normal 1:1 pixel scale
    display->setTextColor(WHITE);        // Draw white text
    display->setCursor(0,0);             // Start at top-left corner
    display->println(F("Hello, world!"));
    display->display();
    // Zeige Startbildschirm
    //Zeige_Startbildschirm (); 
    //delay (5000);

    // Eventhandler einrichten

    // Zeige ersten Statusbildschirm   
}

Anzeige::~Anzeige()
{
    delete display;
}