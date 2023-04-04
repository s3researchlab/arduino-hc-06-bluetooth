#include "Arduino.h"
#include "BluetoothConn.h"
#include <SoftwareSerial.h>

BluetoothConn::BluetoothConn(int rxPin, int txPin) {

  this->BTSerial = new SoftwareSerial(rxPin, txPin);  // RX TX

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  this->message = "";
  this->messageBuffer = "";

  this->BTSerial->begin(9600);
}

void BluetoothConn::begin(int speed) {
  this->BTSerial->begin(speed);
}

String BluetoothConn::read() {

  this->message = "";

  while (this->BTSerial->available() > 0) {

    char data = (char)this->BTSerial->read();

    if (data == ';') {
      this->message = messageBuffer;
      this->messageBuffer = "";
    } else {
      this->messageBuffer += data;
    }
  }

  this->message.trim();

  return this->message;
}

void BluetoothConn::send(String text) {
  this->BTSerial->print(text);
}