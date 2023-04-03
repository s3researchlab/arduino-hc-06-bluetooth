#include <Arduino.h>
#include <SoftwareSerial.h>

const byte rxPin = 8;
const byte txPin = 9;

const byte pin1 = 2;
const byte pin2 = 3;
const byte pin3 = 4;
const byte pin4 = 5;
const byte pin5 = 6;
const byte pin6 = 7;
const byte pinPot = A5;

SoftwareSerial BTSerial(rxPin, txPin);  // RX TX

void setup() {

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);

  pinMode(pinPot, INPUT);

  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);

  BTSerial.begin(9600);
  Serial.begin(9600);
}

String message = "";
String messageBuffer = "";

void turnOffAllLeds() {

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
}

String readFromBluetooth() {

  message = "";

  while (BTSerial.available() > 0) {

    char data = (char)BTSerial.read();

    if (data == ';') {
      message = messageBuffer;
      messageBuffer = "";
    } else {
      messageBuffer += data;
    }
  }

  message.trim();

  return message;
}

void sendToBluetooth(String text) {
  BTSerial.print(text);
}

void runCommand(String command) {

  Serial.println("Command: " + command);

  turnOffAllLeds();

  if (command == "l0") {
    turnOffAllLeds();
  } else if (command == "l1") {
    digitalWrite(pin1, HIGH);
  } else if (command == "l2") {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
  } else if (command == "l3") {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
  } else if (command == "l4") {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, HIGH);
  } else if (command == "l5") {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, HIGH);
    digitalWrite(pin5, HIGH);
  } else if (command == "l6") {
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, HIGH);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, HIGH);
    digitalWrite(pin5, HIGH);
    digitalWrite(pin6, HIGH);
  }
}

void loop() {

  message = readFromBluetooth();

  if (message != "") {
    runCommand(message);
  }

  int sensorValue = analogRead(pinPot);

  sensorValue = map(sensorValue, 0, 1023, 0, 255);

  sendToBluetooth("p" + String(sensorValue));

  delay(100);
}
