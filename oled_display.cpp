#include "oled_display.h"
#include <ESP8266WiFi.h> 

void setupOLED() {
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("LED FX Init...");
  display.display();
  delay(500);
}

void updateOLEDDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Effect: ");
  if (currentSettings.effectId >= 0 && currentSettings.effectId < NUM_EFFECTS) {
    display.println(effectNames[currentSettings.effectId]);
  } else {
    display.println("Unknown");
  }
  display.print("Speed: ");
  display.print(map(currentSettings.speed, MAX_SPEED_DELAY, MIN_SPEED_DELAY, 0, 100)); 
  display.println("%");

  if (currentSettings.effectId == 0) {
    display.print("State: ");
    display.println(currentSettings.allOnState ? "ON" : "OFF");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    display.setCursor(0, SCREEN_HEIGHT - 8);
    display.print(WiFi.localIP());
  } else if (WiFi.getMode() == WIFI_AP) {
     display.setCursor(0, SCREEN_HEIGHT - 16); 
     display.println(WiFi.softAPSSID());
     display.setCursor(0, SCREEN_HEIGHT - 8);
     display.print(WiFi.softAPIP());
  }
  display.display();
}