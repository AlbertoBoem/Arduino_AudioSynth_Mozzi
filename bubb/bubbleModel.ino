
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> bCos(COS2048_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> bCos_2(COS2048_DATA);

Ead envelope_1(AUDIO_RATE);
Ead envelope_2(CONTROL_RATE);

//StateVariable <HIGHPASS> hpf;
StateVariable <LOWPASS> lpf;

AutoMap map1(0, 1023, 0, 600);

boolean trigg = false;

void bubbleControl(int the_freq, int centreFreq, int checkButton, int attack_1, int decay_1, int attack_2, int decay_2) {
  
  if(checkButton == 1) {
    if(!trigg) {
     envelope_1.start(attack_1,decay_1);
     envelope_2.start(attack_2,decay_2);
     trigg = true;
    } else {
      trigg = false;
    }
  }
  
  the_freq = map1.next(the_freq); //it works good with very low or very high values
  
  bCos.setFreq((the_freq)*envelope_1.next()); //600
  
  bCos_2.setFreq((120)*envelope_2.next()); //120
  
  //hpf.setResonance(50);
  //hpf.setCentreFreq(centreFreq);
  
  lpf.setResonance(250); //50
  lpf.setCentreFreq(550); //250
  
  
}


int bubbleAudio() {
  
  //return hpf.next(bCos_2.next()*(bCos.next()+bCos.next())>>6); //high
  return lpf.next(bCos_2.next()*(bCos.next()+bCos.next())>>7); //low
}
