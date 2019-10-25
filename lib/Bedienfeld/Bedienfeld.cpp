
#include <Bedienfeld.h>

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
};

Bedienfeld::Bedienfeld()
{
    //Display = new Anzeige ();
    //Display->Zeige_Startbildschirm ();
    
    xTaskCreatePinnedToCore(
                    this->startTaskImpl,   /* Task function. */
                    "Bedienfeld",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &TaskBedienfeld,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
    delay(500);

    //Btn_Left  = new TouchButton (Touch4,"LEFT");
    Btn_Right = new TouchButton (Touch2,"RIGHT");
    //Btn_OK    = new TouchButton (Touch3,"OK");

}

Bedienfeld::~Bedienfeld()
{
    delete Btn_Left;
    delete Btn_Right;
    delete Btn_OK;

    //delete Display;
}