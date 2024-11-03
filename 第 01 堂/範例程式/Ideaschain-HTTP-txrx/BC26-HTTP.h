#ifndef BC26_HTTP_H
#define BC26_HTTP_H

#include <Arduino.h>

class BC26_HTTP
{
public:
     BC26_HTTP();

     String Check_RevData();
     byte Send_ATcommand(String msg, byte stepnum);
     bool BC26init();
     bool Connect_HTTP_Server(String serverName);
     bool Close_HTTP();
     bool Send_Data_IdeasChain(String token, String message);
     String Get_QIRD_DATA();
     String Get_Data_IdeasChain(byte mode, String token, String key);

private:
     const int waitingTime = 30000; // 等候 30 秒的回覆
};

#endif
