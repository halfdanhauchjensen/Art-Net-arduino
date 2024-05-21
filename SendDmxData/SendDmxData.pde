import ch.bildspur.artnet.*;

ArtNetClient artnet;
byte[] artNetData_u1 = new byte[512];
byte[] artNetData_u2 = new byte[512];
byte[] artNetData_u3 = new byte[512];

int NUM_PIX = 120;

void setup()
{
  size(360, 50);  
  textAlign(CENTER, CENTER);
  textSize(20);
  noStroke();
  // create artnet client without buffer (no receving needed)
  artnet = new ArtNetClient(null);
  artnet.start();
  frameRate(30);
}

float rectX = 0;
int rectW = 10;

void draw()
{
  println(frameRate);
  // create color
  rectX+=1.5;
  if (rectX > width) rectX = -rectW;
  background(255,0,0);
  rect(rectX, 0, rectW, height);

  updateData(artNetData_u1, NUM_PIX, 0);
  updateData(artNetData_u2, NUM_PIX, NUM_PIX);
  updateData(artNetData_u3, NUM_PIX, NUM_PIX*2);

  // send dmx to localhost
  artnet.unicastDmx("192.168.1.101", 0, 1, artNetData_u1);
  artnet.unicastDmx("192.168.1.101", 0, 2, artNetData_u2);
  artnet.unicastDmx("192.168.1.101", 0, 3, artNetData_u3);
}

void updateData(byte [] data, int num_pixels, int canvas_x_start){
  for (int i = 0; i < num_pixels; i++){
    int idx = i * 3;
    data[idx + 0] = (byte) red(get(canvas_x_start+i,25));
    data[idx + 1] = (byte) green(get(canvas_x_start+i,25));
    data[idx + 2] = (byte) blue(get(canvas_x_start+i,25));
  }
}
