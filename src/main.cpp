#include <Arduino.h>
#include "captive.h"

void setup() {
  Serial.begin(9600);
  Serial.println();
  digitalWrite(2, 1);
  setupCaptive();
  digitalWrite(2, 0);
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}