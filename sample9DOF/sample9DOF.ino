//Author: Thomas Lloyd

#include <Arduino_LSM9DS1.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
  Serial.println();

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");
  

  
}

void loop() {
  float x, y, z;
  float roll, pitch, yaw;

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    IMU.readGyroscope(roll, pitch, yaw);

    Serial.print("x,y,z: ");
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);
    
    Serial.print('\t');
    Serial.print('\t');
    Serial.print("roll, pitch, yaw: ");
    Serial.print(roll);
    Serial.print('\t');
    Serial.print(pitch);
    Serial.print('\t');
    Serial.print(yaw);
    
  }
}
