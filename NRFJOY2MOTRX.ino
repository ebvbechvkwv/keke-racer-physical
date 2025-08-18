#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Motor A control pins
const int AIN1 = 3;
const int AIN2 = 4;
const int PWMA = 5;

// Motor B control pins
const int BIN1 = 7;
const int BIN2 = 8;
const int PWMB = 6;            // Change PWMB to pin 6

const int STBY = 2;            // Change STBY to pin 2

RF24 radio(9, 10);             // Create a radio object with CE pin 9 and CSN pin 10
const byte address[6] = "00001"; // Define a unique address for this receiver

void setup() {
  Serial.begin(9600);          // Begin serial communication at 9600 baud rate
  radio.begin();               // Initialize the RF24 radio
  radio.openReadingPipe(0, address); // Open a reading pipe with the defined address
  radio.setPALevel(RF24_PA_MIN);  // Set the power amplifier level to minimum
  radio.startListening();      // Set the radio as a receiver

  // Initialize motor control pins
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  // Ensure motor controller is in standby mode initially
  digitalWrite(STBY, LOW);
}

void loop() {
  if (radio.available()) {     // Check if data is available to read from the radio
    struct {
      int x;                   // X-axis value
      int y;                   // Y-axis value
      bool button;             // Button state
    } data;

    radio.read(&data, sizeof(data)); // Read the data from the radio into the data structure

    // Print received values to the serial monitor
    Serial.print("Received X: ");    // Print received X-axis label
    Serial.print(data.x);            // Print received X-axis value
    Serial.print(" Y: ");            // Print received Y-axis label
    Serial.print(data.y);            // Print received Y-axis value
    Serial.print(" Button: ");       // Print received button state label
    Serial.println(data.button ? "Pressed" : "Released"); // Print received button state

    // Control Motor A based on joystick Y value
    int motorASpeed = map(data.y, 0, 1023, -255, 255); // Map joystick Y value to motor speed range

    if (motorASpeed > 0) {       // If motor speed is positive
      digitalWrite(AIN1, HIGH);  // Set AIN1 to HIGH
      digitalWrite(AIN2, LOW);   // Set AIN2 to LOW
      analogWrite(PWMA, motorASpeed); // Write the motor speed to PWMA
    } else if (motorASpeed < 0) { // If motor speed is negative
      digitalWrite(AIN1, LOW);   // Set AIN1 to LOW
      digitalWrite(AIN2, HIGH);  // Set AIN2 to HIGH
      analogWrite(PWMA, -motorASpeed); // Write the motor speed (absolute value) to PWMA
    } else {                     // If motor speed is zero
      digitalWrite(AIN1, LOW);   // Set AIN1 to LOW
      digitalWrite(AIN2, LOW);   // Set AIN2 to LOW
      analogWrite(PWMA, 0);      // Write zero speed to PWMA
    }

    // Control Motor B based on joystick X value
    int motorBSpeed = map(data.x, 0, 1023, -255, 255); // Map joystick X value to motor speed range

    if (motorBSpeed > 0) {       // If motor speed is positive
      digitalWrite(BIN1, HIGH);  // Set BIN1 to HIGH
      digitalWrite(BIN2, LOW);   // Set BIN2 to LOW
      analogWrite(PWMB, motorBSpeed); // Write the motor speed to PWMB
    } else if (motorBSpeed < 0) { // If motor speed is negative
      digitalWrite(BIN1, LOW);   // Set BIN1 to LOW
      digitalWrite(BIN2, HIGH);  // Set BIN2 to HIGH
      analogWrite(PWMB, -motorBSpeed); // Write the motor speed (absolute value) to PWMB
    } else {                     // If motor speed is zero
      digitalWrite(BIN1, LOW);   // Set BIN1 to LOW
      digitalWrite(BIN2, LOW);   // Set BIN2 to LOW
      analogWrite(PWMB, 0);      // Write zero speed to PWMB
    }

    // Take motor controller out of standby mode
    digitalWrite(STBY, HIGH);    // Set STBY to HIGH to take the motor controller out of standby mode
  }
}
