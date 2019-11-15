
#include <Bedienfeld.h>

TaskHandle_t TaskBedienfeld;
Anzeige Display;

void Bedienfeld::task ()
{
    Serial.print("Task 'CheckForButtonPress' started on Core ");
    Serial.println(xPortGetCoreID());
    
    for(;;)
    {   // Check the Queue
        ButtonData_t Message;
        xQueueReceive(ButtonsQueue,&Message, portMAX_DELAY); // wait for next Message
        uint16_t color =0;
        switch (Message.State)
        {   
            case BTN_OFF :
                color = BLACK;       
            break;
            case BTN_TOUCHED :
                color = GREEN;
            break;
            case BTN_HOLD :
                color = RED;                
            break;   
            default:
            break;     
        }
        switch (Message.Name)
        {
            case BTN_LEFT:
                Display.drawButtonLeft((uint16_t)color); 
                //Serial.printf("Left - pressed %d/n",color);
            break;
            case BTN_OK:
                Display.drawButtonOK((uint16_t)color); 
                //Serial.printf("OK - pressed %d/n",color);
            break;
            case BTN_RIGHT:
                Display.drawButtonRight((uint16_t)color);   
                //Serial.printf("Right - pressed %d/n",color); 
            break;
            default:
            break;  
        }
    } 
};

void Bedienfeld::startTaskImpl(void* _this)
{
    static_cast<Bedienfeld*>(_this)->task();
};

void Bedienfeld::drawTestScreen(uint8_t t)
{    

};

void Bedienfeld::stopAllTasks()
{
    delete Btn_Left;
    delete Btn_Right;
    delete Btn_OK;
};

Bedienfeld::Bedienfeld()
{
    //Display = new Anzeige();
    //Serial.print("*Display : "); Serial.printf("%#10x",Display->Display);
    

    Serial.println("Erzeuge Buttons");
    Btn_Left  = new TouchButton (Touch4,BTN_LEFT);
    Btn_Right = new TouchButton (Touch6,BTN_RIGHT);
    Btn_OK    = new TouchButton (Touch5,BTN_OK);
    Serial.println("Buttons fertig");

    Display.drawStartbildschirm();
    
    xTaskCreatePinnedToCore(
                    this->startTaskImpl,    /* Task function. */
                    "Bedienfeld",           /* name of task. */
                    2048,                   /* Stack size of task */
                    NULL,                   /* parameter of the task */
                    1,                      /* priority of the task */
                    &TaskBedienfeld,         /* Task handle to keep track of created task */
                    1);                      /* pin task to core 0 */                  
    delay(500);

    

}

Bedienfeld::~Bedienfeld()
{
    delete Btn_Left;
    delete Btn_Right;
    delete Btn_OK;

    //delete Display;
}