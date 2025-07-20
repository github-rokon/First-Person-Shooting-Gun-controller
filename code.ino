#include <Wire.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32 Keyboard", "MyCompany", 100);

// Define the pins for the switches
const int switchPins[9] = {14, 19, 21, 22, 23, 15, 4, 18, 5}; // GPIO5 added twice
const char keys[9] = {'S', 'R', 'A', 'J', 'C', 'W', 'A', 'S', 'D'}; // GPIO5 now prints 'A'

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  // Initialize the switch pins as inputs
  for (int i = 0; i < 9; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }
}

void loop() {
  if (bleKeyboard.isConnected()) {
    for (int i = 0; i < 9; i++) {
      checkButton(i);
    }
  }
}

void checkButton(int index) {
  if (digitalRead(switchPins[index]) == LOW) { // Assuming active LOW switches
    Serial.print("Sending '");
    Serial.print(keys[index]);
    Serial.println("'");
    bleKeyboard.print(keys[index]);
    delay(500); // Debounce delay
  }
