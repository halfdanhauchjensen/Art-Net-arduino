#include <FastLED.h>  // include FastLED *before* Artnet

// Please include ArtnetEther.h to use Artnet on the platform
// which can use both WiFi and Ethernet
#include <ArtnetEther.h>
// #include <ArtnetNativeEther.h>  // only for Teensy 4.1
// this is also valid for other platforms which can use only Ethernet
// #include <Artnet.h>

// Ethernet stuff
//const IPAddress ip(192, 168, 0, 201);
// uint8_t mac[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};
uint8_t mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

ArtnetReceiver artnet;
uint8_t uni_1 = 1;  // 0 - 15
uint8_t uni_2 = 2;
uint8_t uni_3 = 3;

// FastLED
#define NUM_LEDS 605
CRGB leds[NUM_LEDS];
//const uint8_t PIN_LED_DATA = 3;
#define DATA_PIN 3
#define CLOCK_PIN 6
size_t idx = 0;
void setup() {
    Serial.begin(115200);
    delay(2000);

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    //FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);  // BGR ordering is typical

    //Ethernet.begin(mac, ip);
        //Ethernet.begin(mac, ip);
      // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
    artnet.begin();

    // if Artnet packet comes to this universe, forward them to fastled directly
    //artnet.forwardArtDmxDataToFastLED(universe, leds, NUM_LEDS);

    // this can be achieved manually as follows
    // if Artnet packet comes to this universe, this function (lambda) is called
     
     artnet.subscribeArtDmxUniverse(uni_1, [&](const uint8_t* data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote) {
    //     // set led
    //     // artnet data size per packet is 512 max
    //     // so there is max 170 pixel per packet (per universe)
         //idx = 0;
         for (size_t pixel = 0; pixel < 120; ++pixel) {
             idx = pixel * 3;
             leds[pixel].r = data[idx + 0];
             leds[pixel].g = data[idx + 1];
             leds[pixel].b = data[idx + 2];
         }
         //printMessage(size, data, remote);
         
     });
     
     artnet.subscribeArtDmxUniverse(uni_2, [&](const uint8_t* data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote) {
    //     // set led
    //     // artnet data size per packet is 512 max
    //     // so there is max 170 pixel per packet (per universe)
         //idx = 0;
         //idx = 60; // offset with 20 LEDS 
         for (size_t pixel = 0; pixel < 120; ++pixel) {
             idx = + pixel * 3;
             //idx += 20*3; // offset with 20 LEDS on the LED strip
             leds[pixel+120].r = data[idx + 0];
             leds[pixel+120].g = data[idx + 1];
             leds[pixel+120].b = data[idx + 2];
         }
         //printMessage(size, data, remote);
         
     });

     artnet.subscribeArtDmxUniverse(uni_3, [&](const uint8_t* data, uint16_t size, const ArtDmxMetadata &metadata, const ArtNetRemoteInfo &remote) {
    //     // set led
    //     // artnet data size per packet is 512 max
    //     // so there is max 170 pixel per packet (per universe)
         //idx = 0;
         //idx = 60; // offset with 20 LEDS 
         for (size_t pixel = 0; pixel < 120; ++pixel) {
             idx = + pixel * 3;
             //idx += 20*3; // offset with 20 LEDS on the LED strip
             leds[pixel+240].r = data[idx + 0];
             leds[pixel+240].g = data[idx + 1];
             leds[pixel+240].b = data[idx + 2];
         }
         //printMessage(size, data, remote);
         
     });
}

void loop() {
    artnet.parse();  // check if artnet packet has come and execute callback
    FastLED.show();
}

void printMessage(int size, const uint8_t* data, const ArtNetRemoteInfo &remote){
  Serial.print("lambda : artnet data from ");
        Serial.print(remote.ip);
        Serial.print(":");
        Serial.print(remote.port);
        Serial.print(", universe = ");
        Serial.print(uni_1);
        Serial.print(", size = ");
        Serial.print(size);
        Serial.print(") :");
        for (size_t i = 0; i < size; ++i) {
            Serial.print(data[i]);
            Serial.print(",");
        }
        Serial.println();
}
