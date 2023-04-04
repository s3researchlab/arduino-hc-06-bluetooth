#include <Arduino.h>
// #include <SoftwareSerial.h>
#include "BluetoothConn.h"

const byte rxPin = 8;
const byte txPin = 9;

const byte pin1 = 3;
const byte pin2 = 4;
const byte pin3 = 5;
const byte pin4 = 6;
const byte pin5 = 7;

const byte pinPot = A5;

// rxPin connects to txPin and txPin connets to rxPin in the chip.
BluetoothConn BluetoothConn(rxPin, txPin);

String message = "";
int sensorValue = 0;

void setup() {

  pinMode(pinPot, INPUT);

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);

  Serial.begin(9600);
}

int readPotentiometer() {

  return map(analogRead(pinPot), 0, 1023, 0, 255);
}

void turnOnOff(int p1, int p2, int p3, int p4, int p5) {

  digitalWrite(pin1, p1 == 1 ? HIGH : LOW);
  digitalWrite(pin2, p2 == 1 ? HIGH : LOW);
  digitalWrite(pin3, p3 == 1 ? HIGH : LOW);
  digitalWrite(pin4, p4 == 1 ? HIGH : LOW);
  digitalWrite(pin5, p5 == 1 ? HIGH : LOW);
}

void runCommand(String command) {

  Serial.println("Command: " + command);

  if (command == "l0") {
    turnOnOff(0, 0, 0, 0, 0);
  } else if (command == "l1") {
    turnOnOff(1, 0, 0, 0, 0);
  } else if (command == "l2") {
    turnOnOff(1, 1, 0, 0, 0);
  } else if (command == "l3") {
    turnOnOff(1, 1, 1, 0, 0);
  } else if (command == "l4") {
    turnOnOff(1, 1, 1, 1, 0);
  } else if (command == "l5") {
    turnOnOff(1, 1, 1, 1, 1);
  }
}

void loop() {

  message = BluetoothConn.read();

  if (message != "") {
    runCommand(message);
  }

  sensorValue = readPotentiometer();

  BluetoothConn.send("p" + String(sensorValue));

  delay(100);
}
