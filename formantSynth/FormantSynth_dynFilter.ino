/*
NOTES : 
- it sounds very distorted!
-'O' is not recognizable
*/

Ead mainEnvelope(CONTROL_RATE);

// Tables to be read
Oscil<PHASOR256_NUM_CELLS, AUDIO_RATE> aVoice(PHASOR256_DATA);

// Band pass filter
StateVariable <BANDPASS> bp_f1; //formant filters
StateVariable <BANDPASS> bp_f2; // *
StateVariable <BANDPASS> bp_f3; // *

// Auto Maps
//good to have it here, edit the proper and desired mapping
AutoMap voiceMap(0,1023,0,1000);
AutoMap selMap(0,1023,0,100);

AutoMap map_f1(0,1023,400,1000);
AutoMap map_f2(0,1023,900,2000);

// Values
boolean triggered = false;

int mainEvelopeGain = 0; //start at zero

int f1, f2, f3; //formant filters freq

int final_voice;

int final;



// set function
void setFormantSynth() {
  
  //aVoice.setFreq(100); // to set
  
  
}


//removed : int voice_attack, int voice_decay, 
/*
void updateFormantSynthControl(int sel_vowel, int voice_freq, int attack_main_2, int decay_main_2) { /*, //int
                               int threshold_2, int trigger_2, 
                               int attack_main_2, int decay_main_2) {*/
  
  /*if (trigger_2 > threshold_2) {
    if (!triggered_2) {
      mainEnvelope_2.start(attack_main_2, decay_main_2);
      //vEnvelope.start(voice_attack, voice_decay);
      triggered_2 = true;
    } 
  } else {
      triggered_2 = false;
    }
  */
/*  
  if (attack_main_2 = 1) {
     if (!triggered_2) {
      mainEnvelope_2.start(100, 1000);
      //vEnvelope.start(voice_attack, voice_decay);
      triggered_2 = true;
    } 
  } else {
      triggered_2 = false;
  }
  
  //Serial.println(attack_main_2);

  //aInterpolate.set(voice_freq, AUDIO_STEPS_PER_CONTROL);
  
  //Q16n16 interpolatedFreq = aInterpolate.next();
  
  //int freqVoice = voiceMap.next(interpolatedFreq);
  
  //mainEnvelope_2.start(attack_main_2, decay_main_2);

  int smoothedFreq = aSmooth.next(voice_freq);
  
  int freqVoice = voiceMap.next(smoothedFreq); //int voice_freq
  
  aVoice.setFreq(freqVoice);
  
  int vowel_selection = selMap.next(sel_vowel);
  
  switch(vowel_selection) { // sel_vowel
  
  //A
  case 0:
  f1 = 710; f2 = 1100; f3 = 2640;
  break;
  
  //E
  case 10:
  f1 = 550; f2 = 1770; f3 = 2490;
  break;
  
  //I
  case 20:
  f1 = 400; f2 = 1900; f3 = 2550;
  break;
  
  //O
  case 30:
  f1 = 440;  f2 = 1000; f3 = 2250;
  break; 
  
  //U
  case 40:
  f1 = 450; f2 = 1030; f3 = 2380;
  break;
  
  }

  
  bp_f1.setResonance(100); //resonance 100
  bp_f1.setCentreFreq(f1);  //f1);
  
  bp_f2.setResonance(100);
  bp_f2.setCentreFreq(f2);  //f2);
  
  bp_f3.setResonance(50);
  bp_f3.setCentreFreq(f3);   //f3);
  
  
  mainEvelopeGain = (int) mainEnvelope_2.next()>>3;
  
  //final_voice = (bp_f1.next(aVoice.next())+bp_f2.next(aVoice.next())+bp_f3.next(aVoice.next()))>>8;
  
}
*/

void updateFormantSynthControl(int voice_freq, int sel_f1, int sel_f2, int attack_main) { 
  
  if (attack_main == 1) {
     if (!triggered) {
      mainEnvelope.start(100, 1000);
      //vEnvelope.start(voice_attack, voice_decay);
      triggered = true;
    } 
  } else {
      triggered = false;
  }
  
  
  //int freqVoice = voiceMap.next(voice_freq); //int voice_freq
  
  aVoice.setFreq(voice_freq);
  
  f1 = map_f1.next(sel_f1);
  
  f2 = map_f2.next(sel_f2);
  
  
  bp_f1.setResonance(100); //resonance 100
  bp_f1.setCentreFreq(f1);  //f1);
  
  bp_f2.setResonance(100);
  bp_f2.setCentreFreq(f2);  //f2);
  
  //bp_f3.setResonance(50);
  //bp_f3.setCentreFreq(2500);   //f3);
  
  mainEvelopeGain = (int) mainEnvelope.next();
  
}


int updateFormantSynthAudio() {
  
  //final = (bp_f1.next(aVoice.next()*0.1)+bp_f2.next(aVoice.next()*0.1)+bp_f3.next(aVoice.next()*0.1));
  final = mainEvelopeGain*(bp_f1.next(aVoice.next()*0.1)+bp_f2.next(aVoice.next())*0.1);
  return final;//* mainEvelopeGain;
  //return finalAmp(mainEvelopeGain, (bp_f1.next(aVoice.next())+bp_f2.next(aVoice.next())+bp_f3.next(aVoice.next()))>>1);
  
}
