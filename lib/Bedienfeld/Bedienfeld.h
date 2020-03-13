#ifndef Bedienfeld_h
#define Bedienfeld_h

#include <Arduino.h>

#include <TouchButton\TouchButton.h>
#include <Anzeige\Anzeige.h>

#include <Remote\Remote.h>
const int RemoteRecvPin = 26;  //  Der Kontakt der am Infrarotsensor die Daten ausgibt, wird mit Pin 11 des Arduinoboards verbunden.

extern TaskHandle_t TaskBedienfeld;
extern Anzeige *Display; 

// Color definitions
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

class Bedienfeld
{
    private:
        /* data */
        //TouchButton *Btn_Down;

        void task();
        static void startTaskImpl(void*);
        void startTask();
        
        void drawTestScreen(uint8_t t);
        
        
    public:
        Anzeige *pDisplay;
        Remote *MyIR;

        void stopAllTasks();

        Bedienfeld();
        ~Bedienfeld();
};

#endif