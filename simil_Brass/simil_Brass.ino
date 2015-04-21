//A sort of brass-like sound
//----------------------------
//sensors:
// pot 1 (optional pot 2)
//-----------------------

#include <MozziGuts.h>
#include <Oscil.h>
#include <mozzi_fixmath.h>
#include <mozzi_midi.h>
#include <mozzi_rand.h>
#include <LowPassFilter.h>
#include <Ead.h>
#include <AutoMap.h>
#include <RollingAverage.h>
#include <AutoMap.h>
#include <ADSR.h>
#include <Smooth.h>
#include <Line.h>
#include <EventDelay.h>

#include <tables/cos2048_int8.h> 
#include <tables/phasor256_int8.h>

#define CONTROL_RATE 256

const int PIN_0 = 0; // set freq
const int PIN_1 = 1; // set the input for trigger
const int PIN_2 = 2;
const int PIN_3 = 3;
const int PIN_4 = 4;
const int PIN_5 = 5;

const int GATE = 4;

//Sensor values
int pin0_val = 0; //int
int pin1_val = 0;
int pin2_val = 0;
int pin3_val = 0;
int pin4_val = 0;
int pin5_val = 0;

int button_in = 0;

int byteSh = 0; //shift byte - audio final

EventDelay kGainChangeDelay;

int valu;



void setup() {
  
  startMozzi(CONTROL_RATE);
  
  pinMode(GATE, INPUT);
  
  Serial.begin(115200);
  
}



void loop() {
  
  audioHook();
  
}


void updateControl() {
  
  button_in = digitalRead(GATE);
  
  pin1_val = mozziAnalogRead(PIN_1);
  
  pin2_val = mozziAnalogRead(PIN_2);
  
  Serial.println(button_in);
    
  modelControl(pin1_val, pin2_val, 800, 10, button_in);
  
  
}

int updateAudio() {
  
  modelAudio();
  
}


