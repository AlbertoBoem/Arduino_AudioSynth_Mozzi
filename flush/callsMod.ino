/*
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> fOsc_1(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> fOsc_2(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> fOsc_3(COS2048_DATA);

AutoMap mapF_1(0, 1023, 0, 600);
AutoMap mapF_2(0, 1023, 0, 600);
AutoMap mapCentF(0, 1023, 0, 500);

StateVariable <BANDPASS> bpf_1;
StateVariable <BANDPASS> bpf_2;

LowPassFilter lpf;

int final_sig;


void modControl(int f_1, int f_2, int val_1, int val_2, int val_3, int centreFr) {
  
  f_1 = mapF_1.next(f_1);
  f_2 = mapF_2.next(f_2);
  
  fOsc_1.setFreq(220);//f_1);
  fOsc_2.setFreq(440);//f_2);
  
  int glue_1 = (fOsc_1.next()*fOsc_2.next());
  
  int brew_1 = glue_1 * val_1;
  int brew_2 = brew_1 * val_2;
  int frul_1 = brew_2 + val_3;
  
  fOsc_3.setFreq(frul_1);
  
  bpf_1.setResonance(100);
  centreFr = mapCentF.next(centreFr);
  bpf_1.setCentreFreq(centreFr);
  
 
    
}

int modAudio() {
  
  int glue_2 = bpf_1.next(fOsc_3.next());
  
  lpf.setResonance(100);
  lpf.setCutoffFreq(500);
  
  final_sig = lpf.next(glue_2);
  
  return (final_sig+final_sig)>>3;
  
}
*/
