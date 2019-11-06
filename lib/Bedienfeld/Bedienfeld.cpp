
#include <Bedienfeld.h>

TaskHandle_t TaskBedienfeld;

void Bedienfeld::task ()
{
    Serial.print("Task 'CheckForButtonPress' started on Core ");
    Serial.println(xPortGetCoreID());

    for(;;)
    {   // Check the Queue
        if( ButtonsQueue != 0 )
        { 
            BTN_Button Message;
            xQueueReceive(ButtonsQueue,&Message, portMAX_DELAY);
            Serial.print(Message.Name);
            Serial.print("-");
            Serial.println(Message.State);
        }  
        vTaskDelay( 100 / portTICK_PERIOD_MS );
    } 
};

void Bedienfeld::startTaskImpl(void* _this)
{
    static_cast<Bedienfeld*>(_this)->task();
};

Bedienfeld::Bedienfeld()
{
    Serial.println("Erzeuge Buttons");
    Btn_Left  = new TouchButton (Touch4,"LEFT");
    Btn_Right = new TouchButton (Touch6,"RIGHT");
    Btn_OK    = new TouchButton (Touch5,"OK");
    Serial.println("Buttons fertig");
    
    xTaskCreatePinnedToCore(
                    this->startTaskImpl,   /* Task function. */
                    "Bedienfeld",     /* name of task. */
                    2048,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &TaskBedienfeld,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 0 */                  
    delay(500);

    

}

Bedienfeld::~Bedienfeld()
{
    delete Btn_Left;
    delete Btn_Right;
    delete Btn_OK;

    //delete Display;
}