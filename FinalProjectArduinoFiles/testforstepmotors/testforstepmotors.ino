#include <AccelStepper.h>

// Define the pins connected to the driver
#define DIR_PIN 4
#define STEP_PIN 5
#define ENABLE_PIN 9

// Define the maximum speed and acceleration of the stepper motor
#define MAX_SPEED 10000
#define ACCELERATION 1500
// Define the number of steps needed to move the motor one revolution
#define STEPS_PER_REV 200

// Create a new AccelStepper object
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
float inputValue = -0.1;

void setup() {
  // Set the enable pin as an output
  pinMode(ENABLE_PIN, OUTPUT);

  // Enable the driver
  digitalWrite(ENABLE_PIN, LOW);

  // Set the maximum speed and acceleration of the stepper motor
  stepper.setMaxSpeed(MAX_SPEED);
  stepper.setAcceleration(ACCELERATION);

  // Start the Serial communication
  Serial.begin(9600);

  // Wait for Serial connection to be established
  while (!Serial) {
    delay(100);
  }

  // Prompt the user to enter the desired input value
  Serial.println("Enter the input value:");
}

void loop() {
  // Check if a new input value is available
  if (Serial.available() > 0) {
    // Read the input value from Serial
    inputValue = Serial.parseFloat();
    // Prompt the user to enter the next input value
    Serial.println("Enter the input value:");
  }

  stepper.move(inputValue * STEPS_PER_REV);

  // Wait for the motor to reach its destination
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }

  // Move the stepper motor 100 steps clockwise
  delay(1000);
}
