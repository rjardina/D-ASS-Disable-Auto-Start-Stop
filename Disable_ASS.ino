/**
D-ASS (Disable Auto Start-Stop)
By Ryan Jardina ~ KF5EKB
This is Open Source & is release under the GNU GPL v2 or v3 (which ever you like)

Made this to disable the engine's auto start-stop in my company's truck
without modifing it other than a small piece of double sided tape.
If my boss doesn't like it tell him to fire me!

All is needed is a power source that is only on with the engine on
USB port / cigar lighter port & shuts off when engine is off.

I didn't have the above requirments BUT my truck's USB turns on 15 seconds
after unlocking it & I put a 60 second "InitialDelay". Morethan enough time
for me to jump in & turn over the engine.

Theory of operations:
  1) D-ASS is off when the driver gets in the automobile
  2) Engine turns on, D-ASS powers on from a power source only when the engine is on
  3) D-ASS turns servo to press the Auto Start-Stop button to diable it.
  4) Servo gos back to home position.
Adjusting:
  If button on digital 3 is held down the POT can adjust the position. To push the "ASS" button

Parts Used:
  Arduino (Nano)
  Small servo motor
  POT = potentiometer (used 100K) anything above 1K & lessthan <100K should work
  Button
  (These parts are less than $10 in 2025 money & you could omit the last two if you change the code)

Wiring:
    1) Power & GND on both Servo & POT (1&3) goto their respeceted places
    2) Wiper from POT goes to "A0"
    3) Signal wire from servo goes to "D9"
    4) Button goes from "D3" to GND
**/

#include <Servo.h> // Servo Library

Servo servo; // Creats an object named "servo" to control the servo

int InitialDelay = 60; // Initial delay (in seconds) after Arduino gets power
int Press = 1; // How long to press the button for

void ScaleServoToPot() {
  servo.write(map(analogRead(A0), 0, 1024, 0, 180)); }
    // Scales the analog input to the servo output

void setup() {
  pinMode(3, INPUT_PULLUP); // Enables Pin 3
  servo.attach(9);  // Attaches the servo on pin 9 to the servo objectư
  while (millis() < InitialDelay * 1000) { };  // do nothing for a moment
  while (millis() < InitialDelay * 1000 + Press * 1000) { ScaleServoToPot(); } }
    // Holds the position to press the ASS button for about a seconds

void loop() {
  servo.write(90); // Puts the server back into the 90 degree / home position 
  while (!digitalRead(3)) { ScaleServoToPot(); } }
    // While button/input 3 is shorted to ground. This is used to adjusted.