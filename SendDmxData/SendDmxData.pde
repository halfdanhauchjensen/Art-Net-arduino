import ch.bildspur.artnet.*;

ArtNetClient artnet;
byte[] dmxData = new byte[512];

void setup()
{
  size(170, 50);
  
  //colorMode(RGB, 360, 100, 100);
  textAlign(CENTER, CENTER);
  textSize(20);
  noStroke();
  // create artnet client without buffer (no receving needed)
  artnet = new ArtNetClient(null);
  artnet.start();
}

float rectX = 0;
int rectW = 10;

void draw()
{
  // create color
  //int c = color(frameCount % 360, 80, 100);
  rectX+=0.5;
  if (rectX > width) rectX = -rectW;
  background(255,0,0);
  rect(rectX, 0, rectW, height);

  // fill dmx array
  /*
  dmxData[0] = (byte) red(c);
  dmxData[1] = (byte) green(c);
  dmxData[2] = (byte) blue(c);
  */
  /*
  for(int x = 0; x < width; x+=3){
    //c = get(x, 50);
    dmxData[x] = (byte) red(c);
    dmxData[x+1] = (byte) green(c);
    dmxData[x+2] = (byte) blue(c);
  }
  */
  
  for (int pixel = 0; pixel < width; pixel++) {
             int idx = pixel * 3;
             dmxData[idx + 0] = (byte) red(get(pixel, 25));
             dmxData[idx + 1] = (byte) green(get(pixel, 25));
             dmxData[idx + 2] = (byte) blue(get(pixel, 25));
             //println(pixel, (byte) red(get(pixel, 25)), (byte) green(get(pixel, 50)), (byte) blue(get(pixel, 50)));
             
         }

  // send dmx to localhost
  artnet.unicastDmx("192.168.1.168", 0, 1, dmxData);

  // show values
  //text("R: " + (int)red(c) + " Green: " + (int)green(c) + " Blue: " + (int)blue(c), width / 2, height / 2);
}
