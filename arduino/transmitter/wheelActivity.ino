void setWheelActivity(byte readPin, byte index) {
  int r = readOm(readPin);
  if (r >= 4000) {
    emitData[index] = FORWARD_MOTR;
  } else if (r <= 1000) {
    emitData[index] = REVERSE_MOTOR;
  } else {
    emitData[index] = STOP_MOTOR;
  }
}
