#ifndef Bedienfeld_h
#define Bedienfeld_h

#include <Arduino.h>
#include <TouchButton.h>
#include <Bedienfeld.h>
#include <Anzeige.h>

extern TaskHandle_t TaskBedienfeld;

void Setup_Bedienfeld (void);

class Bedienfeld
{
    private:
        /* data */
        TouchButton *Btn_Left;// (4, "LEFT");
        TouchButton *Btn_Right;// (Touch2,"RIGHT");
        TouchButton *Btn_OK ;//   (Touch3,"OK");
        TouchButton *Btn_Up;
        TouchButton *Btn_Down;

        Anzeige *Display;

        void task();
        static void startTaskImpl(void*);
        void startTask();
        
    public:
    
        Bedienfeld(/* args */);
        ~Bedienfeld();
};

#endif