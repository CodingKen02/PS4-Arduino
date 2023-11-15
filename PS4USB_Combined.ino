// Turning Wheels - kennedy

#include <PS4USB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
PS4USB PS4(&Usb);

int const ena = 5;
int const in1 = 6;
int const in2 = 7;

int const enb = 2;
int const in3 = 4;
int const in4 = 3;


bool leftMotorRunning = false;
bool rightMotorRunning = false;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }
  Serial.print(F("\r\nPS4 USB Library Started"));
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  Usb.Task();

  if (PS4.connected()) {
    int leftStickY = PS4.getAnalogHat(LeftHatY);
    int rightStickY = PS4.getAnalogHat(RightHatY);

    // Define motor speeds
    int leftMotorSpeed = 255;  // Full speed
    int rightMotorSpeed = 255; // Full speed

    // Control the left motor
    if (leftStickY > 137) { // Positive Y axis
      Serial.println("Left Motor: Backword");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      analogWrite(ena, leftMotorSpeed);
    } else if (leftStickY < 117) { // Negative Y axis
      Serial.println("Left Motor: Forward");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      analogWrite(ena, leftMotorSpeed);
    } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(ena, 0);
    }

    // Control the right motor
    if (rightStickY > 137) { // Positive Y axis
      Serial.println("Right Motor: Backword");
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(enb, rightMotorSpeed);
    } else if (rightStickY < 117) { // Negative Y axis
      Serial.println("Right Motor: Forward");
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(enb, rightMotorSpeed);
    } else {
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enb, 0);
    }
  } else {
    // If the PS4 controller is not connected, stop the motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    analogWrite(ena, 0);
    analogWrite(enb, 0);
  }
}
