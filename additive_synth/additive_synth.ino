//additive synthesis

// button - envelope
// pot 1 - modulation

#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <mozzi_fixmath.h>
#include <tables/sin2048_int8.h> // sine table for oscillator
#include <tables/cos2048_int8.h>
#include <AutoMap.h>
#include <Ead.h>
#include <mozzi_rand.h>
// use: Oscil <table_size, update_rate> oscilName (wavetable), look in .h file of table #included above
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aSin0(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aSin1(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aSin2(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aSin3(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aSin4(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aSin5(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aSin6(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aSin7(COS2048_DATA);

Oscil <SIN2048_NUM_CELLS, AUDIO_RATE> aMod(SIN2048_DATA);

Ead kEnvelope(CONTROL_RATE);
int gain;

// use #define for CONTROL_RATE, not a constant
#define CONTROL_RATE 128 // powers of 2 please

const int sensorPin = 1;
const int sensorPinD = 4;

boolean trigger = false;


void setup(){
  startMozzi(CONTROL_RATE); // set a control rate of 64 (powers of 2 please)
  pinMode(sensorPinD, INPUT);
  randSeed();
  Serial.begin(115200);
}


void updateControl(){
  // put changing controls in here
  float val1 = mozziAnalogRead(sensorPin);
  //int main_freq = 120;
  int sensorD = digitalRead(sensorPinD);
  
  selectScale(2, val1);  
  float note = selScale();
  
  aMod.setFreq(note);
  
  float main_freq = 440;
  
  if (sensorD == 1) {
    if (!trigger) {
    unsigned int duration = rand(500u)+200;
    unsigned int attack = rand(75)+5; // +5 so the internal step size is more likely to be >0
    unsigned int decay = duration - attack;
    kEnvelope.start(attack,decay);
      trigger = true;
    } else {
      trigger = false;
   }
  } 
  Serial.println(sensorD);
  
  gain = (int) kEnvelope.next();
  
  float freq1 = main_freq * 0;
  float freq2 = main_freq * 1;
  float freq3 = main_freq * 2;
  float freq4 = main_freq * 3;
  float freq5 = main_freq * 4;
  float freq6 = main_freq * 5;
  float freq7 = main_freq * 6;
  float freq8 = main_freq * 8;
  
  aSin0.setFreq(freq1);
  aSin1.setFreq(freq2);
  aSin2.setFreq(freq3);
  aSin3.setFreq(freq4); // set the frequency
  aSin4.setFreq(freq5);
  aSin5.setFreq(freq6);
  aSin6.setFreq(freq7);
  aSin7.setFreq(freq8); // set the frequency
  
 
  
 
}


int updateAudio(){
  int asig;
  //asig = (uint8_t)aSin0.next();
  
  uint8_t sinu1 = aSin0.next() * 1;
  uint8_t sinu2 = aSin1.next() * 0.7;
  uint8_t sinu3 = aSin2.next() * 0.5;
  uint8_t sinu4 = aSin3.next() * 0.4;
  uint8_t sinu5 = aSin4.next() * 0.3;
  uint8_t sinu6 = aSin5.next() * 0.3;
  //uint8_t sinu7 = aSin6.next() * 0.2;
  //uint8_t sinu8 = aSin7.next() * 0.1;
  
  
  //asig = sinu1 + sinu2 + sinu3 + sinu4 + sinu5; // + sinu6 + sinu7 + sinu8;
  //asig = sinu3 + sinu4 + sinu5 + sinu6 + sinu7 + sinu8;
  asig = aMod.phMod((aSin1.next() + aSin2.next() + aSin3.next() + aSin4.next() + aSin5.next()));//*aMod.next();
  
   int asig_out = gain*asig;// * 0.4;
  //return aSin.next(); // return an int signal centred around 0
  return asig_out>>5; //without gain* >>1
  
}


void loop(){
  audioHook(); // required here
}





