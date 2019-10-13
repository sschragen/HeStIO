#ifndef Bedienfeld_h
#define Bedienfeld_h

#include <Arduino.h>
#include "Bedienfeld/TouchButton/TouchButton.h"
#include "Bedienfeld/Anzeige/Anzeige.h"

extern TaskHandle_t TaskBedienfeld;

void Setup_Bedienfeld (void);

class Bedienfeld
{
    private:
        /* data */
        TouchButton *ButtonLeft;// (4, "LEFT");
        TouchButton *ButtonRight;// (Touch2,"RIGHT");
        TouchButton *ButtonOK ;//   (Touch3,"OK");

        Anzeige *Display;

        void task();
        static void startTaskImpl(void*);
        void startTask();
        
    public:
    
        Bedienfeld(/* args */);
        ~Bedienfeld();
};

#endif