# Code Explanation

## Libraries

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
```

These libraries are used for OLED communication and graphics rendering.

* Wire.h → I2C communication
* Adafruit_GFX.h → graphics functions
* Adafruit_SSD1306.h → OLED control

---

## OLED Configuration

```cpp
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
```

Defines OLED display resolution.

---

```cpp
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
```

Creates the OLED display object using I2C communication.

---

## Ultrasonic Sensor Pins

```cpp
const int trigPin = 5;
const int echoPin = 18;
```

* TRIG sends ultrasonic pulses
* ECHO receives reflected signal timing

---

## LED Pins

```cpp
const int greenLedPin = 15;
const int orangeLedPin = 2;
const int blueLedPin = 4;
```

Each LED represents a different system state:

* Green → SAFE
* Orange → WARNING
* Blue → DANGER

---

## Buzzer Pin

```cpp
const int buzzerPin = 14;
```

Controls the active buzzer for audible alerts.

---

## Variables

```cpp
long duration;
float distance;
```

* duration → ultrasonic echo travel time
* distance → calculated distance in centimeters

---

## setup()

The setup() function runs once during startup.

### Serial Monitor

```cpp
Serial.begin(115200);
```

Starts serial communication for debugging.

---

### Pin Modes

```cpp
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
```

Configures:

* TRIG as output
* ECHO as input

---

### OLED Initialization

```cpp
Wire.begin(21, 22);
```

Starts I2C communication using:

* SDA → GPIO21
* SCL → GPIO22

---

```cpp
display.begin(SSD1306_SWITCHCAPVCC, 0x3C)
```

Initializes the OLED display using I2C address 0x3C.

---

## loop()

The loop() function runs continuously.

---

## Trigger Pulse Generation

```cpp
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
```

Sends a 10µs trigger pulse to the HC-SR04 sensor.

This starts ultrasonic transmission.

---

## Echo Timing Measurement

```cpp
duration = pulseIn(echoPin, HIGH);
```

Measures the echo pulse duration returned by the sensor.

---

## Distance Calculation

```cpp
distance = duration * 0.0343 / 2;
```

Converts echo travel time into distance.

Formula:

distance = (time × speed of sound) / 2

---

## SAFE State

```cpp
if(distance > 10)
```

Behavior:

* Green LED ON
* Buzzer OFF
* OLED displays SAFE

---

## WARNING State

```cpp
else if(distance > 5 && distance <= 10)
```

Behavior:

* Orange LED ON
* Buzzer OFF
* OLED displays WARNING

---

## DANGER State

```cpp
else
```

Behavior:

* Blue LED ON
* Buzzer ON
* OLED displays DANGER

---

## OLED Rendering

```cpp
display.clearDisplay();
display.display();
```

Updates OLED content by:

1. clearing previous frame
2. drawing new information
3. rendering updated screen

---

## Serial Monitor Output

```cpp
Serial.print(distance);
```

Prints measured distance values for debugging and verification.

---

## Delay

```cpp
delay(200);
```

Adds a small update interval between measurements.
