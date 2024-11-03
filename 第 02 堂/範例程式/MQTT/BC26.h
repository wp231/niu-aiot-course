#ifndef BC26_H
#define BC26_H

#include <Arduino.h>

class BC26
{
public:
    BC26();
    bool initialize();
    byte sendATCommand(String msg, byte stepNum);
    String checkReceivedData();

private:
    int waitingTime = 30000; // 等候 30 秒的回覆
};

#endif // BC26_H
