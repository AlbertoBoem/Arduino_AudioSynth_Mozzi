#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/cos2048_int8.h>
#include <AudioDelay.h>
#include <Ead.h>
#include <Line.h>
#include <AutoMap.h>
#include <StateVariable.h>
#include <mozzi_analog.h>
#include <mozzi_rand.h>

#define CONTROL_RATE 64

Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aCos (COS2048_DATA);

StateVariable <BANDPASS> bp1;
StateVariable <BANDPASS> bp2;
StateVariable <BANDPASS> bp3;

Ead env_1(CONTROL_RATE);

AutoMap mapModVal(0, 1023, 0, 255);

const int pin_1 = 1;
const int pin_2 = 2;
const int pin_3 = 3;

const int pin_4 = 4;

int val_1 = 0;
int val_2 = 0;
int val_3 = 0;
int valou = 0;
int b_val = 0;

boolean triggered = false;

int finalSign;


void setup() {
  
  startMozzi(CONTROL_RATE);
  randSeed();
  //Serial.begin(115200);

}


void loop() {
  
  audioHook();
  
}

void updateControl() {
  
  val_1 = mozziAnalogRead(pin_1);
  b_val = digitalRead(pin_4);
  
  val_2 = mozziAnalogRead(pin_2);
  val_3 = mozziAnalogRead(pin_3);
  
  val_2 = map(val_2, 0, 1023, 0, 100);
  val_3 = map(val_3, 0, 1023, 0, 1000);
  
  int freqVal = rand(1600);
  aCos.setFreq((freqVal+800)*val_2);
  
  bp1.setResonance(30);
  bp1.setCentreFreq(val_2);//(2200);
  bp2.setResonance(30);
  bp2.setCentreFreq(val_3);//(3300);
  
}

int updateAudio() {
  
  return bp2.next(aCos.next());
 
}


