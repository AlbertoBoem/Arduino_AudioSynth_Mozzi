//pot 3 - filter cutoff freq

#include <MozziGuts.h>
#include <Oscil.h>
#include <mozzi_fixmath.h>
#include <mozzi_midi.h>
#include <mozzi_rand.h>
#include <LowPassFilter.h>
#include <Ead.h>
#include <AutoMap.h>
#include <StateVariable.h>
#include <AutoMap.h>
#include <ADSR.h>
#include <Smooth.h>
#include <Line.h>
#include <EventDelay.h>

#include <tables/cos2048_int8.h> 


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

//
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> fOsc_1(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> fOsc_2(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> fOsc_3(COS2048_DATA);

AutoMap mapF_1(0, 1023, 0, 600);
AutoMap mapF_2(0, 1023, 0, 600);
AutoMap mapCentF(0, 1023, 0, 500);

StateVariable <BANDPASS> bpf_1;
StateVariable <BANDPASS> bpf_2;

LowPassFilter lpf;

Ead aEnvelope(CONTROL_RATE);

int final_sig;
//


boolean triggered_1 = false;


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
  pin3_val = mozziAnalogRead(PIN_3);
  
  //modControl(pin1_val, pin2_val, 2, 12, 24, pin3_val);
  
  Serial.println(pin1_val);
  
  if (button_in == 1) {    //&& env_sel_2 == 1) 
     if(!triggered_1) {
      aEnvelope.start(10,100);
      triggered_1 = true;
     } else {
    triggered_1 = false;
    }
  }
  
  fOsc_1.setFreq(100);//f_1);
  fOsc_2.setFreq(100);//f_2);
  
  float glue_1 = (aEnvelope.next()*fOsc_1.next())*(aEnvelope.next()*fOsc_2.next());
  
  float brew_1 = glue_1 * 2.5;
  float brew_2 = brew_1 * 2.5;
  float frul_1 = brew_2 + 10;
  
  fOsc_3.setFreq(frul_1);
  
  bpf_1.setResonance(20);
  //centreFr = mapCentF.next(pin3_val);
  bpf_1.setCentreFreq(pin3_val);
  

  
  
}

int updateAudio() {
  
  //modAudio();
  
  int glue_2 = (int)bpf_1.next(fOsc_3.next());
  
  lpf.setResonance(100);
  lpf.setCutoffFreq(1000);
  
  final_sig = lpf.next(glue_2);
  
  return (final_sig+final_sig)>>3;
  
}
