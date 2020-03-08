void trimmer(byte readPin){
  byte buttonState = digitalRead(readPin);
  if(buttonState == 1) {
    emitData[2] = TRIMMER_OFF;
  } else {
    emitData[2] = TRIMMER_ON;
  }
}
