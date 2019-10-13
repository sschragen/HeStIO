#include <SerOut.h>

TaskHandle_t xHandle = NULL;
QueueHandle_t SerQueue = NULL;
int Anzahl=0;

void SerOut::task ()
{
    Serial.print("Task 'CheckForButtonPress' started on Core ");
    Serial.println(xPortGetCoreID());

    SER_MESSAGE *pxRxedMessage;

    for(;;)
    {   
        // Check the Queue
        if( SerQueue != 0 )
        {
            // Receive a message on the created queue.  Block for 10 ticks if a
            // message is not immediately available.
            if( xQueueReceive( SerQueue, &( pxRxedMessage ), ( TickType_t ) 10 ) )
            {
                Serial.print   (pxRxedMessage->sender);
                Serial.print   (" : " );
                Serial.println (pxRxedMessage->message);
            }
        }

        Serial.println ();
    } 
};

void SerOut::startTaskImpl(void* _this)
{
    static_cast<SerOut*>(_this)->task();
}

SerOut::SerOut(/* args */)
{   
    Anzahl++;
    if (SerQueue == NULL)
    {
         SerQueue = xQueueCreate( 1, sizeof( SER_MESSAGE ) );
         xTaskCreatePinnedToCore(this->startTaskImpl, "Task",10000, this, 5, &xHandle,0);
    }
    
   
}

SerOut::~SerOut()
{
    Anzahl--;
    if (Anzahl==0)
    {
        vQueueDelete(SerQueue);
        vTaskDelete (xHandle);
    }
}