#include <MozziGuts.h>
#include <Oscil.h>
#include <tables/whitenoise8192_int8.h> // wavetable
#include <tables/phasor256_int8.h> // wavetable
#include <tables/cos2048_int8.h>
#include <AudioDelay.h>
#include <Ead.h>
#include <AutoMap.h>
#include <StateVariable.h>
#include <mozzi_analog.h>

#define CONTROL_RATE 64

Oscil <WHITENOISE8192_NUM_CELLS, AUDIO_RATE> wNoise (WHITENOISE8192_DATA);
Oscil <PHASOR256_NUM_CELLS, AUDIO_RATE> pHasor (PHASOR256_DATA);
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> kFreq(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, CONTROL_RATE> oscL(COS2048_DATA);

StateVariable <HIGHPASS> hip;
StateVariable <BANDPASS> bp1;
StateVariable <BANDPASS> bp2;
StateVariable <BANDPASS> bp3;
StateVariable <BANDPASS> bp4;
StateVariable <BANDPASS> bp5;

Ead envPh(CONTROL_RATE);
Ead envVol(CONTROL_RATE);

AutoMap mapModVal(0, 1023, 0, 255);

AudioDelay <256> aDel;
int del_samps;

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

int finalSig;

int harmFiltered;

int noiseFiltered;

int noiseSignal;

int modul;


void setup() {
  
  startMozzi(CONTROL_RATE);
  Serial.begin(115200);
  kFreq.setFreq(.63f);

}


void loop() {
  
  audioHook();
  
}

void updateControl() {
  
  val_1 = mozziAnalogRead(pin_1);
  b_val = digitalRead(pin_4);
  
  val_2 = mozziAnalogRead(pin_2);
  val_3 = mozziAnalogRead(pin_3);
  
  valou = mozziAnalogRead(pin_3);
  
  val_2 = map(val_2, 0, 1023, 0, 1000);
  val_3 = map(val_3, 0, 1023, 0, 1000);
  
  Serial.println(val_2);
  
  //controlProcess(val_1, b_val, 10, 100, 10, 100);
  
   if(b_val == 1) {
    if (!triggered) {
      envPh.start(10, 1000);
      envVol.start(100, 10);
      triggered = true;
    } else {
      triggered = false;
    }
  }
  
  ///
  
  wNoise.setFreq(1000);
  
  hip.setResonance(150); //fix
  hip.setCentreFreq(val_2);//(100); //fix
  
  bp1.setResonance(30);
  bp1.setCentreFreq(val_3+200);//(2200);
  bp2.setResonance(30);
  bp2.setCentreFreq(val_3+1200);//(3300);
  bp3.setResonance(30);
  bp3.setCentreFreq(val_3+2200);//(4200);
  bp4.setResonance(30);
  bp4.setCentreFreq(val_3+3200);//(6500);
  bp5.setResonance(30);
  bp5.setCentreFreq(val_3+4200);//(9600);
  
  noiseFiltered = hip.next(wNoise.next()); //hip.next(wNoise.next());
  
  //harmFiltered = bp1.next(noiseFiltered)+ bp2.next(noiseFiltered);//*0.1 + bp3.next(noiseFiltered)*0.1 + bp4.next(noiseFiltered)*0.1 + bp5.next(noiseFiltered)*0.1);
 
  int firstEnvelope = (int)envVol.next();
    
  noiseSignal = (noiseFiltered*firstEnvelope)>>6;
  //noiseSignal = (wNoise.next()*firstEnvelope)>>6;//harmFiltered * firstEnvelope;
  
  int modVal_1 = mapModVal.next(val_1);
    
  int freqEnv = (int)(envPh.next()*(modVal_1));
   
  pHasor.setFreq((float)freqEnv); 
  
  ////
 
  modul = pHasor.phMod(noiseSignal);//(int)(noiseSignal>>3)*(pHasor.next()>>3);
  
  finalSig = modul * envPh.next();
  
  del_samps = 128+kFreq.next();
  
}

int updateAudio() {
  
  //audioProcess();
  
  //return finalSig;
   
  return aDel.next(modul, del_samps);

  
}


//void controlProcess(int modVal, int trigEnv, int attack_a, int decay_a, int attack_b, int decay_b) {
  
  ////
  /*
  if(trigEnv == 1) {
    if (!triggered) {
      envPh.start(attack_b, decay_b);
      envVol.start(attack_a, decay_a);
      triggered = true;
    } else {
      triggered = false;
    }
  }
  
  ///
  
  wNoise.setFreq(220);
  
  hip.setResonance(100); //fix
  hip.setCentreFreq(1000); //fix
  
  bp1.setResonance(30);
  bp1.setCentreFreq(2200);
  bp2.setResonance(30);
  bp2.setCentreFreq(3300);
  bp3.setResonance(30);
  bp3.setCentreFreq(4200);
  bp4.setResonance(30);
  bp4.setCentreFreq(6500);
  bp5.setResonance(30);
  bp5.setCentreFreq(9600);
  
  int noiseFiltered = hip.next(wNoise.next());
  
  int harmFiltered = bp1.next(noiseFiltered) + bp2.next(noiseFiltered) + bp3.next(noiseFiltered) + bp4.next(noiseFiltered) + bp5.next(noiseFiltered);
  
  envVol.start(attack_a, decay_a);
  
  int firstEnvelope = (int) envVol.next();
  
  int noiseSignal = harmFiltered * firstEnvelope;
  
  
  int modVal_1 = mapModVal.next(modVal);
  
  
  int freqEnv = (int)(envPh.next()*(modVal_1));
  
  
  pHasor.setFreq((float)freqEnv); 
  
  ////
 
  
  int modul = noiseSignal*pHasor.next();
  
  finalSig = modul * envPh.next();
  */
  
//}

/*
int audioProcess() {
  
  return finalSig;
  
}
*/
