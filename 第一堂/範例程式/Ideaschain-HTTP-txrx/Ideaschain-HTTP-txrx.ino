#include "BC26-HTTP.h"

BC26_HTTP bc26;

byte Attrib_Mode = 1;                          // 0 -> sharedKeys ; 1 -> clientKeys
String Server_Name = "iiot.ideaschain.com.tw"; // HTTP Server 的 IP 位址
String Access_Token = "<你的 TOKEN>";          // 使用者資訊 ==> IDEAS Chain存取權杖
String Attrib_Client_String = "attributes";    // API 屬性的字串
String Attrib_Key = "TestValue";               // 屬性的 Key
int test_value = 5555;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    pinMode(PC13, OUTPUT);

    // 重置 BC26
    digitalWrite(PC13, LOW);
    delay(30);
    digitalWrite(PC13, HIGH);
    delay(3000);

    if (!bc26.BC26init())
    {
        delay(10000);
        nvic_sys_reset();
    }
    Serial.println("初始化完成....");
}

void loop()
{
    Serial.println("開始傳送資料....");
    if (bc26.Connect_HTTP_Server(Server_Name))
    {
        String dataAttrib = "/api/v1/" + Access_Token + "/" + Attrib_Client_String;
        String dataMessage = "{\"" + Attrib_Key + "\":" + String(test_value) + "}";

        if (bc26.Send_Data_IdeasChain(dataAttrib, dataMessage))
        {
            Serial.println("資料傳送成功!!");
        }
        bc26.Close_HTTP();
    }
    else
    {
        Serial.println("資料傳送失敗.....");
    }

    Serial.println("\n\n延遲 10 秒.....\n\n");
    delay(10000);

    Serial.println("開始取得資料....");
    String gData;
    if (bc26.Connect_HTTP_Server(Server_Name))
    {
        String dataAttrib = "/api/v1/" + Access_Token + "/" + Attrib_Client_String;
        gData = bc26.Get_Data_IdeasChain(Attrib_Mode, dataAttrib, Attrib_Key);
        if (gData != "Empty")
        {
            Serial.println("\n獲取 " + Attrib_Key + " 的資料為: " + gData);
        }
    }
    bc26.Close_HTTP();
    Serial.println("資料獲取成功!!");

    delay(3000);
    exit(0);
}
