#ifndef PIR_H
#define PIR_H

#include <Arduino.h>

class PIR {

private:
  uint8_t pin;
  bool state;
  int calibrationTime;
  unsigned long lowMillis;
  int lowThreshold;

  void (*callBackFunction)(bool);

  inline void Execute_CallBackFunction() {
    if (callBackFunction) {
      (*callBackFunction)(getState());
    }
  }

public:
  PIR(uint8_t _pin, void (*_callBackFunction)(bool) = 0);

  void begin();
  void handle();

  virtual ~PIR();

  inline void setPin(uint8_t _pin) { this->pin = _pin; }

  inline bool getState() { return this->state; }
};

#endif