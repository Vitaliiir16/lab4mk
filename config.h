#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "NetojNet"
#define WIFI_PASSWORD "ss18031970"

#define OLED_SDA_PIN 4
#define OLED_SCL_PIN 5
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

#define LED_PIN_1 12 
#define LED_PIN_2 13 
#define LED_PIN_3 14 

#define BUTTON_EFFECT_PIN 0  
#define BUTTON_PARAM_PIN 2   

#define DEBOUNCE_DELAY 50

#define MIN_SPEED_DELAY 50 
#define MAX_SPEED_DELAY 2000

const int NUM_LEDS = 3;
const int NUM_EFFECTS = 4;

struct EffectSettings {
  int effectId;
  int speed; 
  bool allOnState;
};

#endif