#ifndef WEB_SERVER_HANDLERS_H
#define WEB_SERVER_HANDLERS_H

#include <ESP8266WebServer.h>
#include "config.h"

extern ESP8266WebServer server;
extern EffectSettings currentSettings;
extern String effectNames[];

void setupWebServer();
void handleRoot();
void handleSet();
void handleNotFound();

#endif