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
int num = 17;
uint16_t pwm[] =  {47617, 42290, 43258, 35994, 10811, 8390, 5000, 6937, 11296, 28245, 34057, 42774, 65535, 17591, 22918, 7421, 23887};
int velocity[] =  { 62, 40, 48, 64, 69, 96, 150, 137, 74, 78, 65, 54, 40, 83, 67, 137, 78};
void setup() {
  Serial.begin(9600);
  Serial.println("TLC59711 test");
  tlc.begin();
  tlc.write();
}

void loop() {

  for (int j = 0; j < num; j ++) {
    for (uint8_t i = 0; i < NUM_CHANNELS * NUM_TLC59711; i++) {
      tlc.setPWM(i, 0);
      tlc.setPWM(i + 1,  int(pwm[j] / 5));
      tlc.setPWM(i + 2,  int(pwm[j] / 4));
      tlc.setPWM(i + 3,  int(pwm[j] / 3));
      tlc.setPWM(i + 4,  int(pwm[j] / 2));
      if (i >= (NUM_CHANNELS - 1)) {
        //tlc.setPWM(0, pwm[j]/6);
      } else {
        tlc.setPWM(i + 5,  pwm[j]);
      }
      tlc.write();
      delay(velocity[j]);
    }
    tlc.setPWM(0, 0);
    tlc.write();
    delay(600);
  }
  delay(1000);

}



