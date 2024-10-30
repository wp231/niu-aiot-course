#include "BC26.h"
#include "MQTTHandler.h"
#include "SensorHandler.h"

// BC26 實例
BC26 bc26;
MQTTHandler mqttHandler;
SensorHandler sensorHandler(PB9); // DHT11 使用 PB9 腳位

String MQTT_Server = "<SERVER>";
String MQTT_Port = "<PORT>";
String MQTT_User = "<USER>";
String MQTT_Password = "<PASSWORD>";
String MQTTtopic = "<TOPIC>";

float CorrectionTEMP = 0.0;
float CorrectionHUMI = 20.0;

void setup()
{
    Serial.begin(115200);
    Serial1.begin(115200);
    pinMode(PB6, OUTPUT);
    pinMode(PB7, OUTPUT);
    pinMode(PB8, OUTPUT);
    pinMode(PC13, OUTPUT);
    digitalWrite(PB6, HIGH);

    // Reset BC26
    digitalWrite(PC13, LOW);
    delay(30);
    digitalWrite(PC13, HIGH);
    delay(3000);

    Serial.println("開始初始化");
    if (!bc26.initialize())
    {
        delay(10000);
        nvic_sys_reset();
    }
    Serial.println("初始化完成 ....");
}

void loop()
{
    if (mqttHandler.connect(MQTT_Server, MQTT_Port, MQTT_User, MQTT_Password))
    {
        float temperature, humidity;
        if (sensorHandler.readData(temperature, humidity))
        {
            temperature = 25.0;
            humidity = 50.0;
            Serial.print("攝氏溫度：");
            Serial.print(temperature - CorrectionTEMP);
            Serial.println(" °C");
            Serial.print("環境溼度：");
            Serial.print(humidity - CorrectionHUMI);
            Serial.println(" %");

            String DHTtemp = String(temperature - CorrectionTEMP);
            String DHThumi = String(humidity - CorrectionHUMI);
            String message = "{\"Temperature\":" + DHTtemp + ",\"Humidity\":" + DHThumi + "}";

            if (mqttHandler.publish(MQTTtopic, message))
            {
                Serial.println("資料已成功發布!");
            }
        }
        else
        {
            Serial.println("讀取 DHT11 失敗");
        }
        mqttHandler.close();
    }
    else
    {
        Serial.println("MQTT 連線失敗");
    }
    delay(20000); // 根據需求調整暫停時間
}
