/*
模擬運行 30 秒後，進入待機模式 30 秒
*/

#include <STM32Sleep.h>
#include <RTClock.h>

RTClock rt(RTCSEL_LSE);
long int alarmDelay = 30;

void setup()
{
    // 從 Standby 待機模式喚醒會執行 setup()
    delay(30000);
    sleepAndWakeUp(STANDBY, &rt, alarmDelay);
}

void loop() {} // 這裡永遠不會執行
