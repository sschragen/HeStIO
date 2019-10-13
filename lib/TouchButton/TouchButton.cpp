#include <TouchButton.h>

QueueHandle_t ButtonsQueue;
int AnzahlButtons=0;

void TouchButton::task()
{   int TOUCH_SENSOR_VALUE = 0;
    while(1){
        TOUCH_SENSOR_VALUE = touchRead(Button.Pin);
        if (TOUCH_SENSOR_VALUE < Button.Threshold)                                  // Taste wurde berührt
        {
            switch (Button.State)                                                   // anhand des alten State neuen setzen
            {
                case (BTN_OFF) :                                                    // Alter State "nicht berührt"
                    Button.State = BTN_TOUCHED;                                     // Neuer Status "berührt" setzen
                    Button.Start_millis = millis();                                 // Timer sichern
                    xQueueSend(ButtonsQueue,(void *)&Button,(TickType_t )0);        // sende statuswechsel in Queue
                    break;
                case (BTN_TOUCHED) :
                    if (millis()-Button.Start_millis > 3000)
                    {
                        Button.State = BTN_HOLD;
                        xQueueSend(ButtonsQueue,(void *)&Button,(TickType_t )0);    // sende statuswechsel in Queue
                    }
                    break;
                default :
                    break;
                    
            }
        }
        else 
        {
            Button.State = BTN_OFF;
            xQueueSend(ButtonsQueue,(void *)&Button,(TickType_t )0);    // sende statuswechsel in Queue
        }
    }
}

void TouchButton::startTaskImpl(void* _this)
{
    static_cast<TouchButton*>(_this)->task();
}

void TouchButton::startTask(){
    

    //xTaskCreate(this->startTaskImpl, "Task", 2048, this, 5, NULL);
}

int TouchButton::Measure  ()
{   int sum=0;
    for (int i=0; i<10 ; i++)
    {   sum += touchRead(Button.Pin);
        delay (500);
    }
    return sum / 10;    
};

TouchButton::TouchButton(int _BTN_PIN, String _NAME)
{
    AnzahlButtons++;
    Button.Pin = _BTN_PIN;
    Button.State = BTN_OFF;
    Button.Name = _NAME;

    if( ButtonsQueue == NULL )
    {
        // Queue was not created
        ButtonsQueue = xQueueCreate (5, sizeof(BTN_Button));
    }

    xTaskCreatePinnedToCore(this->startTaskImpl, "Task",10000, this, 5, &xHandle,0);
}

TouchButton::~TouchButton()
{
    AnzahlButtons--;
    if (AnzahlButtons==0)
    {
        vQueueDelete(ButtonsQueue);
        
    }
    vTaskDelete (xHandle);
}