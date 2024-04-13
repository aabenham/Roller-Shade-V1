#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include <Stepper.h>

// Constants for the motor
const int stepsPerRevolution = 2048; 
// Create stepper object
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); // pins connected to IN1, IN3, IN2, IN4 on the ULN2003 driver

// Constants for the APDS-9960 sensor
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int gesture = 0;

void setup() {
  // Start the serial and I2C
  Serial.begin(9600);
  Wire.begin();

  // Motor setup
  myStepper.setSpeed(5); // Set the speed in RPM

  // Gesture sensor initialization
  if (apds.init()) {
    Serial.println("APDS-9960 initialization complete");
  } else {
    Serial.println("Something went wrong during APDS-9960 init!");
  }

  // Start running the APDS-9960 gesture sensor engine
  if (apds.enableGestureSensor(true)) {
    Serial.println("Gesture sensor is now running");
  } else {
    Serial.println("Something went wrong during gesture sensor init!");
  }
}

void loop() {
  if (apds.isGestureAvailable()) {
    gesture = apds.readGesture();
    switch (gesture) {
      case DIR_UP:
        Serial.println("UP");
        myStepper.step(stepsPerRevolution / 4); 
        delay(5000); // Motor run time
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        myStepper.step(-stepsPerRevolution / 4); 
        delay(5000); // Motor run time
        break;
    }
  }
}
