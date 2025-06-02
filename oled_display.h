#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

#include <Adafruit_SSD1306.h>
#include "config.h"

extern Adafruit_SSD1306 display;
extern EffectSettings currentSettings;
extern String effectNames[];

void setupOLED();
void updateOLEDDisplay();

#endif