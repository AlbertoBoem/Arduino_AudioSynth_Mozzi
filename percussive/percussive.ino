
#include <MozziGuts.h>
#include <Oscil.h>
#include <mozzi_fixmath.h>
#include <EventDelay.h>
#include <mozzi_rand.h>
#include <mozzi_midi.h>
#include <AutoMap.h>
#include <mozzi_analog.h>
#include <Ead.h>
#include <StateVariable.h>
#include <LowPassFilter.h>

#include <tables/brownnoise8192_int8.h>
#include <tables/cos2048_int8.h>

#define CONTROL_RATE 64

// Analog in
const int pin_1 = 1;
const int pin_2 = 2;
const int pin_3 = 3;

// Digital in/out
const int button_4 = 4;

// Sensor values
int val_1 = 0;
int val_2 = 0;
int val_3 = 0;

//
int buttonVal_4 = 0;


void setup() {
  
  startMozzi(CONTROL_RATE);
  
  pinMode(button_4, INPUT);
  
  //Serial.begin(115200);
  
}

void loop() {  
  
  audioHook();
  
}

void updateControl() {
  
  val_1 = mozziAnalogRead(pin_1);
  val_2 = mozziAnalogRead(pin_2);
  val_3 = mozziAnalogRead(pin_3);
  
  buttonVal_4 = digitalRead(button_4);
  
  //updateControlPercussiVe(val_1, val_2, val_3, buttonVal_4, 10, 2000); //2000
  //attack 100 dec 10 - freqEnv at 10 dec 1000 more close noisy
  //       10      2000 -          10     1000
  
  updateControlPercussiVe_1(val_1, val_2, val_3, buttonVal_4, 10, 2000);
  
  //Serial.println();

}

int updateAudio() {
  
  //updateAudioPercussiVe();
  updateAudioPercussiVe_1();
  
}
