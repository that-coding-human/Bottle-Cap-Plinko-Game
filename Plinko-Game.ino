/* Plinko-Game Arduino Sketch
Copyright (c) 2021
Author: Nico Schwarz
Github Repository: ( https://github.com/that-coding-human/Bottle-Cap-Plinko-Game )
 
Project for an arduino based bottle cap plinko pame with a snack rewarding dispenser, driven by a stepper motor. 
This file is copyright under the version 1.2 (only) of the EUPL.
Please see the LICENSE file for your rights under this license.
*/

#define Step 3
#define Dir 4
#define Sleep 8

// We use Microstepping, as it makes the motor run smoother, and we still have enough torque.
// You can chose to not use Microstepping to have more torque if required. You will
#define MS1 7
#define MS2 6
#define MS3 5

#define LDETECT 9 // Defining the Laser Detection Pin

void setup() {
  Serial.begin(9600); // This has been fast enough for even fast falling bottle caps.
  pinMode(LDETECT, INPUT); // Setting up the Detection pin
  pinMode(Step, OUTPUT); // Setting up the Pin for the Stepper
  pinMode(MS1, OUTPUT);  // Setting up Microstep1 Pin
  pinMode(MS2, OUTPUT);  // Setting up Microstep2 Pin
  pinMode(MS3, OUTPUT);  // Setting up Microstep3 Pin
  pinMode(Dir, OUTPUT); //Setting Direction Pin
  pinMode(13, OUTPUT);  // For direct visual Feedback we set up the internal Arduino LED
  pinMode(Sleep, OUTPUT);  // We use the Sleep Pin to set the Motor and Driver in Sleep State if not used
  digitalWrite(Sleep, HIGH);  // We start with the driver asleep.
  delay(2000); // A short delay for giving the driver enough time to settle
}

void loop() {
  int detected = digitalRead(LDETECT);//Here we read the input from the laser sensor
  if( detected == LOW) // If the sensor goes LOW, this means something passed the beam
  {
    digitalWrite(Sleep, HIGH); // We wake up the driver
    digitalWrite(MS1, HIGH); // Enabling Microstepping1 at the driver
    digitalWrite(MS2, HIGH); // Enabling Microstepping2 at the driver
    digitalWrite(MS3, HIGH); // Enabling Microstepping3 at the driver
    digitalWrite(13,HIGH); // This lights up the Arduino LED to have a visual representation that we detected a Laser interruption. Very useful for debugging.
    delay(1500); // Wait a second and a half in order to give the player time to cheer, and switch to looking at the dispenser
    for (int i = 0; i <= 1500; i++) {
      // This loop performs 1500 (Micro)Steps of the Motor. One Step is the cycle of HIGH and LOW
      // Assuming a normal bipolar nema17 stepper motor, 200 Steps is one 360 degree turn.
      // With Microstepping fully enabled every step is split into 256 microsteps.
      // The number of turns is responsible for the amount of snacks disposed. Adjust this value as you please.
      // By doing several tries I figured out that 1500 Microsteps dispense a good amount of snacks from my dispenser. 
      // This might vary depending on your dispenser, snacks and taste.
      digitalWrite(Step,HIGH); 
      delayMicroseconds(900); // This, and the next delay in Microseconds determines how fast the steps get executed and thus how fast your motor turns
      digitalWrite(Step,LOW);
      delayMicroseconds(900); // I have chosen 900 Microseconds in combination with Microstepping, as I wanted my dispenser to dispense the snacks slowly.
      // Adjust the delay as you see fit for your dispenser. 
      // If you disable Microstepping and do full stepps, you need to increase the delay of each step, as your motor turns a full step with each loop, not one Microstep.
    }
    digitalWrite(13,LOW); //When the action sequence of turning the motor ended, we turn the internal Arduino LED down again to have a visual hint that the loop ended. Useful for debugging.
    digitalWrite(MS1, LOW); // Disabling Microstepping1 at the driver
    digitalWrite(MS2, LOW); // Disabling Microstepping2 at the driver
    digitalWrite(MS3, LOW); // Disabling Microstepping3 at the driver
    delay(500); // We wait one second before we enter the detection loop again. Maybe this time can be decreased.
  }else{
    // The else part runs every loop, when nothing just passed the beam and pulled "detected" to LOW
    digitalWrite(13,LOW);  // Making sure the LED is turned off. This is a bit redundant. Remove it if it offends you.
    digitalWrite(Sleep, LOW);     // I had trouble with one of my drivers if I did not make sure to always have the Sleep Pin on Low here. 
                                  // Maybe a bug. Even though this looks redundant, it resolved my issue with one of my driver boards, so I leave it here. 
  }
}
