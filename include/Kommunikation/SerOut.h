#ifndef SerOut_h
#define SerOut_h

#include <Arduino.h>

extern QueueHandle_t SerQueue;
extern TaskHandle_t xHandle;

typedef struct
{
    char sender[20];
    char message[30];
} SER_MESSAGE;

class SerOut
{
    private:
        /* data */
        void task();
        static void startTaskImpl(void*);
        void startTask();
        
    public:
    
        SerOut(/* args */);
        ~SerOut();
};

#endif