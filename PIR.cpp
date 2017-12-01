#include <PIR.h>

#ifdef PIR_DEBUG
#define PIR_DEBUG_PRINT(String) (Serial.print(String))
#define PIR_DEBUG_PRINTLN(String) (Serial.println(String))
#endif

#ifndef PIR_DEBUG
#define PIR_DEBUG_PRINTLN(String)
#endif

PIR::PIR(uint8_t _pin, void (*callBackFunction)(bool)) {
  this->pin = _pin;
  this->callBackFunction = callBackFunction;
  this->state = false;
  this->calibrationTime = 20;
  this->lowMillis = 0;
  this->lowThreshold = 5000;
}

PIR::~PIR() { PIR_DEBUG_PRINTLN("Deleting Pir Object"); }

void PIR::begin() {
  pinMode(pin, INPUT);

  // Calibrate/stabilize sensor
  PIR_DEBUG_PRINTLN("calibrating sensor");
  for(int i = 0; i < calibrationTime; i++) {
    PIR_DEBUG_PRINT(".");
    delay(1000);
  }

  PIR_DEBUG_PRINTLN(" done");
  delay(50);
}
bool setLowMillis = false;
void PIR::handle() {
  bool tmpState = digitalRead(this->pin);
  
  if (tmpState != state) {
    state = tmpState;
    setLowMillis = state;
    PIR_DEBUG_PRINTLN("PIR State: " + String(state) + " " + millis());
    Execute_CallBackFunction();
  }

  // needed? esp8266 specific?
  //delay(500);
}