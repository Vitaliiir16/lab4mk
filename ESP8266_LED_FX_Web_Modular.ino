#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FS.h>

#include "config.h"
#include "oled_display.h"
#include "led_effects.h"
#include "file_system.h"
#include "web_server_handlers.h"
#include "button_handler.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 100000);
ESP8266WebServer server(80);


int ledPins[NUM_LEDS] = {LED_PIN_1, LED_PIN_2, LED_PIN_3}; 

EffectSettings currentSettings;
String effectNames[NUM_EFFECTS] = {"All On/Off", "Chaser", "Blink All", "Random"};

volatile bool effectButtonPressed = false;
volatile bool paramButtonPressed = false;

void setup() {
  Serial.begin(115200);
  delay(100);

  setupLEDs();
  setupButtons();
  setupOLED();
  setupFS();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20) {
    delay(500);
    Serial.print(".");
    attempt++;
  }

  String ipAddressString = "N/A";
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected");
    ipAddressString = WiFi.localIP().toString();
    Serial.print("IP address: ");
    Serial.println(ipAddressString);
  } else {
    Serial.println("\nFailed to connect to WiFi. Starting AP.");
    WiFi.mode(WIFI_AP);
    String apSSID = "LED_FX_Config_AP";
    WiFi.softAP(apSSID.c_str());
    ipAddressString = WiFi.softAPIP().toString();
    Serial.print("AP Name: ");
    Serial.println(apSSID);
    Serial.print("AP IP address: ");
    Serial.println(ipAddressString);
  }
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("LED FX Controller");
  display.setCursor(0,16);
  display.print("IP: ");
  display.println(ipAddressString);
  display.display();
  delay(1000);

  currentSettings.speed = map(currentSettings.speed, 0, 100, MAX_SPEED_DELAY, MIN_SPEED_DELAY); 

  setupWebServer();
  Serial.println("HTTP server started");

  updateOLEDDisplay(); 
}

void loop() {
  server.handleClient();

  if (effectButtonPressed) {
    effectButtonPressed = false;
    currentSettings.effectId = (currentSettings.effectId + 1) % NUM_EFFECTS;
    resetEffectState();
    saveConfiguration();
    updateOLEDDisplay();
    Serial.print("Effect changed by button to: "); Serial.println(effectNames[currentSettings.effectId]);
  }

  if (paramButtonPressed) {
    paramButtonPressed = false;
    int speedPercent = map(currentSettings.speed, MAX_SPEED_DELAY, MIN_SPEED_DELAY, 0, 100); 
    speedPercent += 10; 
    if (speedPercent > 100) {
      speedPercent = 0; 
    }
    currentSettings.speed = map(speedPercent, 0, 100, MAX_SPEED_DELAY, MIN_SPEED_DELAY);
    saveConfiguration();
    updateOLEDDisplay();
    Serial.print("Speed changed by button to (mapped): "); Serial.println(currentSettings.speed);
  }

  runLedEffect();
  
  delay(10); 
}