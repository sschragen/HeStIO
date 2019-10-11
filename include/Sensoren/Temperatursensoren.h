#ifndef TEMPERATURSENSOREN_H
#define TEMPERATURSENSOREN_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define ONE_WIRE_BUS 2
#define TEMPERATURE_PRECISION 9



class Temperatursensoren
{
    private:
        /* data */
        void task();
        static void startTaskImpl(void*);
        void startTask();
        int numberOfDevices;
        // We'll use this variable to store a found device address
        OneWire *oneWire;
        DallasTemperature *sensors;
        DeviceAddress tempDeviceAddress;
        void printAddress (DeviceAddress deviceAddress);
                
    public:
        Temperatursensoren();
        ~Temperatursensoren();

};

#endif