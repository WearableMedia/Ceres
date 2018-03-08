#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define vibLF 6
#define vibLB 5
#define vibRF 11
#define vibRB 10

#define PIN_R 3 //3 on feather
#define PIN_L 2 //3 on feather
#define NUMPIXELS 50

Adafruit_NeoPixel stripR = Adafruit_NeoPixel(NUMPIXELS, PIN_R, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripL = Adafruit_NeoPixel(NUMPIXELS, PIN_L, NEO_GRB + NEO_KHZ800);

int num = 17;
uint16_t pwm[] =  {114, 132, 129, 153, 236, 244, 255, 249, 234, 178, 159, 130, 55, 213, 196, 247, 193};
int velocity[] =  { 62, 40, 48, 64, 69, 96, 150, 137, 74, 78, 65, 54, 40, 83, 67, 137, 78};

float pos1 = 0, speed1 = 1;
int fullBri = 255;


unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  stripR.begin();
  stripR.setBrightness(fullBri);
  stripR.show(); // Initialize all pixels to 'off'

  stripL.begin();
  stripL.setBrightness(fullBri);
  stripL.show(); // Initialize all pixels to 'off'
}


void loop() {
  for (int j = 0; j < num; j ++) {
    //each neo
    for (uint8_t i = 0; i < NUMPIXELS; i++) {
      //each neopixel
      stripR.setPixelColor(i, 0);
      stripR.setPixelColor(i + 1,  int(pwm[j] / 5), int(pwm[j] / 5), int(pwm[j] / 5));
      stripR.setPixelColor(i + 2,  int(pwm[j] / 4), int(pwm[j] / 4), int(pwm[j] / 4));
      stripR.setPixelColor(i + 3,  int(pwm[j] / 3), int(pwm[j] / 3), int(pwm[j] / 3));
      stripR.setPixelColor(i + 4,  int(pwm[j] / 2), int(pwm[j] / 2), int(pwm[j] / 2));

      stripL.setPixelColor(i, 0);
      stripL.setPixelColor(i + 1,  int(pwm[j] / 5), int(pwm[j] / 5), int(pwm[j] / 5));
      stripL.setPixelColor(i + 2,  int(pwm[j] / 4), int(pwm[j] / 4), int(pwm[j] / 4));
      stripL.setPixelColor(i + 3,  int(pwm[j] / 3), int(pwm[j] / 3), int(pwm[j] / 3));
      stripL.setPixelColor(i + 4,  int(pwm[j] / 2), int(pwm[j] / 2), int(pwm[j] / 2));

      if (i >= (NUMPIXELS - 1)) {
        //tlc.setPWM(0, pwm[j]/6);
      } else {
        stripR.setPixelColor(i + 5,  pwm[j], pwm[j], pwm[j]);
        stripL.setPixelColor(i + 5,  pwm[j], pwm[j], pwm[j]);
      }
      stripR.show();
      stripL.show();
      // if (j % 4 == 0) {
      analogWrite(vibLF, pwm[j]);
      // Serial.println("LF");
      //} else if (j % 4 == 1) {
      analogWrite(vibRF, pwm[j]);
      //Serial.println("RF");
      //} else if (j % 4 == 2) {
      analogWrite(vibRB, pwm[j]);
      //Serial.println("RB");
      //} else if (j % 4 == 3) {
      analogWrite(vibLB, pwm[j]);
      //Serial.println("LB");
      //}
      delay(velocity[j]);
    }
    analogWrite(vibLF, 0);
    analogWrite(vibLB, 0);
    analogWrite(vibRF, 0);
    analogWrite(vibRB, 0);
    delay(600);
  }
  delay(1000);
}


