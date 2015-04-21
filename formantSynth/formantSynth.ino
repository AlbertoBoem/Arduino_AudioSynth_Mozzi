//-------------------------------------------

//Formant Synth

//connections:
//button --> pin D4 (env)
//Pot1 --> A1 (sel vowel)
//Pot2 --> A2 (pitch)
//Pot3 --> A3 (modulation/tremolo)

//--------------------------------------------

#include <MozziGuts.h>
#include <Oscil.h>
#include <mozzi_fixmath.h>
#include <mozzi_midi.h>
#include <mozzi_rand.h>
#include <StateVariable.h>
#include <Ead.h>
#include <RollingAverage.h>
#include <AutoMap.h>
#include <ADSR.h>
#include <Smooth.h>
#include <Line.h>
#include <EventDelay.h>

#include <tables/cos2048_int8.h> 
#include <tables/phasor256_int8.h>
#include <tables/sin2048_int8.h>

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
  
  //setFormantSynth();
  //setFormantSynth_1();
  
  randSeed();
  
  pinMode(GATE, INPUT);
  
  kGainChangeDelay.set(100);
  
  //Serial.begin(115200);
}



void updateControl() {
  
  pin1_val = mozziAnalogRead(PIN1);
  pin2_val = mozziAnalogRead(PIN2);
  pin3_val = mozziAnalogRead(PIN3);
  
  button_in = digitalRead(GATE);
  
  pin1_val = map(pin1_val, 0, 1023, 0, 50);
  
  //pin2_val = map(pin2_val, 0, 1023, 60, 220);
  
  if(kGainChangeDelay.ready()){
    valu = rand(5);
    
    kGainChangeDelay.start();
  }
  
  //updateFormantSynthControl();
  updateFormantSynthControl_1(pin1_val, pin2_val, pin3_val, button_in, 10, 5000);
  
  
  //Serial.println(pin3_val);
  
}

int updateAudio() {
  
  //updateFormantSynthAudio();
  updateFormantSynthAudio_1();
  
}


void loop() {
  
  audioHook();
  
}
