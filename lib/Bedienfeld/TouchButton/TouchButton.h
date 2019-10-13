#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <Arduino.h>

#define Touch0 4
//const int Touch0 = 4;
        //Touch1 >>  ((Not available on Devkit 30 pin version but available on Devkit 36 pin version 
const int Touch2 = 2;
const int Touch3 = 15;
const int Touch4 = 13;
const int Touch5 = 12;
const int Touch6 = 14;
const int Touch7 = 27;
const int Touch8 = 33;
const int Touch9 = 32;

extern QueueHandle_t ButtonsQueue;
extern int AnzahlButtons;

typedef enum
    {   
        BTN_OFF,
        BTN_TOUCHED,
        BTN_HOLD
    } BTN_STATE_TYPE;


typedef struct 
    {
        //char Name[10];
        String Name;
        BTN_STATE_TYPE State;
        int Pin;
        int Start_millis;
        int Threshold = 30;
    } BTN_Button; 

class TouchButton
{
    private:
        /* data */
        void task();
        static void startTaskImpl(void*);
        void startTask();
        TaskHandle_t xHandle = NULL;
                
    public:
        BTN_Button Button;
            
        TouchButton(int _BTN_PIN, String _NAME);
        ~TouchButton();

        int Measure  ();

};

#endif