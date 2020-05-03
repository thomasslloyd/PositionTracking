// Basic Inertial Monitoring Unit (IMU) using Madgwick filter.
//
// To view this data, use the Arduino Serial Monitor to watch the
// scrolling angles, or run the OrientationVisualiser example in Processing.

//#include <NXPMotionSense.h>
#include <Arduino_LSM9DS1.h>
#include <MadgwickAHRS.h>
#include <Wire.h>
//#include <EEPROM.h>

Madgwick filter;

void setup() {
  Serial.begin(9600);
  
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  
  filter.begin(100);
}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  float roll, pitch, heading;

  if (IMU.accelerationAvailable()) {
    // Read the motion sensors
    //imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);
    IMU.readMagneticField(mx, my, mz);

    // Update the Madgwick filter
    filter.updateIMU(gx, gy, gz, ax, ay, az);
    //filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    Serial.print("Orientation: ");
    Serial.print(heading);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.println(roll);
  }
}
