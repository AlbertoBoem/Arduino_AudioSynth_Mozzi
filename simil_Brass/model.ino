// Tables to be read
Oscil<PHASOR256_NUM_CELLS, AUDIO_RATE> aTr(PHASOR256_DATA);
Oscil<COS2048_NUM_CELLS, AUDIO_RATE> aMod(COS2048_DATA);

LowPassFilter lpf;

AutoMap mapPitch(0, 1023, 0, 1000);
AutoMap mapPitch_1(0, 1023, 0, 2000);

Ead envelope(CONTROL_RATE);

Q24n8 pitch_f;

int gain, modGain;

boolean trigg = false;


void modelControl(int pitch_val, int pitch_val_1, int duration, int attack, int checkThis) {
  
  pitch_val = mapPitch.next(pitch_val);
  pitch_val_1 = mapPitch_1.next(pitch_val);
  
  //Q16n16 note_pitch = float_to_Q16n16(pitch_val);
  //Q16n16 midi_note = note_pitch;  
  //pitch_f = Q16n16_to_Q24n8(Q16n16_mtof(midi_note));
  
  aTr.setFreq(pitch_val+1);   //_Q24n8(pitch_f);
  aMod.setFreq(pitch_val);  //_Q24n8(pitch_f);
  
  if(pitch_val > 10) {
    if(!trigg) {
     int decay = duration - attack;
     envelope.start(attack,decay);
     trigg = true;
    } else {
      trigg = false;
    }
  }
  
  //gain = (int)envelope.next();
  
  modGain = aMod.next();
  
  lpf.setResonance(100);
  lpf.setCutoffFreq(modGain);
 
    
}

int modelAudio() {
  
  //long signal = aTr.next();
  return lpf.next(aTr.next());//(gain*(lpf.next(aTr.next())>>8)); //without gain* lpf.next(aTr.next())
  //envelope.next()*(aMod.next()+aMod.next());//modGain;
  //lpf.next(signal)>>3;
  
}
