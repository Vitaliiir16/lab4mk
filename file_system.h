#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include "config.h"

extern EffectSettings currentSettings;

void setupFS();
void saveConfiguration();
void loadConfiguration();

#endif