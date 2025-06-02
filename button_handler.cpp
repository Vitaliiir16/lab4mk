#include "button_handler.h"
#include <Arduino.h>

static unsigned long lastEffectDebounce = 0;
static unsigned long lastParamDebounce = 0;

void IRAM_ATTR handleEffectButtonIRQ() {
  if (millis() - lastEffectDebounce > DEBOUNCE_DELAY) {
    effectButtonPressed = true;
    lastEffectDebounce = millis();
  }
}

void IRAM_ATTR handleParamButtonIRQ() {
  if (millis() - lastParamDebounce > DEBOUNCE_DELAY) {
    paramButtonPressed = true;
    lastParamDebounce = millis();
  }
}

void setupButtons(){
  pinMode(BUTTON_EFFECT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PARAM_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(BUTTON_EFFECT_PIN), handleEffectButtonIRQ, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PARAM_PIN), handleParamButtonIRQ, FALLING);
}