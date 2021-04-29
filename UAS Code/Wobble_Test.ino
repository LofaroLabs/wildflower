/**
 * Suspended on it's x-axis (forward/backward) with a free range of rotation about said
 * axis, this program should repeatedly make the drone tilt so that it rolls 45 degrees to
 * the right, then after a brief period tilt so that it is rolled 45 degrees to the left.
 */
#include "WildFlowerUAS.h"

UAS_MotorController MC = UAS_MotorController();
SENSORS sense = SENSORS();
long counter = 0;


// CHANGE THESE FOR TESTING /////////////////////////////////////////////////////////

int BBorPID = 0; // set to 1 for PID mode, set to 0 for bang-bang mode.
                 // For bang-bang mode, may need to lower the lift force.
                 
float angle = 45; // This test will periodically swap between the positive and negative number of this angle,
                  // and a third phase where it will stay level.
                  
long phase_duration = 1000 * 10; // How long it stays in a specific angle. Feel free to extend or decrease
                                 // to make testing easier.

/////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  sense.Initialize();
  MC.Initialize();

  // If it's not actually ascending, try increasing this a bit. Setting it higher will increase the lift force that 
  // each rotor will give by a fixed amount, but may make our change in roll (angular velocity) slower.
  // This is because there is now more force from the rotors on the side opposite of the direction we're rolling,
  // resisting the roll.
    
  MC.SetLiftForce(20);
  //MC.SetUASWeight(number);
  //MC.SetMaxThrust(number);
  
}

void loop() {

  if (counter < phase_duration){
    digitalWrite(13, HIGH);
    // Roll right...
    MC.SetUASOrientation(angle, 0, 0, BBorPID);
  } else if (counter < phase_duration * 2){
    digitalWrite(13, LOW);
    // Roll left...
    MC.SetUASOrientation(-angle, 0, 0, BBorPID);
  } else {
    // Stay level...
    MC.SetUASOrientation(0, 0, 0, BBorPID);
  }
  
  MC.SpinMotors();
  
  counter++;
  if (counter > phase_duration * 3) counter = 0;
  Serial.println(counter);
}
