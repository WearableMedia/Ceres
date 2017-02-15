/***************************************************
  This is an example for our Adafruit 12-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/

  These drivers uses SPI to communicate, 2 pins are required to
  interface: Data and Clock. The boards are chainable

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_TLC59711.h"
#include <SPI.h>

// How many boards do you have chained?
#define NUM_TLC59711 1
#define NUM_CHANNELS 12

#define data   9
#define clock  10

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);
//Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);

uint16_t pwm = 6000;

void setup() {
  Serial.begin(9600);
  Serial.println("TLC59711 test");
  tlc.begin();
  tlc.write();
}

void loop() {

for(int j = 2; j < 8; j ++){
    for (uint8_t i = 0; i < NUM_CHANNELS * NUM_TLC59711; i++) {
    tlc.setPWM(i, 0);
    tlc.setPWM(i + 1, 1000);
    tlc.setPWM(i + 2, 2000);
    tlc.setPWM(i + 3, 5000);
    if (i >= (NUM_CHANNELS - 1)) {
      tlc.setPWM(0, pwm);
    } else {
      tlc.setPWM(i + 4, pwm);
    }
    tlc.write();
    delay(20*j);
  }
}


}



