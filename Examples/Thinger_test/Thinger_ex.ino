#include <WiFi.h>
#define _DEBUG_
#include <ThingerESP32.h>

#define USERNAME "gtas"
#define DEVICE_ID "ESP32_therm"
#define DEVICE_CREDENTIAL "esp@thinger"

#define SSID "ubx"
#define SSID_PASSWORD "GqpZvmK8@r5yL#AP"

// define your board pin here
#define LED_PIN 16

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
int Slide=0;
int Slide_old=0;
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
thing.add_wifi(SSID, SSID_PASSWORD);
  

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(LED_PIN);

  // resource output example (i.e. reading a sensor value)
  thing["millis"] >> outputValue(millis());
 thing["val"]<< inputValue(Slide);
  // more details at http://docs.thinger.io/arduino/
}

void loop() {
  thing.handle();
  
  
  if((Slide-Slide_old)>0) 
  {
    Slide_old=Slide;
    Serial.println(Slide);
    thing.stream(thing["millis"]);
  }
}
