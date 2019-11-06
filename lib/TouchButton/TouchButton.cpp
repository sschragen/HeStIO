#include <TouchButton.h>

QueueHandle_t ButtonsQueue;
int AnzahlButtons=0;

void TouchButton::task()
{   int TOUCH_SENSOR_VALUE = 0;
    while(1)
    {
        TOUCH_SENSOR_VALUE = touchRead(Button.Pin);
        //Serial.print (TOUCH_SENSOR_VALUE);
        //Serial.print (".");
        if (TOUCH_SENSOR_VALUE < Button.Threshold)                                  // Taste wurde berührt
        {
            switch (Button.State)                                                   // anhand des alten State neuen setzen
            {
                case (BTN_OFF) :                                                    // Alter State "nicht berührt"
                    Button.State = BTN_TOUCHED;                                     // Neuer Status "berührt" setzen
                    Button.Start_millis = millis();                                 // Timer sichern
                    xQueueSend(ButtonsQueue,&Button,(TickType_t)0);        // sende statuswechsel in Queue
                    Serial.printf("%2d %s touched\n",TOUCH_SENSOR_VALUE,Button.Name);
                    break;
                case (BTN_TOUCHED) :
                    if (millis()-Button.Start_millis > 2000)
                    {
                        Button.State = BTN_HOLD;
                        xQueueSend(ButtonsQueue,&Button,(TickType_t)0);    // sende statuswechsel in Queue
                        digitalWrite(LED_BUILTIN, HIGH);
                        Serial.println(String(Button.Name)+" hold");
                    }
                    break;
                default :
                    //Serial.println(" nothing");
                    break;
                    
            }
        }
        else 
        {
            Button.State = BTN_OFF;
            digitalWrite(LED_BUILTIN, LOW);
            //xQueueSend(ButtonsQueue,(void *)&Button,(TickType_t )0);    // sende statuswechsel in Queue
        }
        //Serial.println (TOUCH_SENSOR_VALUE);
        vTaskDelay( 150 / portTICK_PERIOD_MS );
    }
    
}

void TouchButton::startTaskImpl(void* _this)
{
    static_cast<TouchButton*>(_this)->task();
}

void TouchButton::startTask()
{
    xTaskCreatePinnedToCore(this->startTaskImpl, "Task", 2048, this, 5, NULL,0);
}

int TouchButton::Measure  ()
{   int sum=0;
    Serial.printf("Kalibrierung von Button %s läuft \n",Button.Name);
    for (int i=0; i<10 ; i++)
    {   int act = touchRead(Button.Pin);
        Serial.printf (" %3d",act);
        sum += act;
        delay (500);
    }
    Serial.println();
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

TouchButton::TouchButton(int _BTN_PIN, String _NAME)
{
    if (configExists ())
    {
        readConfig ();
    }
    else 
    {
        Button.Pin = _BTN_PIN;
        Button.State = BTN_OFF;
        _NAME.toCharArray(Button.Name,10);

        int Eichung = Measure ();
        Serial.print ("Eichung Taste "+_NAME+" ");
        Serial.println (Eichung);
        if (Eichung >40 )
            Button.Threshold = Eichung-35;
        else 
            //failsafe
            Button.Threshold = 15;
    }

    AnzahlButtons++;
    if( ButtonsQueue == NULL )
    {
        // Queue was not created
        ButtonsQueue = xQueueCreate (5, sizeof(BTN_Button));
        Serial.println("MSG Queue created");
    }

    //xTaskCreatePinnedToCore(this->startTaskImpl, "Task",10000, this, 5, &xHandle,1);
    //xTaskCreate (this->startTaskImpl, "Task",10000, this, 5, &xHandle);
    startTask();
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