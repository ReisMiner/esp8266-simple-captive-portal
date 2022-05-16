#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <LittleFS.h>

ESP8266WebServer webServer(80);
ESP8266WebServer httpServer(1337);
ESP8266HTTPUpdateServer httpUpdater;
DNSServer dnsServer;
HTTPClient http;

IPAddress apIP(172, 217, 28, 1);
const uint16_t DNS_PORT = 53;

String responseHTML = ""
					  "<!DOCTYPE html><html lang='en'><head>"
					  "<meta name='viewport' content='width=device-width'>"
					  "<title>CaptivePortal</title></head><body>"
					  "<h1>Hello World!</h1><p>This is a captive portal example."
					  " All requests will be redirected here.</p>"
					  "<form action='/auth' method='POST'>"
					  "<input type='text' name='user'/>"
					  "<input type='submit' content='submint'/>"
					  "</form>"
					  "</body></html>";

void requireAuthentication() {
  if (!webServer.authenticate("admin", "123456"))
	return webServer.requestAuthentication();
}

bool handleFileRead(const char *path) {
  String contentType = "application/json";
  if (LittleFS.exists(path)) {
	File file = LittleFS.open(path, "r");
	webServer.streamFile(file, contentType);
	file.close();
	return true;
  }
  char fileinquestion[50];
  sprintf(fileinquestion, "handleFileRead :: File not found %s", path);
  return false;
}

void setupCaptive() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("gopfetami", "");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
	webServer.send(200, "text/html", responseHTML);
  });
  webServer.on(String(F("/auth")), HTTP_POST, []() {
	String url = webServer.arg("url");
	String user = webServer.arg("user");
	Serial.println(url);
	Serial.println(user);
  });

  webServer.on(String(F("/data")), HTTP_GET, []() {
	requireAuthentication();
  });

  webServer.begin();
}

