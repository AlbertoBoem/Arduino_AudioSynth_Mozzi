
Oscil <BROWNNOISE8192_NUM_CELLS, AUDIO_RATE> bNoise (BROWNNOISE8192_DATA);
Oscil <COS2048_NUM_CELLS, CONTROL_RATE> bMod(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> bCos(COS2048_DATA);

StateVariable <LOWPASS> ntf;
StateVariable <HIGHPASS> hpf;

Ead bPercEnv(CONTROL_RATE);
Ead bPercFreqEnv(CONTROL_RATE);

AutoMap mapFreq(0, 1023, 0.f, 400.f); //255
AutoMap mapMod(0, 1023, 0.f, 100.f);//0, 4000)
AutoMap mapMod2(0, 1023, 0.f, 100.f);

boolean trigger = false;

int genAmp;

void updateControlPercussiVe(int freq_val, int filter_val, int filter_val2, int trigger_val, int attack_val, int decay_val) {
  
  if (trigger_val == 1) {
    if(!trigger) {
      bPercEnv.start(attack_val, decay_val);
      bPercFreqEnv.start(10, 1000); //10 1000
      trigger = true;
    } 
  } else {
      trigger = false;
    }
 
  hpf.setResonance(10);
filter_val2 = mapMod2.next(filter_val2); 
  hpf.setCentreFreq(filter_val2);
  
  freq_val = mapFreq.next(freq_val);
  //bNoise.setFreq((int)bPercFreqEnv.next()+freq_val);
  bNoise.setFreq((genAmp)+freq_val);//bNoise.setFreq((genAmp*2)*70);
  
  ntf.setResonance(70);
  filter_val = mapMod.next(filter_val); 
  bMod.setFreq(filter_val);
  ntf.setCentreFreq((int)bMod.next());//filter_val);
  
  genAmp = (int)bPercEnv.next()>>2;
    
}


int updateAudioPercussiVe() {
  
  //return genAmp*(ntf.next(bNoise.next())>>3); //(ntf.next(bNoise.next()+bNoise.next()))*bPercEnv.next();
  return genAmp*(ntf.next(hpf.next(bNoise.next()))>>8);//bNoise.next())>>8);
}
