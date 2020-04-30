import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port


void setup()  {
  String portName = Serial.list()[0];
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
      String roll_str = inBuffer.substring(0, 2);
      String pitch_str = inBuffer.substring(3, 4);
      String yaw_str = inBuffer.substring(5, 6);
      
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
