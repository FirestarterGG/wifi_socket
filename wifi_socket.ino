#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Номер управляющего пина
#define RELAY_PIN 4

// Параметры WiFi сети, к которой подключаемся
const char *ssid = "Sumrak";
const char *password = "10041997";

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA); // Отключение режима точки доступа. Варианты: WIFI_AP, WIFI_STA, WIFI_AP_STA

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting...");
  }

  Serial.print("LOCAL IP OF THE DEVICE IS: ");
  Serial.print(WiFi.localIP());
  Serial.print("\n");
}

void loop()
{
  // Проверка статуса подключения
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    http.begin("http://192.168.0.26:8000/");

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
      Serial.print("name:");
      Serial.println(name);
      Serial.print("ip:");
      Serial.println(ip);
      Serial.print("status:");
      Serial.println(status);

      if (status == 1 || status == true)
      {
        digitalWrite(RELAY_PIN, LOW);
      }
      else if (status == 0 || status == false)
      {
        digitalWrite(RELAY_PIN, HIGH);
      }
    }

    http.end(); // Закрытие соединения
  }

  // Задержка запроса
  delay(200);
}
