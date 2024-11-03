#include "MQTTHandler.h"
#include "BC26.h"

extern BC26 bc26; // 使用外部宣告的 BC26 實例

MQTTHandler::MQTTHandler() {}

bool MQTTHandler::connect(String server, String port, String user, String pass)
{
    String command = "AT+QMTOPEN=0,\"" + server + "\"," + port;
    if (!bc26.sendATCommand(command, 10))
        return false;

    command = "AT+QMTCONN=0,0,\"" + user + "\",\"" + pass + "\"";
    return bc26.sendATCommand(command, 11);
}

bool MQTTHandler::publish(String topic, String message)
{
    String command = "AT+QMTPUB=0,0,0,0,\"" + topic + "\"," + message;
    return bc26.sendATCommand(command, 12);
}

bool MQTTHandler::subscribe(String topic)
{
    String command = "AT+QMTSUB=0,1,\"" + topic + "\",0";
    return bc26.sendATCommand(command, 13);
}

bool MQTTHandler::close()
{
    return bc26.sendATCommand("AT+QMTCLOSE=0", 1);
}
