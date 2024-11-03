#include "SensorHandler.h"

SensorHandler::SensorHandler(int pin) : dht(pin) {}

bool SensorHandler::readData(float &temperature, float &humidity)
{
    int err = dht.read2(&temperature, &humidity, NULL);
    return err == SimpleDHTErrSuccess;
}
