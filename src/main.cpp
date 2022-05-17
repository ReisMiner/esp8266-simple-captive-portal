#include <Arduino.h>
#include "captive.h"

void setup() {
  Serial.begin(9600);
  Serial.println();
  setupCaptive();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}