#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <Arduino.h>

class MQTTHandler
{
public:
    MQTTHandler();
    bool connect(String server, String port, String user, String pass);
    bool publish(String topic, String message);
    bool subscribe(String topic);
    bool close();
};

#endif // MQTTHANDLER_H
