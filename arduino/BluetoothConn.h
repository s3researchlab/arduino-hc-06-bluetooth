#ifndef BluetoothConn_h
#define BluetoothConn_h

#include "Arduino.h"
#include <SoftwareSerial.h>

class BluetoothConn {

private:
  SoftwareSerial* BTSerial;
  String message;
  String messageBuffer;

public:
  BluetoothConn(int, int);
  void begin(int);
  String read();
  void send(String);
};

#endif