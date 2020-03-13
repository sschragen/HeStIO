#ifndef REMOTE_H
#define REMOTE_H

#include <Arduino.h>
#include <SPIFFS.h>

#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

//IRrecv irrecv(RECV_PIN);   // An dieser Stelle wird ein Objekt definiert, dass den Infrarotsensor an Pin 11 ausliest.
// Dieser Befehl sorgt dafür, dass die Daten, die per Infrarot eingelesen werden unter „results“ abgespeichert werden.

#define REMOTE_CONFIG_NAME "Remote.cfg"

extern QueueHandle_t RemoteQueue;

typedef enum
{
    RMT_OFF,
    RMT_PRESSED,
    RMT_HOLD,
    RMT_RELEASED 
} RemoteState_t;

typedef enum
{
    RMT_LEFT,
    RMT_OK,
    RMT_RIGHT,
    RMT_UP,
    RMT_DOWN
}   RemoteName_t;

typedef struct 
{
    RemoteName_t Name;
    RemoteState_t State;
    int Pin;
} RemoteData_t; 

class Remote
{
    private:
        /* data */
        void task();
        static void startTaskImpl(void*);
        void startTask();
        TaskHandle_t xHandle = NULL;
     
        IRrecv *irrecv;
        decode_results results;
                
    public:
        boolean enabled = false;
        RemoteData_t RemoteData;

        uint8_t getState ();

        void writeConfig ();
        void readConfig ();
        bool configExists  ();


        boolean enable ();
        boolean disable ();

        Remote(int _BTN_PIN);
        ~Remote();
                
};

#endif