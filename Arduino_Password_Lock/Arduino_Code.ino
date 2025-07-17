#include <Keypad.h>
#include <Servo.h>

// Keypad settings
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // R1–R4
byte colPins[COLS] = {5, 4, 3, 2}; // C1–C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Servo setup
Servo myservo;

// I/O pins
const int greenLED = 11;
const int redLED = 12;
const int buzzer = 13;
const int servoPin = 10;

// Password setup
String password = "1234";  // ✅ YOUR CODE
String input = "";

void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin);
  myservo.write(120); // Start at 0°
  
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(buzzer, LOW);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);

    if (key == '#') { // Confirm input
      if (input == password) {
        grantAccess();
      } else {
        denyAccess();
      }
      input = ""; // Reset after attempt
    } 
    else if (key == '*') {
      input = ""; // Clear input manually
    } 
    else {
      input += key;
    }
  }
}

void grantAccess() {
  Serial.println("Correct code!");
  
  // Blink green LED
  for (int i = 0; i < 3; i++) {
    digitalWrite(greenLED, HIGH);
    delay(200);
    digitalWrite(greenLED, LOW);
    delay(200);
  }

  // Move servo
  myservo.write(0);  // Rotate to 120°
  delay(2000);         // Wait 2 seconds
  myservo.write(120);    // Return to 0°
}

void denyAccess() {
  Serial.println("Wrong code!");

  // Red LED + buzzer for 2 sec
  digitalWrite(redLED, HIGH);
  tone(buzzer, 1000); // 1 kHz tone
  delay(2000);
  digitalWrite(redLED, LOW);
  noTone(buzzer);
}
