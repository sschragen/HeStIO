#include "Sensoren/Temperatursensoren.h"

void Temperatursensoren::task()
{ 
    sensors->requestTemperatures(); // Send the command to get temperatures
  
    // Loop through each device, print out temperature data
    for(int i=0;i<numberOfDevices; i++)
    {
        // Search the wire for address
        if(sensors->getAddress(tempDeviceAddress, i)){
        // Output the device ID
        Serial.print("Temperature for device: ");
        Serial.println(i,DEC);
        // Print the data
        float tempC = sensors->getTempC(tempDeviceAddress);
        Serial.print("Temp C: ");
        Serial.print(tempC);
        Serial.print(" Temp F: ");
        Serial.println(DallasTemperature::toFahrenheit(tempC)); // Converts tempC to Fahrenheit
        }
    }
    vTaskDelay(5000 / portTICK_PERIOD_MS);  
};

void Temperatursensoren::startTaskImpl(void* _this)
{
    
};

void Temperatursensoren::startTask()
{
    
};

void Temperatursensoren::printAddress(DeviceAddress deviceAddress) 
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
    }
}

Temperatursensoren::Temperatursensoren()
{
    oneWire = new OneWire(ONE_WIRE_BUS);
    sensors = new DallasTemperature(oneWire);

    numberOfDevices = sensors->getDeviceCount();
    Serial.print("Locating devices...");
    Serial.print("Found ");
    Serial.print(numberOfDevices, DEC);
    Serial.println(" devices.");    

    for(int i=0;i<numberOfDevices; i++)
    {
        // Search the wire for address
        if(sensors->getAddress(tempDeviceAddress, i))
        {
            Serial.print("Found device ");
            Serial.print(i, DEC);
            Serial.print(" with address: ");
            printAddress(tempDeviceAddress);
            Serial.println();
        } 
        else 
        {
            Serial.print("Found ghost device at ");
            Serial.print(i, DEC);
            Serial.print(" but could not detect address. Check power and cabling");
        }
    }
};

Temperatursensoren::~Temperatursensoren()
{
    delete sensors;
    delete oneWire;
}