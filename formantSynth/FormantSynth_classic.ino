/*
NOTES : 
- it sounds very distorted!
-'O' is not recognizable
*/

Line <unsigned int> aGain;

Ead mainEnvelope_1(CONTROL_RATE);

// Tables to be read
Oscil<PHASOR256_NUM_CELLS, AUDIO_RATE> aVoice_1(PHASOR256_DATA);
Oscil<SIN2048_NUM_CELLS, CONTROL_RATE> aMod_1(SIN2048_DATA);

// Band pass filter
StateVariable <BANDPASS> bp_f1_1; //formant filters
StateVariable <BANDPASS> bp_f2_1; //     ''
StateVariable <BANDPASS> bp_f3_1; //     ''

// Auto Maps
//good to have it here, edit the proper and desired mapping
AutoMap voiceMap_1(0,1023,0,100);
AutoMap selMap_1(0,1023,0,100);
AutoMap modMap_1(0,1023,0.0f,200.0f);

AutoMap map_f1_1(0,1023,400,1000);
AutoMap map_f2_1(0,1023,900,2000);

// Values
boolean triggered_1 = false;

int mainEvelopeGain_1 = 0; //start at zero

int f1_1, f2_1, f3_1; //formant filters freq

int final_voice_1;

int final_1;

float intensity = 100.0;

int soundSource;



// set function
void setFormantSynth_1() {
 
  //aVoice.setFreq(100); // to set  

}


void updateFormantSynthControl_1(int sel_vowel_1, int voice_freq_1, float mod_freq_1, int trigger, int attack_main_1, int decay_main_1) { 
  
  
  if (trigger == 1) {
     if (!triggered_1) {
      mainEnvelope_1.start(attack_main_1, decay_main_1);
      //vEnvelope.start(voice_attack, voice_decay);
      triggered_1 = true;
    } 
  } else {
      triggered_1 = false;
  }
  
  //Select Scale
  //0 overtone - 1 pentatonic - 2 minor - 3 major - 4 arpeggio - 5 arab scale
  selectScale(5, voice_freq_1);
  
  //int freqVoice = voiceMap.next(voice_freq); //int voice_freq
  
  aVoice_1.setFreq(selScale());//voice_freq_1);
  
  mod_freq_1 = modMap_1.next(mod_freq_1);
  aMod_1.setFreq(mod_freq_1);
  
  
  /*
  //Modulation of the source - tremolo
  
  unsigned int vibrato = (128u + aMod_1.next())<<8;//(int)aMod_1.next();
  aGain.set(vibrato, AUDIO_RATE / CONTROL_RATE);
  soundSource = (aVoice_1.next()*aGain.next())>>8;
  
  //put 'soundSource' instead of 'aVoice_1.next()' in 'updateAudio'
  */
   
  int vowel_selection_1 = sel_vowel_1;
  
  switch(vowel_selection_1) { // sel_vowel
  
  //A
  case 0:
  f1_1 = 710; 
  f2_1 = 1100; 
  f3_1 = 2640;
  break;
  
  //E
  case 10:
  f1_1 = 550; 
  f2_1 = 1770; 
  f3_1 = 2490;
  break;
  
  //I
  case 20:
  f1_1 = 400; 
  f2_1 = 1900; 
  f3_1 = 2550;
  break;
  
  //O
  case 30:
  f1_1 = 440;  
  f2_1 = 1000; 
  f3_1 = 2250;
  break; 
  
  //U
  case 40:
  f1_1 = 450; 
  f2_1 = 1030; 
  f3_1 = 2380;
  break;
  
  }

  
  
  mainEvelopeGain_1 = (int) mainEnvelope_1.next()>>3;
  
  bp_f1_1.setResonance(100); //resonance 100
  bp_f1_1.setCentreFreq(f1_1);  //f1);
  
  bp_f2_1.setResonance(100);
  bp_f2_1.setCentreFreq(f2_1);  //f2);
  
  bp_f3_1.setResonance(50);
  bp_f3_1.setCentreFreq(f3_1);   //f3);
  
  //mainEvelopeGain_1 = (int) mainEnvelope_1.next()>>3;
  
}


int updateFormantSynthAudio_1() {
  
  //final = (bp_f1.next(aVoice.next()*0.1)+bp_f2.next(aVoice.next()*0.1)+bp_f3.next(aVoice.next()*0.1));
//final_1 = mainEvelopeGain_1*((bp_f1_1.next(aVoice_1.next()*0.1)+bp_f2_1.next(aVoice_1.next())*0.1+bp_f3_1.next(aVoice_1.next())*0.1));
int modular = aMod_1.next()>>8;
final_1 = mainEvelopeGain_1*((((bp_f1_1.next(aVoice_1.next())*0.1)+bp_f2_1.next(aVoice_1.next())*0.1+bp_f3_1.next(aVoice_1.next())*0.1))*modular);
  //mainEvelopeGain_1*(bp_f1.next(aVoice.next()*0.1)+bp_f2.next(aVoice.next())*0.1);
  return final_1>>3;//* mainEvelopeGain;

  //return finalAmp(mainEvelopeGain, (bp_f1.next(aVoice.next())+bp_f2.next(aVoice.next())+bp_f3.next(aVoice.next()))>>1);
  
}
