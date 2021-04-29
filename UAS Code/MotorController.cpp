#include "Arduino.h"
#include "WildFlowerUAS.h"

// Define the pins for each motor.
#define MOTOR_BL A1
#define MOTOR_FL A2
#define MOTOR_FR A3
#define MOTOR_BR A4

// internal values
int motorSpeedBL;
int motorSpeedFL;
int motorSpeedFR;
int motorSpeedBR;

int BLCounter;
int FLCounter;
int FRCounter;
int BRCounter;

/* --- Constructor --- */
MotorController::MotorController(void)
{
  
}

/* Init Method */
int MotorController::Initialize(void)
{
  motorSpeedBL = 80;
  motorSpeedFL = 80;
  motorSpeedFR = 80;
  motorSpeedBR = 80;
  return 0;
}

float MotorController::StayAtHeight(float desiredHeight){
  sense.ReadCloseRangeLIDAR();
  sense.ReadLongRangeLIDAR();
  float closeL = Lidar.CloseRange;
  float longL = Lidar.LongRange;
  float currentHeight = longL;
  if (longL <= 100){ // Switch to the close range one - once we get down to mid range between the two's boundaries.
    currentHeight = closeL;
  }
  float error = desiredHeight - currentHeight; // positive when we need to go up, negative when we need to go down
  // For a velocity controller, we need:
  // desired velocity
  // actual velocity
  // way to set derivative of velocity (force)

}


/**
 * Takes a force that we want from each motor (in pounds/newtons) and converts it into something that the MCU
 * can read and use to switch the motors periodically (a floating percentage.)
 * If a upwards or downwards force greater than we can give is requested, set it to the max in that direction
 * and send a message to the serial communications line.
 */
int MotorController::SetMotorForces(float BL_Force, float FL_Force, float FR_Force, float BR_Force){
  float maxThrust = 10; // say its like 10 lbs
  float droneWeight = 8; // 8 lbs
  // The maximum force it can have upwards is maxThrust - droneWeight.
  // The maximum force it can have going downwards is droneWeight (our rotors don't spin backwards.)
  // The difference between these two is maxThrust.
  // In this case, 0% of maxThrust would be -8 lbs of force, 100% of maxThrust would be +2 lbs of force.
  // 
  // (-8 + 8) / 10 * 100 = 0
  // (-2 + 8) / 10 * 100 = 60
  // (0  + 8) / 10 * 100 = 80
  // (2  + 8) / 10 * 100 = 100


  // Init the percent of time each motor should be driven high.  
  float percentBL = (BL_Force + droneWeight/4) / maxThrust * 100;
  if (percentBL > 100) {
    percentBL = 100;
    Serial.print("Trying to get more force than we can muster out of motor BL!");
  }
  else if (percentBL < 0){
    percentBL = 0;
    Serial.print("Trying to drop faster than gravity will allow for side BL!");
  }

  float percentFL = (FL_Force + droneWeight/4) / maxThrust * 100;
  if (percentFL > 100) {
    percentFL = 100;
    Serial.print("Trying to get more force than we can muster out of motor FL!");
  }
  else if (percentFL < 0){
    percentFL = 0;
    Serial.print("Trying to drop faster than gravity will allow for side FL!");
  }

  float percentFR = (FR_Force + droneWeight/4) / maxThrust * 100;
  if (percentFR > 100) {
    percentFR = 100;
    Serial.print("Trying to get more force than we can muster out of motor FR!");
  }
  else if (percentFR < 0){
    percentFR = 0;
    Serial.print("Trying to drop faster than gravity will allow for side FR!");
  }
  
  float percentBR = (BR_Force + droneWeight/4) / maxThrust * 100;
  if (percentBR > 100) {
    percentBR = 100;
    Serial.print("Trying to get more force than we can muster out of motor BR!");
  }
  else if (percentBR < 0){
    percentBR = 0;
    Serial.print("Trying to drop faster than gravity will allow for side BR!");
  }
  
}

// Function that should be called in main to spin the motors in a time-sensitive manner.
int MotorController::SpinMotors(void)
{
  if (BLCounter > motorSpeedBL) digitalWrite(MOTOR_BL, LOW); // turn off for (100-BL)% of the time.
  else digitalWrite(MOTOR_BL, HIGH); // turn on for BL% of the time.
  if (FLCounter > motorSpeedFL) digitalWrite(MOTOR_FL, LOW);
  else digitalWrite(MOTOR_FL, HIGH);
  if (FRCounter > motorSpeedFR) digitalWrite(MOTOR_FR, LOW);
  else digitalWrite(MOTOR_FR, HIGH);
  if (BRCounter > BRCounter) digitalWrite(MOTOR_BR, LOW);
  else digitalWrite(MOTOR_BR, HIGH);
  
  BLCounter++;
  FLCounter++;
  FRCounter++;
  BRCounter++;
  
  // When counters reach > 100, set back to 0.
  if (BLCounter > 100) BLCounter = 0;
  if (FLCounter > 100) FLCounter = 0;
  if (FRCounter > 100) FRCounter = 0;
  if (BRCounter > 100) BRCounter = 0;
  return 0;
}

int setYaw()
{
  
}

int setRoll()
{
  
}

int setPitch()
{
  
}
