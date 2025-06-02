#include "led_effects.h"
#include <Arduino.h>

static unsigned long previousEffectMillis = 0;
static int chaserIndex = 0;
static bool blinkState = false;
static int randomLedIndex = 0;

void setupLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);
  }
}

void resetEffectState() {
    chaserIndex = 0;
    blinkState = false;
    randomLedIndex = 0;
    previousEffectMillis = millis(); 
    for(int i=0; i<NUM_LEDS; i++) {
        digitalWrite(ledPins[i], LOW);
    }
}

void runLedEffect() {
  unsigned long currentMillis = millis();
  int mappedSpeed = currentSettings.speed; 

  switch (currentSettings.effectId) {
    case 0: 
      for (int i = 0; i < NUM_LEDS; i++) {
        digitalWrite(ledPins[i], currentSettings.allOnState ? HIGH : LOW);
      }
      break;

    case 1: 
      if (currentMillis - previousEffectMillis >= mappedSpeed) {
        previousEffectMillis = currentMillis;
        digitalWrite(ledPins[chaserIndex], LOW);
        chaserIndex = (chaserIndex + 1) % NUM_LEDS;
        digitalWrite(ledPins[chaserIndex], HIGH);
      }
      break;

    case 2: 
      if (currentMillis - previousEffectMillis >= mappedSpeed) {
        previousEffectMillis = currentMillis;
        blinkState = !blinkState;
        for (int i = 0; i < NUM_LEDS; i++) {
          digitalWrite(ledPins[i], blinkState ? HIGH : LOW);
        }
      }
      break;

    case 3: 
      if (currentMillis - previousEffectMillis >= mappedSpeed) {
        previousEffectMillis = currentMillis;
        digitalWrite(ledPins[randomLedIndex], LOW); 
        randomLedIndex = random(0, NUM_LEDS);
        digitalWrite(ledPins[randomLedIndex], HIGH);
      }
      break;
  }
}