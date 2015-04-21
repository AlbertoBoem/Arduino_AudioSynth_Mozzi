#include <MozziGuts.h>
#include <Oscil.h> // oscillator template
#include <tables/brownnoise8192_int8.h> // recorded audio wavetable
#include <Ead.h> // exponential attack decay
#include <EventDelay.h>
#include <mozzi_rand.h>
#include <AutoMap.h>
#include <LowPassFilter.h>
#include <tables/cos2048_int8.h>
#include <tables/triangle2048_int8.h>

#define CONTROL_RATE 64 // powers of 2 please

Oscil<BROWNNOISE8192_NUM_CELLS, AUDIO_RATE> aNoise(BROWNNOISE8192_DATA);
//Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aModDepth(COS2048_DATA);
Oscil<TRIANGLE2048_NUM_CELLS, AUDIO_RATE> aModDepth(TRIANGLE2048_DATA);

EventDelay kDelay; // for triggering envelope start

Ead kEnvelope(CONTROL_RATE); // resolution will be CONTROL_RATE

LowPassFilter lpf;

int gain;

AutoMap map1(0, 1023, 0, 500);
AutoMap map2(0, 1023, 0, 3000);
AutoMap map3(0, 1023, 0, 1000);

const int pin1 = 1;
const int pin2 = 2;
const int pin3 = 3;

int val1 = 0;
int val2 = 0;
int val3 = 0;


void setup() {

  aNoise.setFreq((float)AUDIO_RATE/BROWNNOISE8192_SAMPLERATE);
  startMozzi(CONTROL_RATE);
  lpf.setResonance(100);

}

void updateControl() {
  
// jump around in audio noise table to disrupt obvious looping
aNoise.setPhase(rand((unsigned int)BROWNNOISE8192_NUM_CELLS));

val1 = mozziAnalogRead(pin1);
val1 = map1.next(val1);

val2 = mozziAnalogRead(pin2);
val2 = map2.next(val2);

val3 = mozziAnalogRead(pin3);
val3 = map3.next(val3);

aModDepth.setFreq(val3);

//lpf.setCutoffFreq(val3);
lpf.setCutoffFreq(aModDepth.next());


if(kDelay.ready()) {
// set random parameters // change these set up to vary tempo
  unsigned int delay = rand(2000);

  unsigned int attack = val1; //rand(500);
  unsigned int decay = val2; //rand(3000);

  kEnvelope.start(500+attack,2000+decay);
  kDelay.start(5000+delay);
}

gain = (int) kEnvelope.next();

}

int updateAudio() {
  
  int filtered = (int)lpf.next(aNoise.next());
  return (gain*filtered)>>8; //without filter >>8

}

void loop(){
  
  audioHook(); // required here

}

