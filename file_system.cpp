#include "file_system.h"
#include <FS.h>
#include <Arduino.h> 
#include "oled_display.h" 

void setupFS(){
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("SPIFFS Error!");
    display.display();
    delay(2000);
  } else {
    loadConfiguration();
  }
}

void saveConfiguration() {
  File configFile = SPIFFS.open("/config.txt", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return;
  }
  configFile.println(currentSettings.effectId);
  configFile.println(currentSettings.speed);
  configFile.println(currentSettings.allOnState ? 1:0);
  configFile.close();
  Serial.println("Configuration saved (txt).");
}

void loadConfiguration() {
  if (SPIFFS.exists("/config.txt")) {
    File configFile = SPIFFS.open("/config.txt", "r");
    if (!configFile) {
      Serial.println("Failed to open config file for reading");
      currentSettings.effectId = 0;
      currentSettings.speed = (MIN_SPEED_DELAY + MAX_SPEED_DELAY) / 2;
      currentSettings.allOnState = false;
      return;
    }
    if(configFile.available()){
      currentSettings.effectId = configFile.readStringUntil('\n').toInt();
    } else {
      currentSettings.effectId = 0;
    }
    if(configFile.available()){
      currentSettings.speed = configFile.readStringUntil('\n').toInt();
    } else {
      currentSettings.speed = (MIN_SPEED_DELAY + MAX_SPEED_DELAY) / 2;
    }
    if(configFile.available()){
      currentSettings.allOnState = (configFile.readStringUntil('\n').toInt() == 1);
    } else {
      currentSettings.allOnState = false;
    }
    configFile.close();
    
    if (currentSettings.speed < MIN_SPEED_DELAY || currentSettings.speed > MAX_SPEED_DELAY) {
        currentSettings.speed = (MIN_SPEED_DELAY + MAX_SPEED_DELAY) / 2;
    }
    if (currentSettings.effectId < 0 || currentSettings.effectId >= NUM_EFFECTS) {
        currentSettings.effectId = 0;
    }

    Serial.println("Configuration loaded (txt):");
    Serial.print("Effect ID: "); Serial.println(currentSettings.effectId);
    Serial.print("Speed (raw): "); Serial.println(currentSettings.speed);
    Serial.print("All On State: "); Serial.println(currentSettings.allOnState);
  } else {
    Serial.println("Config file not found, using default settings.");
    currentSettings.effectId = 0;
    currentSettings.speed = (MIN_SPEED_DELAY + MAX_SPEED_DELAY) / 2; 
    currentSettings.allOnState = false;
    saveConfiguration();
  }
}