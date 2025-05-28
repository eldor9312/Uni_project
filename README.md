# 🚪 ESP32 Door Status Notifier with MQTT and Telegram

This project uses an ESP32 connected to a magnetic reed switch to detect whether a door is open or closed. It sends the status to an MQTT broker, and a Python bot running on a server listens for changes and forwards updates to a Telegram chat.

---

## 🧰 What You Need

- ESP32 development board
- Reed (СМК) magnetic switch
- 10kΩ resistor
- Breadboard + jumper wires
- MQTT broker (e.g. Mosquitto on VM, or MQTTX GUI broker)
- Wi-Fi connection
- Google Cloud VM or any server with Python
- Telegram Bot Token
- Your Telegram chat ID

---

## 🛠 1. Wiring the ESP32

- Reed switch:
  - One contact → GPIO 4 (D4) on ESP32
  - One contact → GND
- 10kΩ pull-up resistor between GPIO 4 and 3.3V

---

## 🔌 2. Flash the ESP32

1. Open VS Code with PlatformIO
2. Load the ESP32 sketch that connects to Wi-Fi, reads the reed switch, and publishes `"Дверь ЗАКРЫТА"` or `"Дверь ОТКРЫТА"` to the topic `door/status`
3. Add your Wi-Fi and MQTT credentials to the code
4. Flash to ESP32 and monitor serial output to confirm it connects and publishes

---

## 🛰 3. Set Up MQTT Broker

You can use:
- MQTTX GUI broker, OR
- Mosquitto on Google Cloud VM (port 1883 open)

Ensure:
- Broker is running and reachable from ESP32 IP
- You have the username, password, and IP (use public IP if hosted)

---

## 💬 4. Telegram Bot

1. In Telegram, talk to [@BotFather](https://t.me/BotFather)
2. Create a bot → save the token
3. Send a message to your bot so it knows you
4. Use a script or bot like [@userinfobot](https://t.me/userinfobot) to get your Telegram chat ID

---

## 🧠 5. Python Listener Script (on VM or PC)

1. Make sure Python 3.11 is installed
2. Install requirements:

```bash
sudo apt update
sudo apt install python3.11-venv python3-pip -y
python3 -m venv venv
source venv/bin/activate
pip install paho-mqtt python-telegram-bot
