
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>


// Замените на свои данные
const char* ssid     = "Galaxy A51292C";
const char* password = "5112787e";

const int reedSwitchPin = 4;
const int ledPin = 2;

const char* mqtt_server = "34.154.152.150";      // например, "192.168.1.100"

const char* mqtt_user = "eldor";        // логин MQTT
const char* mqtt_pass = "12345";        // пароль MQTT
const char* topic = "door/status";

WiFiClient espClient;
PubSubClient client(espClient);

int lastSensorState = -1;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Подключение к Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi подключён. IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Подключение к MQTT...");
    // добавляем логин и пароль
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("Успешно подключено к MQTT");
    } else {
      Serial.print("Ошибка подключения, rc=");
      Serial.print(client.state());
      Serial.println(". Повтор через 5 сек...");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(reedSwitchPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();  // ← ОБЯЗАТЕЛЬНО

  int sensorValue = digitalRead(reedSwitchPin);

  if (sensorValue != lastSensorState) {
    lastSensorState = sensorValue;

    if (sensorValue == HIGH) {
      digitalWrite(ledPin, HIGH);
      client.publish(topic, "Дверь ЗАКРЫТА");
      Serial.println("Магнит рядом (замкнуто)");
    } else {
      digitalWrite(ledPin, LOW);
      client.publish(topic, "Дверь ОТКРЫТА");
      Serial.println("Магнит далеко (разомкнуто)");
    }
  }

  delay(50); // антидребезг
}
