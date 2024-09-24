#include "BC26-HTTP.h"

byte Rset_Count = 0; // 系統重新啟動計時器宣告

BC26_HTTP::BC26_HTTP() {}

String BC26_HTTP::Check_RevData() // 讀取收到的每一字元資料 ，彙整成一個字串
{
    /*
    讀取收到的每一字元資料 ，彙整成一個字串
     */
    String data = "";
    char c;
    while (Serial1.available())
    {
        delay(50);
        c = Serial1.read(); // 進行串列讀取
        data += c;
        if (c == '\n')
            break;
    }
    data.trim();
    return data;
}

byte BC26_HTTP::Send_ATcommand(String msg, byte stepnum)
{
    /*
    傳送 AT command ，並加以判斷
    */
    String showMsg, expectedResponse;
    Serial.println(msg);
    Serial1.println(msg);
    showMsg = Check_RevData();

    long startTime = millis();
    switch (stepnum)
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
    case 20:
        expectedResponse = "+QIOPEN: 0,0";
        break;
    default:
        return stepnum;
    }

    while (!showMsg.startsWith(expectedResponse))
    {
        showMsg = Check_RevData();
        if (showMsg.startsWith("+"))
            Serial.println(showMsg);
        if ((startTime + waitingTime) < millis())
            return stepnum;
    }
    return 99;
}

bool BC26_HTTP::BC26init()
{
    /*
    初始化 BC26
    */
    Send_ATcommand("AT+QGACT=1,1,\"apn\",\"internet.iot\"", 1);
    Send_ATcommand("AT+QCGDEFCONT=\"IP\",\"internet.iot\"", 1);
    Send_ATcommand("AT+QBAND=1,8", 1);
    Send_ATcommand("AT+QRST=1", 0);

    if (Send_ATcommand("ATE0", 1) == 99 && Send_ATcommand("AT+CGPADDR=1", 2) == 99)
    {
        return true;
    }
    return false;
}

bool BC26_HTTP::Connect_HTTP_Server(String serverName)
{
    /*
    與 HTTP 伺服器建立 TCP 連線
    */
    String command = "AT+QIOPEN=1,0,\"TCP\",\"" + serverName + "\",80,0,0";
    if (Send_ATcommand(command, 20) != 99)
        return false;
    delay(100);
    return true;
}

bool BC26_HTTP::Close_HTTP()
{
    /*
    關閉 HTTP 連線
    */
    if (Send_ATcommand("AT+QICLOSE=0", 1) != 99)
        return false;
    delay(100);
    return true;
}

bool BC26_HTTP::Send_Data_IdeasChain(String token, String message)
{
    /*
    POST 資料到 IdeasChain
    */
    String sendCheck = "";
    Serial.println("AT+QISEND=0");
    Serial1.println("AT+QISEND=0");

    sendCheck = Check_RevData();
    while (!sendCheck.startsWith(">"))
    {
        sendCheck = Check_RevData();
    }

    Serial.println("POST " + token + " HTTP/1.1");
    Serial1.println("POST " + token + " HTTP/1.1");
    Serial.println("Host: iiot.ideaschain.com.tw");
    Serial1.println("Host: iiot.ideaschain.com.tw");
    Serial.println("Content-Type: application/json");
    Serial1.println("Content-Type: application/json");
    Serial.println("Content-Length:" + String(message.length()));
    Serial1.println("Content-Length:" + String(message.length()));
    Serial1.println();
    Serial.println(message);
    Serial1.print(message);
    Serial1.print("\x1A");

    sendCheck = Check_RevData();
    while (!sendCheck.startsWith("SEND OK"))
    {
        sendCheck = Check_RevData();
    }

    sendCheck = Check_RevData();
    while (!sendCheck.startsWith("+QIURC: \"recv\",0"))
    {
        sendCheck = Check_RevData();
    }
    return true;
}

String BC26_HTTP::Get_QIRD_DATA()
{
    /*
    取得回傳資料
    */
    String response = "";
    Serial.println("AT+QIRD=0,512");
    Serial1.println("AT+QIRD=0,512");

    while (!Serial1.available())
        ;
    while (Serial1.available())
    {
        response = Serial1.readString();
    }

    if (response.length() > 30)
    {
        Serial.println(response);
        return response;
    }
    return "Empty";
}

String BC26_HTTP::Get_Data_IdeasChain(byte mode, String token, String key)
{
    /*
    獲取 IdeasChain 資料
    */
    String sendCheck = "";
    Serial.println("AT+QISEND=0");
    Serial1.println("AT+QISEND=0");

    sendCheck = Check_RevData();
    while (!sendCheck.startsWith(">"))
    {
        sendCheck = Check_RevData();
    }

    if (mode == 0)
    {
        Serial.println("GET " + token + "?sharedKeys=" + key + " HTTP/1.1");
        Serial1.println("GET " + token + "?sharedKeys=" + key + " HTTP/1.1");
    }
    else
    {
        Serial.println("GET " + token + "?clientKeys=" + key + " HTTP/1.1");
        Serial1.println("GET " + token + "?clientKeys=" + key + " HTTP/1.1");
    }

    Serial.println("Host: iiot.ideaschain.com.tw");
    Serial1.println("Host: iiot.ideaschain.com.tw");
    Serial1.print("\r\n\r\n\x1A");

    sendCheck = Check_RevData();
    while (!sendCheck.startsWith("SEND OK"))
    {
        sendCheck = Check_RevData();
    }

    sendCheck = Check_RevData();
    while (!sendCheck.startsWith("+QIURC: \"recv\",0"))
    {
        sendCheck = Check_RevData();
    }
    return Get_QIRD_DATA();
}
