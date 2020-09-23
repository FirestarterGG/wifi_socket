#ifndef MAIN_H
#define MAIN_H

// Библиотеки для работы с ESP и кодовой базой Arduino
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// Глобольные настройки
#define RELAY_PIN 4                                 // Номер управляющего пина
#define SSID "Sumrak"                               // Имя WiFi сети, к которой подключаемся
#define PASSWORD "10041997"                         // Пароль от WiFi сети 
#define SERVER_URL "http://192.168.0.26:8000/"      // Адрес backend сервера
#define HOST_NAME "Smart Socket: MAIN"              // Имя устройства в сети
#define REQUEST_DELAY 500                           // Задержка отправки запросов на backend (мс)

#endif