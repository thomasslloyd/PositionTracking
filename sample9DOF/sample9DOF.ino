//Author: Thomas Lloyd

#include <Arduino_LSM9DS1.h>
#include <MadgwickAHRS.h>
#include <Wire.h>

Madgwick filter;

float samplecount = 0;
float time1;
float time2;
float setuptime;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Started");

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  filter.begin(100);

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

void index_helper(int roll, int pitch, int heading) {
  
  String roll_str = String(roll);
  String pitch_str = String(pitch);
  String heading_str = String(heading);

  int roll_sign;
  int pitch_sign;
  int heading_sign;

  //sign
  //value part one
  
//-----------------------------------------
//ROLL
  if (roll > 0) {
    roll_sign = 0x01; //positive value
  }
  else {
    roll_sign = 0x00; //negative value
  }
  uint8_t roll_send = abs(roll); //removing sign and making one byte
  
//-----------------------------------------
//PITCH
  if (pitch > 0) {
    pitch_sign = 0x01; //positive value
  }
  else {
    pitch_sign = 0x00; //negative value
  }
  uint8_t pitch_send = abs(pitch); //removing sign and making one byte
//-----------------------------------------
//HEADING
  if (roll > 0) {
    heading_sign = 0x01; //positive value
  }
  else {
    heading_sign = 0x00; //negative value
  }
  uint8_t heading_send = abs(heading); //removing sign and making one byte

//-----------------------------------------

  byte data[3];
  //myBytes[0] = (myInt >> 8);
  //myBytes[1] = myInt;
  data[0] = roll_sign;
  data[1] = roll_send;
  
  data[2] = pitch_sign;
  data[3] = pitch_send;
  
  data[4] = heading_sign;
  data[5] = heading_send;

  Serial.print(String(data[0]));
  Serial.print(String(data[1]));
  Serial.print(String(data[2]));
  Serial.print(String(data[3]));
  Serial.print(String(data[4]));
  Serial.print(String(data[5]));
}


void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  int roll, pitch, heading;
  
  if (IMU.accelerationAvailable()) {
    
    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);
    IMU.readMagneticField(mx, my, mz);
    Serial.println("sensors successfully read...");

     // Update the Madgwick filter
    filter.updateIMU(gx, gy, gz, ax, ay, az);
    //filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    
    if (samplecount == 0){
      time1 = 0;
      time2 = 0;
      roll = 0;
      setuptime = millis();
      Serial.print('\n');
      Serial.print("time1: ");
      Serial.println(time1);
      Serial.print("time2: ");
      Serial.print(time2);
      Serial.print('\n');
      
    }
    else if (samplecount == 1){
      time2 = millis() - setuptime;
      //Serial.print("time1: ");
      //Serial.println(time1);
      //Serial.print("time2: ");
      //Serial.println(time2);
    }
    else {
      time2 = millis()-time2;
    }
//    Accelerometer range is set at [-4,+4]g -/+0.122 mg
//    Gyroscope range is set at [-2000, +2000] dps +/-70 mdps
//    Magnetometer range is set at [-400, +400] uT +/-0.014 uT
//    Accelerometer Output data rate is fixed at 104 Hz
//    Gyroscope Output data rate is fixed at 104 Hz
//    Magnetometer Output data rate is fixed at 20 Hz

//
//    roll = (time2*roll_dot)-(time1*roll_dot)+roll;
//    pitch = (time2*pitch_dot)-(time1*pitch_dot)+pitch;
//    yaw = (time2*yaw_dot)-(time1*yaw_dot)+yaw;


    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw(); 

    Serial.print('\t');
    Serial.print('\t');
    Serial.print("roll, pitch, heading: ");
    Serial.print(roll);
    Serial.print('\t');
    Serial.print(pitch);
    Serial.print('\t');
    Serial.print(heading);
    Serial.println();

    index_helper(roll, pitch, heading);
    Serial.println();
    
    time1 = time2;
    samplecount++;
  }
}
