#include "Remote.h"

QueueHandle_t RemoteQueue;

void Remote::task()
{   
    Serial.print("Task 'Remote' started on Core ");
    Serial.println(xPortGetCoreID());
    while(1)
    {
        if (irrecv->decode(&results)) 
        {    //Wenn Daten empfangen wurden,
            serialPrintUint64(results.value, HEX);
            Serial.println("");
            irrecv->resume(); 
        }

        vTaskDelay( 50 / portTICK_PERIOD_MS );
    }
    
}

void Remote::startTaskImpl(void* _this)
{
    static_cast<Remote*>(_this)->task();
}

uint8_t Remote::getState ()
{
    return RemoteData.State;
};


void Remote::writeConfig ()
{

};

void Remote::readConfig ()
{

};

bool Remote::configExists ()
{   if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return false;
    }
    else 
    {
        File file = SPIFFS.open(REMOTE_CONFIG_NAME, FILE_READ);
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

boolean Remote::enable ()
{
    if (!enabled) 
    {   
        xTaskCreatePinnedToCore(this->startTaskImpl, "Task", 2048, this, 5, NULL,1);
        enabled = true;
    }
    return enabled;
};

boolean Remote::disable ()
{
    if (enabled)
    {
        vTaskDelete (xHandle);
        enabled = false;
    }
    return enabled;
};

Remote::Remote(int _BTN_PIN)
{
    enabled = false;
    if( RemoteQueue == NULL )
    {
        // Queue was not created
        RemoteQueue = xQueueCreate (20, sizeof(RemoteData_t));
        Serial.println("RMT Queue created");
    }
    else 
    {
        RemoteData.Pin = _BTN_PIN;
        RemoteData.State = RMT_OFF;       
    }

    //startTask();
    irrecv = new IRrecv (_BTN_PIN); 
    enable ();
};

Remote::~Remote()
{
    delete irrecv;
    vQueueDelete(RemoteQueue);
    vTaskDelete (xHandle);
};