Oscil <COS2048_NUM_CELLS, AUDIO_RATE> bCos_1(COS2048_DATA);
Oscil <COS2048_NUM_CELLS, AUDIO_RATE> bMod_1(COS2048_DATA);


LowPassFilter lpf;

Ead bPercEnv_1(CONTROL_RATE);
Ead bPercFreqEnv_1(CONTROL_RATE);

AutoMap mapFreq_1(0, 1023, 0.f, 400.f); //255
AutoMap mapMod_1(0, 1023, 0.f, 100.f);//0, 4000)
AutoMap mapMod2_1(0, 1023, 0.f, 100.f);

boolean trigger_1 = false;

int genAmp_1;

void updateControlPercussiVe_1(int freq_val_1, int filter_val_1, int filter_val2_1, int trigger_val_1, int attack_val_1, int decay_val_1) {
  
  if (trigger_val_1 == 1) {
    if(!trigger_1) {
      bPercEnv_1.start(attack_val_1, decay_val_1);
      bPercFreqEnv_1.start(10, 2000); //10 1000
      trigger_1 = true;
    } 
  } else {
      trigger_1 = false;
    }
  
  filter_val_1 = mapMod.next(filter_val_1);
  bMod_1.setFreq(filter_val_1);
 
  freq_val_1 = mapFreq_1.next(freq_val_1);
  //bNoise.setFreq((int)bPercFreqEnv.next()+freq_val);
  bCos_1.setFreq(freq_val_1);//bNoise.setFreq((genAmp*2)*70);
  
  lpf.setResonance(50);
  lpf.setCutoffFreq(bPercFreqEnv_1.next()*bMod_1.next());//filter_val);
  
  genAmp_1 = (int)bPercEnv_1.next();
    
}


int updateAudioPercussiVe_1() {
  
  //return genAmp*(ntf.next(bNoise.next())>>3); //(ntf.next(bNoise.next()+bNoise.next()))*bPercEnv.next();
  //return genAmp*(ntf.next(hpf.next(bNoise.next()))>>8);//bNoise.next())>>8);
  return genAmp_1*(lpf.next(bCos_1.next())>>8);
}
