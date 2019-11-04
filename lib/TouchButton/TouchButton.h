#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <Arduino.h>
#include <SPIFFS.h>

#define Touch0 4
//#define Touch 1 0 // 
#define Touch2 2
#define Touch3 15
#define Touch4 13
#define Touch5 12
#define Touch6 14
#define Touch7 27
#define Touch8 33
#define Touch9 32

#define TOUCHBUTTON_CONFIG_NAME "Button.cfg"

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
        int Measure  ();

                
    public:
        BTN_Button Button;
            
        void writeConfig ();
        void readConfig ();
        bool configExists  ();
        TouchButton(int _BTN_PIN, String _NAME);
        ~TouchButton();

        
};

#endif