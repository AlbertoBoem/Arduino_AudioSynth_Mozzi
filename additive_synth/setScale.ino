AutoMap mapFreq(0, 1023, 5, 100);
AutoMap mapFT(0, 1023, 0, 12);
AutoMap mapSet(0, 1023, 4, 64);

int tuneArraySel;

int tuneArrI;

int selected_scale;


void selectScale(int sel_array, float fundamental) {
  
  float tunedArray[6][13] = {   
    {1, 1.285, 1.5, 1.75, 2, 2.25, 2.57, 2.8, 3, 3.11, 3.5, 3.857, 4}, // 0 overtone series
    {1, 1.166, 1.33, 1.5, 1.75, 2, 2.332, 2.66, 3.0, 3.5, 4, 4.664, 6}, // 1 pentatonic
    {1, 1.166, 1.5, 2, 2.33, 3.0, 4, 4.66, 6.0, 8, 9.33, 12, 16}, // 2 minor
    {1, 1.25, 1.5, 2, 2.5, 3.0, 4, 5.0, 6.0, 8, 10, 12, 16}, // 3 major
    {1, 1.25, 1.56, 2, 2.5, 3.12, 4, 5.0, 6.24, 8, 10, 12.48, 16 }, // 4 augmented arpeggio
    {1, 1.071, 1.25, 1.33, 1.5, 1.56, 1.890, 2.0, 2.142, 2.5, 2.66, 3.0, 3.12} // 5 hicaz - arab scale  
  };

  tuneArraySel = sel_array;

  fundamental = mapFreq(fundamental);

  tuneArrI = mapFT(fundamental); //tuning array index
    
  selected_scale = tunedArray[tuneArraySel][tuneArrI] * 44; //the fundamental

}


//retrun the pitch/scale

int selScale() {
  
  return selected_scale;
  
}

