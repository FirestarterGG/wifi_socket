#include "main.h"

// Функция настройки
void setup()
{
    Serial.begin(115200);

    WiFi.hostname(HOST_NAME); // Задание имени устройства
    WiFi.begin(SSID, PASSWORD);
    WiFi.mode(WIFI_STA); // Отключение режима точки доступа. Варианты: WIFI_AP, WIFI_STA, WIFI_AP_STA

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println((String) "[  Connecting to \"" + SSID + "\"  ]");
    }

    Serial.println((String) "\n[  Connected to \"" + SSID + "\"  ]\n");
    Serial.print((String) "------> IP address of this device: [  ");
    Serial.print(WiFi.localIP());
    Serial.println("  ] <------");
}


// Функция основного цикла исполнения
void loop()
{
    // Проверка статуса подключения
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;

        http.begin(SERVER_URL);

        int httpCode = http.GET();

        // Проверка кода ответа HTTP
        if (httpCode > 0)
        {
            // Парсинг JSON с ответа
            const size_t bufferSize = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
            DynamicJsonBuffer jsonBuffer(bufferSize);
            JsonObject &root = jsonBuffer.parseObject(http.getString());

            // Получаемые параметры из JSON
            const char *name = root["name"];
            const char *ip = root["ip"];
            const bool status = root["status"];

            // Вывод данных на монитор порта
            Serial.println((String) "\n----- RESPONSE FROM [ " + SERVER_URL + " ] -----");
            Serial.println((String) "[  Name  ]: " + name + "\n[  IP  ]: " + ip + "\n[  Status  ]: " + status);

            if (status == true)
            {
                digitalWrite(RELAY_PIN, LOW);
            }
            else if (status == false)
            {
                digitalWrite(RELAY_PIN, HIGH);
            }
        }

        http.end(); // Закрытие соединения
    }

    // Задержка запроса
    delay(REQUEST_DELAY);
}
