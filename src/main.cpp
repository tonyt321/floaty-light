#include <Arduino.h>
#include <Logger.h>
#include "config.h"
#include "CanBus.h"


VescData vescData;
CanBus * canbus = new CanBus(&vescData);

// Declare the local logger function before it is called.
void localLogger(Logger::Level level, const char* module, const char* message);


void setup() {
  Logger::setOutputFunction(localLogger);

  Logger::setLogLevel(Logger::NOTICE);
  if(Logger::getLogLevel() != Logger::SILENT) {
      Serial.begin(115200);
  }
  
  delay(50);

  canbus->init();

  Logger::notice("Floaty", "Startup...");
}

void loop() {

  canbus->loop();

}

void localLogger(Logger::Level level, const char* module, const char* message) {
  Serial.print(F("FLOATY: ["));
  Serial.print(Logger::asString(level));
  Serial.print(F("] "));
  if (strlen(module) > 0) {
      Serial.print(F(": "));
      Serial.print(module);
      Serial.print(" ");
  }
  Serial.println(message);
}