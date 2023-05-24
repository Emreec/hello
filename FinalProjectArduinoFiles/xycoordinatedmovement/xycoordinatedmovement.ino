#include <AccelStepper.h>
#include <SCServo.h>
///////////////////////////////////////STEPPER MOTORS/////////////////////////////////////
// Define the pins connected to the drivers
#define DIR_PIN 4
#define STEP_PIN 5
#define ENABLE_PIN 9

#define DIR_PIN2 2
#define STEP_PIN2 3
#define ENABLE_PIN2 8

// Define the maximum speed and acceleration of the stepper motors
#define MAX_SPEED 10000
#define ACCELERATION 20000
#define ACCELERATION2 1000

// Define the number of steps needed to move the motor one revolution
#define STEPS_PER_REV 200

// Create a new AccelStepper objects
AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN2, DIR_PIN2);

bool runOnce = true;
///////////////////////////////////////STEPPER MOTORS/////////////////////////////////////
///////////////////////////////////////SERVO MOTORS/////////////////////////////////////
SMS_STS st;
// the uart used to control servos.
// GPIO 18 - S_RXD, GPIO 19 - S_TXD, as default.
#define S_RXD 18
#define S_TXD 19
///////////////////////////////////////SERVO MOTORS/////////////////////////////////////

void setup() {
  ///////////////////////////////////////STEPPER MOTORS/////////////////////////////////////
  // Set the enable pins as outputs
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(ENABLE_PIN2, OUTPUT);

  // Enable the drivers
  digitalWrite(ENABLE_PIN, LOW);
  digitalWrite(ENABLE_PIN2, LOW);

  // Set the maximum speed and acceleration of the stepper motors
  stepper1.setMaxSpeed(MAX_SPEED);
  stepper1.setAcceleration(ACCELERATION);

  stepper2.setMaxSpeed(MAX_SPEED);
  stepper2.setAcceleration(ACCELERATION2);
  ///////////////////////////////////////STEPPER MOTORS/////////////////////////////////////
  ///////////////////////////////////////SERVO MOTORS/////////////////////////////////////
  Serial.begin(115200);
  //Servo1
  Serial1.begin(1000000);
  st.pSerial = &Serial1;
  ///////////////////////////////////////SERVO MOTORS/////////////////////////////////////
  float firstShelfX = 1.3;
  float firstShelfY = 19;
  
  float secondShelfX = 15;
  float secondShelfY = 19;

  float thirdShelfX = 28;
  float thirdShelfY = 19;

  float fourthShelfX = 1.3;
  float fourthShelfY = 4;

  float fifthShelfX = 15;
  float fifthShelfY = 4;

  float sixthShelfX = 28;
  float sixthShelfY = 4;

  float uFirstShelfX = 49;
  float uFirstShelfY = 19;

  float uSecondShelfX = 62;
  float uSecondShelfY = 19;

  float upsideMovement = 2;

//Stepper1 == X motor 
//Stepper2 == Y motor

  int modbusarray[5] = [0,0,0,0,0];
//[0] == whether the operation is loading or unloading

}

void loop() {

  //For unloading operations 
  //1st shelf
  if(modbusarray[0] == 0){
    if(modbusarray[1] == 1){
      stepper1.move(firstShelfX * STEPS_PER_REV);
      while(stepper1.distanceToGo()!=0){
        stepper1.run();
      }
      stepper2.move(firstShelfY * STEPS_PER_REV);
      while(stepper2.distanceToGo()!=0){
        stepper2.run();
      }
      st.WritePosEx(1,0, 3400, 50); // ID , position , speed , acceleration // position will be decided // 
      //instant movement of y motor
      stepper2.move(upsideMovement * STEPS_PER_REV);
      while(stepper2.distanceToGo()!=0){
        stepper2.run();
      }
      stepper2.move(-upsideMovement * STEPS_PER_REV);
      while(stepper2.distanceToGo()!=0){
        stepper2.run();
      }
    }
    else if (modbusarray[1] == 2){
      return 0;
    }
  }  
  

}

  
  

