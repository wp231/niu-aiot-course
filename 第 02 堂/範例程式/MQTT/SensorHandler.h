#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H

#include <Arduino.h>
#include <SimpleDHT.h>

class SensorHandler
{
public:
    SensorHandler(int pin);
    bool readData(float &temperature, float &humidity);

private:
    SimpleDHT11 dht;
};

#endif // SENSORHANDLER_H
