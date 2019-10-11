
#include "Bedienfeld/Bedienfeld.h"

TaskHandle_t TaskBedienfeld;

void Bedienfeld::task ()
{
    Serial.print("Task 'CheckForButtonPress' started on Core ");
    Serial.println(xPortGetCoreID());

    for(;;)
    {   // Check the Queue
       
    } 
};

void Bedienfeld::startTaskImpl(void* _this)
{
    static_cast<Bedienfeld*>(_this)->task();
}

Bedienfeld::Bedienfeld(/* args */)
{
    Display = new Anzeige ();
    
    xTaskCreatePinnedToCore(
                    this->startTaskImpl,   /* Task function. */
                    "Bedienfeld",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &TaskBedienfeld,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
    delay(500);

    ButtonLeft  = new TouchButton (Touch4,"LEFT");
    ButtonRight = new TouchButton (Touch2,"RIGHT");
    ButtonOK    = new TouchButton (Touch3,"OK");

    Display = new Anzeige ();
}

Bedienfeld::~Bedienfeld()
{
    delete ButtonLeft;
    delete ButtonRight;
    delete ButtonOK;

    delete Display;
}