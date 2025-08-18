#include <SPI.h>               // Include SPI library for communication
#include <nRF24L01.h>          // Include nRF24L01 library for the radio module
#include <RF24.h>              // Include RF24 library to control the nRF24L01 module

// Create an RF24 object
RF24 radio(9, 10);             // Create a radio object with CE pin 9 and CSN pin 10

// Joystick connections
const int joystickX = A0;      // Define the analog pin for joystick VRx
const int joystickY = A1;      // Define the analog pin for joystick VRy
const int joystickButton = 2;  // Define the digital pin for joystick button (SW)

// Address for the radio channel
const byte address[6] = "00001"; // Define a unique address for this transmitter

void setup() {
  Serial.begin(9600);          // Begin serial communication at 9600 baud rate
  radio.begin();               // Initialize the RF24 radio
  radio.openWritingPipe(address); // Open a writing pipe with the defined address
  radio.setPALevel(RF24_PA_MIN);  // Set the power amplifier level to minimum
  radio.stopListening();       // Set the radio as a transmitter

  pinMode(joystickButton, INPUT_PULLUP); // Set the joystick button as an input with pullup resistor
}

void loop() {
  int xValue = analogRead(joystickX); // Read the joystick X-axis value
  int yValue = analogRead(joystickY); // Read the joystick Y-axis value
  bool buttonState = !digitalRead(joystickButton); // Read and invert the joystick button state (active low)

  // Structure to send data
  struct {
    int x;                      // X-axis value
    int y;                      // Y-axis value
    bool button;                // Button state
  } data;

  data.x = xValue;              // Assign X-axis value to data structure
  data.y = yValue;              // Assign Y-axis value to data structure
  data.button = buttonState;    // Assign button state to data structure

  // Send data
  radio.write(&data, sizeof(data)); // Send the data structure via the radio

  // Debug output to serial monitor
  Serial.print("X: ");           // Print X-axis label
  Serial.print(xValue);          // Print X-axis value
  Serial.print(" Y: ");          // Print Y-axis label
  Serial.print(yValue);          // Print Y-axis value
  Serial.print(" Button: ");     // Print button state label
  Serial.println(buttonState ? "Pressed" : "Released"); // Print button state

  delay(200);                    // Delay for stability
}
