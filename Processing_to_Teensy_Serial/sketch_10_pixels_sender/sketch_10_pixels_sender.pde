import processing.serial.*; 

float boxX;
float boxY;
int boxSize = 20;
boolean mouseOverBox = false;

Serial port; 


byte[] bytesA = {byte(10), byte(20), byte(30), byte(40), byte(50), byte(60), byte(70), byte(80), byte(90), byte(100)};
byte[] bytesB = {byte(110), byte(120), byte(130), byte(140), byte(150), byte(160), byte(170), byte(180), byte(190), byte(200)};

void setup() {
  size(200, 200);
  boxX = width/2.0;
  boxY = height/2.0;
  rectMode(RADIUS); 

  // List all the available serial ports in the output pane. 
  // You will need to choose the port that the Arduino board is 
  // connected to from this list. The first port in the list is 
  // port #0 and the third port in the list is port #2. 
  println(Serial.list()); 

  // Open the port that the Arduino board is connected to (in this case #0) 
  // Make sure to open the port at the same speed Arduino is using (9600bps) 
  port = new Serial(this, Serial.list()[5], 115200);
  
  /*
  for (int i=0; i<bytes.length; i++) {
    bytes[i] = byte(255);
    println(bytes[i]);
  }
  */
}

void draw() 
{ 
  background(0);

  // Test if the cursor is over the box 
  if (mouseX > boxX-boxSize && mouseX < boxX+boxSize && 
    mouseY > boxY-boxSize && mouseY < boxY+boxSize) {
    mouseOverBox = true;
    // draw a line around the box and change its color:
    stroke(255); 
    fill(153);
    // send an 'H' to indicate mouse is over square:
    //port.write('H');
    //bytes[0] = byte(255);
    //print(bytes[0]);
    port.write(bytesA);
  } 
  else {
    // return the box to it's inactive state:
    stroke(153);
    fill(50);
    // send an 'L' to turn the LED off: 
    //port.write('L'); 
    //bytes[0] = byte(100);
    port.write(bytesB);
    mouseOverBox = false;
  }

  // Draw the box
  rect(boxX, boxY, boxSize, boxSize);
}
