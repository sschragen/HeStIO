#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <Arduino.h>

#define Touch0 4
#define Touch2 2
#define Touch3 15
#define Touch4 13
#define Touch5 12
#define Touch6 14
#define Touch7 27
#define Touch8 33
#define Touch9 32


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
        char Name[10];
        //String Name;
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