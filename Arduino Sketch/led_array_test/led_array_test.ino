
#include "Adafruit_TLC59711.h"
#include <SPI.h>

// How many boards do you have chained?
#define NUM_TLC59711 2

#define data   11
#define clock  13

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);
//Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);

void setup() { 
  Serial.begin(9600);
  
  Serial.println("TLC59711 test") ;
  pinMode(10, OUTPUT);
  tlc.begin();
  tlc.write();
}

void loop() {
 breathingLEDArray();
}


// Fill the dots one after the other with a color, built for next function
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for(uint16_t i=0; i< 8*NUM_TLC59711; i++) {
      tlc.setLED(i, r, g, b);
      tlc.write();
      delay(wait);
  }
}


int breath=0,spd=1101,vel=100;

//below function lights up two LEDs in one of the R/G/B channels.
void breathingLEDArray(){
  //breathing calculcation
  spd+=vel;
  breath+=spd;
  
  //default function in library light up the R/G/B channel of all LEDs on board
  colorWipe(breath, 0, 0, 1); // "Red" (depending on your LED wiring)
  colorWipe(0,breath, 0, 1); // "Green" (depending on your LED wiring)
  colorWipe(0, 0, breath, 1); // "Blue" (depending on your LED wiring)
  
  //breathing calculation
  breath++;
  if (breath>=63535||breath<=1300)
  {spd*=-1;}
  
}





