//Author: Thomas Lloyd

#include <Arduino_LSM9DS1.h>

float samplecount = 0;
float time1;
float time2;

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

  Serial.print("Magnetic field sample rate = ");
  Serial.print(IMU.magneticFieldSampleRate());
  Serial.println(" uT");
  Serial.println();
  Serial.println("Magnetic Field in uT");
  Serial.println("X\tY\tZ");

}


void loop() {
  float x, y, z;
  float roll_dot, pitch_dot, yaw_dot;
  float roll, pitch, yaw;

  if (IMU.accelerationAvailable()) {
    
    IMU.readAcceleration(x, y, z);
    IMU.readGyroscope(roll_dot, pitch_dot, yaw_dot);
    IMU.readMagneticField(roll, pitch, yaw);
    if (samplecount == 0){
      time1 = 0;
      time2 = 0;
      roll = 0;
    }
    else {
      time2 = millis() - time2;
    }
//    Accelerometer range is set at [-4,+4]g -/+0.122 mg
//    Gyroscope range is set at [-2000, +2000] dps +/-70 mdps
//    Magnetometer range is set at [-400, +400] uT +/-0.014 uT
//    Accelerometer Output data rate is fixed at 104 Hz
//    Gyroscope Output data rate is fixed at 104 Hz
//    Magnetometer Output data rate is fixed at 20 Hz

    Serial.print("x,y,z: ");
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.print(z);

    Serial.print('\t');
    Serial.print('\t');
    Serial.print("roll_dot, pitch_dot, yaw_dot: ");
    Serial.print(roll_dot);
    Serial.print('\t');
    Serial.print(pitch_dot);
    Serial.print('\t');
    Serial.print(yaw_dot);

    roll = (time2*roll_dot)+roll;
    pitch = (time2*roll_dot)+roll;
    yaw = (time2*roll_dot)+roll;

    time1 = time2;
    samplecount++;

    Serial.print('\t');
    Serial.print('\t');
    Serial.print("roll, pitch, yaw: ");
    Serial.print(roll);
    Serial.print('\t');
    Serial.print(pitch);
    Serial.print('\t');
    Serial.print(yaw);
    

//    Serial.print('\t');
//    Serial.print('\t');
//    Serial.print("roll, pitch, yaw: ");
//    Serial.print(mag_x);
//    Serial.print('\t');
//    Serial.print(maf_y);
//    Serial.print('\t');
//    Serial.print(mag_z);

    Serial.println();
    
  }
}
