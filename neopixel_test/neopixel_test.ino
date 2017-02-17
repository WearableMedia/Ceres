#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 9
#define NUMPIXELS 30
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int num = 17;
uint16_t pwm[] =  {114, 132, 129, 153, 236, 244, 255, 249, 234, 178, 159, 130, 55, 213, 196, 247, 193};
int velocity[] =  { 62, 40, 48, 64, 69, 96, 150, 137, 74, 78, 65, 54, 40, 83, 67, 137, 78};

float pos1 = 0, speed1 = 1;
int fullBri = 200;
uint32_t blueGradient[] = {0x0028C7, 0x0045CD, 0x0062D3, 0x007FD9, 0x009DE0, 0x00BAE6, 0x00D7EC, 0x00F5F3};

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  strip.begin();
  strip.setBrightness(fullBri / 2);
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  for (int j = 0; j < num; j ++) {
    for (uint8_t i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, 0);
      strip.setPixelColor(i + 1,  int(pwm[j] / 5), int(pwm[j] / 5), int(pwm[j] / 5));
      strip.setPixelColor(i + 2,  int(pwm[j] / 4), int(pwm[j] / 4), int(pwm[j] / 4));
      strip.setPixelColor(i + 3,  int(pwm[j] / 3), int(pwm[j] / 3), int(pwm[j] / 3));
      strip.setPixelColor(i + 4,  int(pwm[j] / 2), int(pwm[j] / 2), int(pwm[j] / 2));
      if (i >= (NUMPIXELS - 1)) {
        //tlc.setPWM(0, pwm[j]/6);
      } else {
        strip.setPixelColor(i + 5,  pwm[j], pwm[j], pwm[j]);
      }
      strip.show();
      delay(velocity[j]);
    }
    //      strip.setPixelColor(0, 0);
    //      strip.setPixelColor(0, 0);
    delay(600);
  }
  delay(1000);
}


/*

  void loop() {

  for (int k = 0; k < num; k ++) {
    //if ((unsigned long)(millis() % velocity[k]) == 0) {
    int j;
    for (int i = -4; i < 4; i++) {
      strip.setPixelColor(pos1 + i,  int(pwm[k] / (i + 5)), int(pwm[k] / (i + 5)), int(pwm[k] / (i + 5)));
    }


    strip.show();

    for (j = -4; j < 4; j++) strip.setPixelColor(pos1 + j, 0);

    if (pos1 >= NUMPIXELS) {
      pos1 -= NUMPIXELS;
    } else {
      pos1 += speed1;
    }

    delay(velocity[k]);
    //}
  }

  delay(1000);
  }

*/
