import processing.serial.*;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port

byte roll_sign;
byte roll_rec;  
byte pitch_sign;
byte pitch_rec;
byte heading_sign;
byte heading_rec;

int roll_int;
int pitch_int;
int heading_int;


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
  
  byte[] inBuffer = new byte[6];
     
  while (myPort.available() > 0) {    
    inBuffer = myPort.readBytes();
      //String inBuffer = myPort.readString();  
    myPort.readBytes(inBuffer);
    
    if (inBuffer != null) {
      int[] ahrs = byte_handler(inBuffer);
      print(ahrs[0]);
      print(", ");
      print(ahrs[1]);
      print(", ");
      println(ahrs[2]);
      println("---");
      println();
 
      //str.substring(beginIndex, endIndex)
      //Orientation: 239.26 -17.40 -112.52
      //012345678910
      
      
      rotateX(radians(ahrs[0])); 
      rotateY(radians(ahrs[1]));
      rotateZ(radians(ahrs[2]));
      box(160); 
    }
  }
}

int[] byte_handler(byte[] inBuffer) {
  
  roll_sign = inBuffer[0]; 
  roll_rec = inBuffer[1];

  pitch_sign = inBuffer[2];
  pitch_rec = inBuffer[3];
  
  heading_sign = inBuffer[4];
  heading_rec = inBuffer[5];
  
  
 //--------------------------
 //ROLL
 if (roll_sign == 0x00){
   print("roll sign: ");
   println(roll_sign);
   println();
   //negative 
   roll_int = int(roll_rec)*(-1);
 }
 else if (roll_sign == 0x01) {
   //positive
  print("roll sign: ");
  println(roll_sign);
  println();
  roll_int = int(roll_rec);
 }
 
 //--------------------------
 //PITCH
 if (pitch_sign == 0x00){
   print("pitch sign: ");
   println(pitch_sign);
   println();
   //negative 
   roll_int = int(pitch_rec)*(-1);
 }
 else if (pitch_sign == 0x01) {
   //positive
  print("pitch sign: ");
  println(pitch_sign);
  println();
  pitch_int = int(pitch_rec);
 }
 
 //--------------------------
 //HEADING
 if (heading_sign == 0x00){
   print("heading sign: ");
   println(heading_sign);
   println();
   //negative 
   heading_int = int(heading_rec)*(-1);
 }
 else if (heading_sign == 0x01) {
   //positive
  print("heading sign: ");
  println(heading_sign);
  println();
  heading_int = int(heading_rec);
 }
 
  int[] ahrs = new int[3];
  ahrs[0] = roll_int;
  ahrs[1] = pitch_int;
  ahrs[2] = heading_int;
  return ahrs;
}

/*
Integration of the gyroscope measurements provides information
about the orientation of the sensor.

After subtraction of the earth’s gravity, double integration of the
accelerometer measurements provides information about the sensor’s position. 
*/ 
