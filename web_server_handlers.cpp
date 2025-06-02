#include "web_server_handlers.h"
#include "file_system.h"    
#include "oled_display.h"   
#include "led_effects.h" 
#include <Arduino.h>

void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>LED FX Controller</title>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body{font-family: Arial, sans-serif; background-color: #f0f0f0; color: #333; margin: 20px;}";
  html += "h1{color: #007bff;}";
  html += "form{background-color: #fff; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1);}";
  html += "label{display: block; margin-top: 10px; font-weight: bold;}";
  html += "select, input[type=range], input[type=submit], input[type=checkbox]{width: calc(100% - 22px); padding: 10px; margin-top: 5px; border-radius: 4px; border: 1px solid #ddd;}";
  html += "input[type=checkbox]{width: auto; height: auto; margin-right: 5px; vertical-align: middle;}";
  html += "input[type=submit]{background-color: #007bff; color: white; font-size: 1em; cursor: pointer; border: none;}";
  html += "input[type=submit]:hover{background-color: #0056b3;}";
  html += ".range-value{font-weight: normal; margin-left:10px;}";
  html += "</style>";
  html += "<script>";
  html += "function updateSpeedValue(value) { document.getElementById('speedValue').innerText = value + '%'; }";
  html += "</script>";
  html += "</head><body>";
  html += "<h1>LED Effects Controller</h1>";
  html += "<form action='/set' method='POST'>";
  
  html += "<label for='effectId'>Select Effect:</label>";
  html += "<select id='effectId' name='effectId'>";
  for (int i = 0; i < NUM_EFFECTS; i++) {
    html += "<option value='" + String(i) + "'";
    if (i == currentSettings.effectId) {
      html += " selected";
    }
    html += ">" + effectNames[i] + "</option>";
  }
  html += "</select>";

  html += "<label for='speed'>Speed: <span id='speedValue'>" + String(map(currentSettings.speed, MAX_SPEED_DELAY, MIN_SPEED_DELAY, 0, 100)) + "%</span></label>";
  html += "<input type='range' id='speed' name='speed' min='0' max='100' value='" + String(map(currentSettings.speed, MAX_SPEED_DELAY, MIN_SPEED_DELAY, 0, 100)) + "' oninput='updateSpeedValue(this.value)'>";
  
  html += "<div style='margin-top: 15px;'>";
  html += "<input type='checkbox' id='allOnState' name='allOnState' value='1'";
  if (currentSettings.allOnState) {
    html += " checked";
  }
  html += ">";
  html += "<label for='allOnState' style='display:inline; font-weight:normal;'>All LEDs ON (for 'All On/Off' effect)</label>";
  html += "</div>";
  
  html += "<br><br><input type='submit' value='Apply Settings'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleSet() {
  if (server.hasArg("effectId")) {
    currentSettings.effectId = server.arg("effectId").toInt();
    if (currentSettings.effectId < 0 || currentSettings.effectId >= NUM_EFFECTS) {
      currentSettings.effectId = 0;
    }
  }
  if (server.hasArg("speed")) {
    int speedPercent = server.arg("speed").toInt();
    currentSettings.speed = map(speedPercent, 0, 100, MAX_SPEED_DELAY, MIN_SPEED_DELAY); 
  }
  currentSettings.allOnState = server.hasArg("allOnState");

  Serial.println("Settings updated via web:");
  Serial.print("Effect ID: "); Serial.println(currentSettings.effectId);
  Serial.print("Speed (mapped): "); Serial.println(currentSettings.speed);
  Serial.print("All On State: "); Serial.println(currentSettings.allOnState);

  resetEffectState();
  saveConfiguration();
  updateOLEDDisplay();
  
  server.sendHeader("Location","/");
  server.send(302, "text/plain", "Settings Updated. Redirecting...");
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not Found");
}

void setupWebServer(){
  server.on("/", HTTP_GET, handleRoot);
  server.on("/set", HTTP_POST, handleSet);
  server.onNotFound(handleNotFound);
  server.begin();
}