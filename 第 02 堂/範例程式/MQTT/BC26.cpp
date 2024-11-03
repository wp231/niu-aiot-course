#include "BC26.h"

BC26::BC26() {}

bool BC26::initialize()
{
    sendATCommand("AT+QGACT=1,1,\"apn\",\"internet.iot\"", 1);
    sendATCommand("AT+QCGDEFCONT=\"IP\",\"internet.iot\"", 1);
    sendATCommand("AT+QBAND=1,8", 1);
    sendATCommand("AT+QRST=1", 0);
    if (sendATCommand("ATE0", 1) == 99 && sendATCommand("AT+CGPADDR=1", 2) == 99)
    {
        return true;
    }
    return false;
}

byte BC26::sendATCommand(String msg, byte stepNum)
{
    String expectedResponse;
    switch (stepNum)
    {
    case 0:
        expectedResponse = "+IP:";
        break;
    case 1:
        expectedResponse = "OK";
        break;
    case 2:
        expectedResponse = "+CGPADDR:";
        break;
    case 10:
        expectedResponse = "+QMTOPEN: 0,0";
        break;
    case 11:
        expectedResponse = "+QMTCONN: 0,0,0";
        break;
    case 12:
        expectedResponse = "+QMTPUB: 0,0,0";
        break;
    case 13:
        expectedResponse = "+QMTSUB: 0,1,0,0";
        break;
    }

    Serial.println(msg);
    Serial1.println(msg);
    String response = checkReceivedData();
    long startTime = millis();
    while (!response.startsWith(expectedResponse))
    {
        response = checkReceivedData();
        if ((startTime + waitingTime) < millis())
            return stepNum;
    }
    return 99;
}

String BC26::checkReceivedData()
{
    String data = "";
    char c;
    while (Serial1.available())
    {
        delay(50);
        c = Serial1.read();
        data += c;
        if (c == '\n')
            break;
    }
    data.trim();
    return data;
}
