int readOm(byte analogPin) {  
  int raw = 0;
  int Vin = 5;
  float Vout = 0;
  float R1 = 1000;
  float buffer = 0;

  raw = analogRead(analogPin);
  if (raw) {
    buffer = raw * Vin;
    Vout = (buffer) / 1024.0;
    buffer = (Vin / Vout) - 1;   
    return R1 * buffer; // это R2   
  }
}
