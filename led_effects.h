#ifndef LED_EFFECTS_H
#define LED_EFFECTS_H

#include "config.h"

extern EffectSettings currentSettings;
extern int ledPins[]; 

void setupLEDs();
void runLedEffect();
void resetEffectState();

#endif