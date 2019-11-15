#ifndef Bedienfeld_h
#define Bedienfeld_h

#include <Arduino.h>
#include <TouchButton.h>
#include <Anzeige.h>


extern Anzeige Display; 
extern TaskHandle_t TaskBedienfeld;

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
        //Anzeige *Display;
        TouchButton *Btn_Left;// (4, "LEFT");
        TouchButton *Btn_Right;// (Touch2,"RIGHT");
        TouchButton *Btn_OK ;//   (Touch3,"OK");

        void stopAllTasks();

        Bedienfeld(/* args */);
        ~Bedienfeld();
};

#endif