/*************************************************
 * ESP32 Ultrasonic Distance Alert System
 * Author : Milad Mohseni
 * Board  : ESP32 (30-pin)
 *
 * Description:
 * -----------------------------------------------
 * This project measures distance using the
 * HC-SR04 ultrasonic sensor.
 *
 * Depending on the measured distance:
 *
 * SAFE     -> Green LED ON
 * WARNING  -> Orange LED ON
 * DANGER   -> Blue LED ON + Buzzer
 *
 * OLED displays:
 * - Live distance
 * - Current system status
 *
 *************************************************/


// -----------------------------
// LIBRARIES
// -----------------------------

#include <Wire.h>

#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>



// -----------------------------
// OLED CONFIGURATION
// -----------------------------

#define SCREEN_WIDTH 128

#define SCREEN_HEIGHT 64


// Create OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



// -----------------------------
// ULTRASONIC SENSOR PINS
// -----------------------------

const int trigPin = 5;

const int echoPin = 18;



// -----------------------------
// LED PINS
// -----------------------------

// Green LED = SAFE
const int greenLedPin = 15;

// Orange LED = WARNING
const int orangeLedPin = 2;

// Blue LED = DANGER
const int blueLedPin = 4;



// -----------------------------
// BUZZER PIN
// -----------------------------

const int buzzerPin = 14;



// -----------------------------
// VARIABLES
// -----------------------------

long duration;

float distance;



// -----------------------------
// SETUP
// -----------------------------

void setup()
{
  // Start serial monitor
  Serial.begin(115200);


  // -----------------------------
  // PIN MODES
  // -----------------------------

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);


  pinMode(greenLedPin, OUTPUT);

  pinMode(orangeLedPin, OUTPUT);

  pinMode(blueLedPin, OUTPUT);


  pinMode(buzzerPin, OUTPUT);


  // -----------------------------
  // START OLED
  // -----------------------------

  // Start I2C communication
  Wire.begin(21, 22);


  // Initialize OLED display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    // Stop everything if OLED fails
    while(true);
  }


  // Clear screen
  display.clearDisplay();


  // Text settings
  display.setTextSize(2);

  display.setTextColor(SSD1306_WHITE);


  // Initial message
  display.setCursor(10, 20);

  display.println("SYSTEM");

  display.println("READY");


  // Show on OLED
  display.display();

  delay(2000);
}



// -----------------------------
// MAIN LOOP
// -----------------------------

void loop()
{

  // -----------------------------
  // SEND TRIGGER PULSE
  // -----------------------------

  // Make sure trigger starts LOW
  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);


  // Send 10 microsecond pulse
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);



  // -----------------------------
  // READ ECHO TIME
  // -----------------------------

  // Measure pulse duration
  duration = pulseIn(echoPin, HIGH);



  // -----------------------------
  // CALCULATE DISTANCE
  // -----------------------------

  // Formula:
  // distance = time × speed of sound / 2

  distance = duration * 0.0343 / 2;



  // -----------------------------
  // PRINT TO SERIAL MONITOR
  // -----------------------------

  Serial.print("Distance: ");

  Serial.print(distance);

  Serial.println(" cm");



  // -----------------------------
  // SAFE STATE
  // -----------------------------

  // Object farther than 10 cm

  if(distance > 10)
  {
    // LEDs
    digitalWrite(greenLedPin, HIGH);

    digitalWrite(orangeLedPin, LOW);

    digitalWrite(blueLedPin, LOW);


    // Buzzer OFF
    digitalWrite(buzzerPin, LOW);


    // OLED
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0, 0);

    display.println("SYSTEM STATUS");


    display.setTextSize(2);

    display.setCursor(0, 20);

    display.println("SAFE");


    display.setTextSize(1);

    display.setCursor(0, 50);

    display.print("Distance: ");

    display.print(distance);

    display.println(" cm");


    display.display();
  }



  // -----------------------------
  // WARNING STATE
  // -----------------------------

  // Object between 5 and 10 cm

  else if(distance > 5 && distance <= 10)
  {
    // LEDs
    digitalWrite(greenLedPin, LOW);

    digitalWrite(orangeLedPin, HIGH);

    digitalWrite(blueLedPin, LOW);


    // Buzzer OFF
    digitalWrite(buzzerPin, LOW);


    // OLED
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0, 0);

    display.println("SYSTEM STATUS");


    display.setTextSize(2);

    display.setCursor(0, 20);

    display.println("WARNING");


    display.setTextSize(1);

    display.setCursor(0, 50);

    display.print("Distance: ");

    display.print(distance);

    display.println(" cm");


    display.display();
  }



  // -----------------------------
  // DANGER STATE
  // -----------------------------

  // Object closer than 20 cm

  else
  {
    // LEDs
    digitalWrite(greenLedPin, LOW);

    digitalWrite(orangeLedPin, LOW);

    digitalWrite(blueLedPin, HIGH);


    // Turn buzzer ON
    digitalWrite(buzzerPin, HIGH);


    // OLED
    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0, 0);

    display.println("SYSTEM STATUS");


    display.setTextSize(2);

    display.setCursor(0, 20);

    display.println("DANGER");


    display.setTextSize(1);

    display.setCursor(0, 50);

    display.print("Distance: ");

    display.print(distance);

    display.println(" cm");


    display.display();
  }



  // -----------------------------
  // SMALL DELAY
  // -----------------------------

  delay(200);
}