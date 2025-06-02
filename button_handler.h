#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "config.h"

extern volatile bool effectButtonPressed;
extern volatile bool paramButtonPressed;

void setupButtons();

#endif