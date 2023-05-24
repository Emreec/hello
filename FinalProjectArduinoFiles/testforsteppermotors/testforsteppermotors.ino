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

// put your setup code here, to run once:
#define MAX_SPEED 50000
#define ACCELERATION 50000
#define ACCELERATION2 1000

#define STEPS_PER_REV 200

#include <SCServo.h>
SMS_STS st;
#define S_RXD 18
#define S_TXD 19
AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN2, DIR_PIN2);
bool runOnce = true;
void setup() {
 
  
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
}

void loop() {
  if(runOnce == true){
    // put your main code here, to run repeatedly:
  stepper1.move((0)* STEPS_PER_REV);
    while(stepper1.distanceToGo()!=0){
      stepper1.run();
    }
    
    stepper2.move((-10)* STEPS_PER_REV);
    while(stepper2.distanceToGo()!=0){
      stepper2.run();
    }
  
    
   
     // take tong back
    
  runOnce = false;
  }
}
 

