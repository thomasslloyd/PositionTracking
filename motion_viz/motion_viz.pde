import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port


void setup()  {
  String portName = Serial.list()[8];
  myPort = new Serial(this, portName, 9600);
  
  size(1280, 720, P3D);
  noStroke();
  fill(204);
}

void draw()  {
  float fov = PI/3.0; 
  float cameraZ = (height/2.0) / tan(fov/2.0); 
  
  background(0);
  lights();
  perspective(fov, float(width)/float(height), cameraZ/2.0, cameraZ*2.0); 
  
  translate(width/2, height/2, 0);
  rotateX(PI/6); 
  rotateY(PI/3);
  box(160);
 
  
  while (myPort.available() > 0) {
    String inBuffer = myPort.readString();   
    if (inBuffer != null) {
      println(inBuffer);
      
      //str.substring(beginIndex, endIndex)
      //Orientation: 239.26 -17.40 -112.52
      //012345678910              
      String roll_str = inBuffer.substring(12, 18);
      String pitch_str = inBuffer.substring(19, 26);
      String yaw_str = inBuffer.substring(27, 34);
      
      int roll = Integer.parseInt(roll_str);
      int pitch = Integer.parseInt(pitch_str);
      int yaw = Integer.parseInt(yaw_str);
      
      rotateX(radians(roll)); 
      rotateY(radians(pitch));
      rotateZ(radians(yaw));
      box(160); 
    }
  }
}


/*
Integration of the gyroscope measurements provides information
about the orientation of the sensor.

After subtraction of the earth’s gravity, double integration of the
accelerometer measurements provides information about the sensor’s position. 



*/ 
