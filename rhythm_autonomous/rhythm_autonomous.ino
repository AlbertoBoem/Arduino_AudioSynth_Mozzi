#include <MozziGuts.h>
#include <Metronome.h>
#include <SampleHuffman.h>
#include <mozzi_rand.h>
#include <Oscil.h>
#include <mozzi_fixmath.h>
#include <mozzi_analog.h>
#include <AutoMap.h>
#include <LowPassFilter.h>

#include <tables/cos2048_int8.h>
#include <tables/triangle2048_int8.h>

Oscil <COS2048_NUM_CELLS, AUDIO_RATE> aCos (COS2048_DATA);
Oscil <TRIANGLE2048_NUM_CELLS, AUDIO_RATE> aTri (TRIANGLE2048_DATA);

LowPassFilter lpf;

const char NUM_SAMPLES = 5;

//const int PIN_1 = 1;
//const int PIN_2 = 2;
const int PIN_3 = 1;
//const int PIN_5 = 5;

const int pin13 = 13;
//const int PIN_4 = 4;

int valo_1 = 100;
int valo_2 = 200;
int valo_3 = 300; //float valo_3 = 0;
int valo_5 = 100;

AutoMap mapVal1(0, 1023, 0, 500);
AutoMap mapVal2(0, 1023, 0, 500);
AutoMap mapVal3(0, 1023, 0, 400);//mapVal3(0, 1023, 0.f, 6000.f);
AutoMap mapVal5(0, 1023, 0, 255);

Metronome kMetro(800); // enough delay so samples don't overlap, because the load would be too much

int aFreq = 0;
int bFreq = 0;

void setup() {
  
  startMozzi();
  
  Serial.begin(115200);
  
  pinMode(pin13, OUTPUT);
  
  lpf.setResonance(150);

}



void updateControl(){
  
  static unsigned int counter;
  
  float valo_3 = mozziAnalogRead(PIN_3);
  //int val_4 = digitalRead(PIN_4);
  valo_3 = mapVal3.next(valo_3);
  
  /*if (valo_3 > 100){
    kMetro.setBPM(10.f);
  } if (valo_3 < 350) {
    kMetro.setBPM(100.f);
  }*/
  
  counter++;
  
  if (valo_3 > 250){
    kMetro.setBPM(250+valo_3);
  } else {//(val_4==1) {
   kMetro.setBPM(550-(valo_3));
  }
   
  
  
  //int valo_1 = mozziAnalogRead(PIN_1);
  //int valo_2 = mozziAnalogRead(PIN_2);
  
  //int valo_5 = mozziAnalogRead(PIN_5);  
  //valo_5 = mapVal5.next(valo_5);
  
  lpf.setCutoffFreq(valo_5);
  
  //valo_1 = mapVal1.next(valo_1);
  //valo_2 = mapVal2.next(valo_2);
  
  if (counter==120) {
  //if (counter==val_4)
  //if(valo_1>100) //if(counter==valo_1) 
    kMetro.stop();
    digitalWrite(pin13, LOW);
  
  }
  if(counter==133) {
    //if(counter==val_4)
  //if(valo_2<300)//if(counter==valo_2)
   
    kMetro.start();
    counter = 0;
    digitalWrite(pin13, HIGH);
  
  }
  
  
  
  //Serial.println(counter);
  //Serial.print("-");
  Serial.println(counter);
  
  if(kMetro.ready()) {
    
    switch(rand(NUM_SAMPLES)) {
      
      case 0:
      aFreq = 350+valo_1;
      bFreq = 0;
      break;
      
      case 1:
      aFreq = 85;
      bFreq = 100;
      break;
      
      case 2:
      aFreq = 220;
      bFreq = 0;
      break;
      
      case 3:
      aFreq = 100+valo_1;
      bFreq = 220;
      break;
      
      case 4:
      aFreq = 300;
      bFreq = 0;
      break;
    }
  }
  
  aCos.setFreq(aFreq);
  aTri.setFreq(bFreq);
  
}


int updateAudio(){ 
  int asig = (int)
  lpf.next(aCos.next()+aTri.next())*2;
  return asig>>8;
}


void loop() {
  audioHook();
}
