#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 9
#define NUMPIXELS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int num = 17;
uint16_t pwm[] =  {47617, 42290, 43258, 35994, 10811, 8390, 5000, 6937, 11296, 28245, 34057, 42774, 65535, 17591, 22918, 7421, 23887};
int velocity[] =  { 62, 40, 48, 64, 69, 96, 150, 137, 74, 78, 65, 54, 40, 83, 67, 137, 78};

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  for (int j = 0; j < num; j ++) {
    for (uint8_t i = 0; i < NUMPIXELS; i++) {
       strip.setPixelColor(i, 0);
      strip.setPixelColor(i + 1,  int(pwm[j] / 5), int(pwm[j] / 5), int(pwm[j] / 5));
      strip.setPixelColor(i + 2,  int(pwm[j] / 4),int(pwm[j] / 4),int(pwm[j] / 4));
       strip.setPixelColor(i + 3,  int(pwm[j] / 3),int(pwm[j] / 3),int(pwm[j] / 3));
      strip.setPixelColor(i + 4,  int(pwm[j] / 2), int(pwm[j] / 2), int(pwm[j] / 2));
      if (i >= (NUMPIXELS - 1)) {
        //tlc.setPWM(0, pwm[j]/6);
      } else {
         strip.setPixelColor(i + 5,  pwm[j],pwm[j],pwm[j]);
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
