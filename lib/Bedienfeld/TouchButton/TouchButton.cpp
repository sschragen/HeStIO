#include "TouchButton.h"

QueueHandle_t ButtonsQueue;
int AnzahlButtons=0;


void TouchButton::task()
{   int TOUCH_SENSOR_VALUE = 0;
    Serial.print("Task 'Touchbutton' started on Core ");
    Serial.println(xPortGetCoreID());
    while(1)
    {
        TOUCH_SENSOR_VALUE = touchRead(ButtonData.Pin);
        //Serial.print (TOUCH_SENSOR_VALUE);
        //Serial.print (".");
        if (TOUCH_SENSOR_VALUE < ButtonData.Threshold)                                  // Taste wurde berührt
        {
            switch (ButtonData.State)                                                   // anhand des alten State neuen setzen
            {
                case (BTN_OFF) :                                                    // Alter State "nicht berührt"
                    ButtonData.State = BTN_JITTER;                                     // Neuer Status "berührt" setzen
                    ButtonData.Start_millis = millis();                                 // Timer sichern
                    //Serial.printf("%2d %s jitter\n",TOUCH_SENSOR_VALUE,Button.Name);
                    break;
                case (BTN_JITTER) :
                    if (millis()-ButtonData.Start_millis > 150)
                    {   
                        ButtonData.State = BTN_TOUCHED;                                     // Neuer Status "berührt" setzen
                        xQueueSend(ButtonsQueue,&ButtonData,(TickType_t)0);        // sende statuswechsel in Queue
                        Serial.printf("%2d %d touched\n",TOUCH_SENSOR_VALUE,ButtonData.Name);
                    }
                    break;
                case (BTN_TOUCHED) :
                    if (millis()-ButtonData.Start_millis > 2000)
                    {
                        ButtonData.State = BTN_HOLD;
                        xQueueSend(ButtonsQueue,&ButtonData,(TickType_t)0);    // sende statuswechsel in Queue
                        //digitalWrite(LED_BUILTIN, HIGH);
                        //Serial.println(String(Button.Name)+" hold");
                    }
                    break;
                default :
                    //Serial.println(" nothing");
                    break;
                    
            }
        }
        else 
        {
            if ((ButtonData.State == BTN_TOUCHED) || (ButtonData.State == BTN_HOLD)) 
            {
                ButtonData.State = BTN_OFF;
                xQueueSend(ButtonsQueue,&ButtonData,(TickType_t )0);    // sende statuswechsel in Queue
            }
            ButtonData.State = BTN_OFF;
            //digitalWrite(LED_BUILTIN, LOW);
            
        }
        //Serial.println (TOUCH_SENSOR_VALUE);
        vTaskDelay( 50 / portTICK_PERIOD_MS );
    }
    
}

void TouchButton::startTaskImpl(void* _this)
{
    static_cast<TouchButton*>(_this)->task();
}

uint8_t TouchButton::getState ()
{
    return ButtonData.State;
};

int TouchButton::Measure  ()
{   int sum=0;
    Serial.printf("Kalibrierung von Button %d läuft \n",ButtonData.Name);
    for (int i=0; i<10 ; i++)
    {   int act = touchRead(ButtonData.Pin);
        //Serial.printf (" %3d",act);
        sum += act;
        delay (20);
    }
    //Serial.println();
    return sum / 10;    
};

void TouchButton::writeConfig ()
{

};

void TouchButton::readConfig ()
{

};

bool TouchButton::configExists ()
{   if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return false;
    }
    else 
    {
        File file = SPIFFS.open(TOUCHBUTTON_CONFIG_NAME, FILE_READ);
        if (!file) 
        {
            Serial.println("There was an error opening the file for writing");
            file.close();
            return false;
        }
        file.close();
    }
    
    return true;
};

boolean TouchButton::enable ()
{
    if (!enabled) 
    {   
        xTaskCreatePinnedToCore(this->startTaskImpl, "Task", 2048, this, 5, NULL,1);
        enabled = true;
    }
    return enabled;
};

boolean TouchButton::disable ()
{
    if (enabled)
    {
        vTaskDelete (xHandle);
        enabled = false;
    }
    return enabled;
};

TouchButton::TouchButton(int _BTN_PIN, ButtonName_t name)
{
    AnzahlButtons++;
    if( ButtonsQueue == NULL )
    {
        // Queue was not created
        ButtonsQueue = xQueueCreate (20, sizeof(ButtonData_t));
        Serial.println("MSG Queue created");
    }

    if (configExists ())
    {
        //readConfig ();
    }
    else 
    {
        ButtonData.Pin = _BTN_PIN;
        ButtonData.State = BTN_OFF;
        ButtonData.Name = name;
        int Eichung = Measure ();
        Serial.printf ("Eichung Taste %d - %d \n",(uint8_t)ButtonData.Name,Eichung);
        if (Eichung >40 )
            ButtonData.Threshold = Eichung-20;
        else 
            //failsafe
            ButtonData.Threshold = 15;
    }
    //startTask();
    enable ();
};

TouchButton::~TouchButton()
{
    AnzahlButtons--;
    if (AnzahlButtons==0)
    {
        vQueueDelete(ButtonsQueue);
        
    }
    vTaskDelete (xHandle);
};