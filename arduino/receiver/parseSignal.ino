/* Данные для конерсии сигналов колес и триммера */
#define FORWARD_MOTR  20
#define STOP_MOTOR    10
#define REVERSE_MOTOR 0
#define TRIMMER_ON    1
#define TRIMMER_OFF   0

void relayActivation(uint8_t* data) {
  if (data && sizeof(data)) {
    Serial.print("Left wheel: ");
    switchWheelOutput(data[0], leftForwardPin, leftReversePin);
    Serial.print(" Rigth wheel: ");
    switchWheelOutput(data[1], rightForwardPin, rightReversePin);
    swithTrimmerOutput(data[2]);
    Serial.println(" ");
  }
}

void switchWheelOutput(uint8_t value, byte forwardPin, byte reversPin) {
  if (value == FORWARD_MOTR) {
    digitalWrite(reversPin, LOW);
    digitalWrite(forwardPin, HIGH);
    Serial.print("FORWAR");
  } else if (value == REVERSE_MOTOR) {
    digitalWrite(forwardPin, LOW);
    digitalWrite(reversPin, HIGH);
    Serial.print("REVERSE");
  } else if (value == STOP_MOTOR || !value) {
    digitalWrite(forwardPin, LOW);
    digitalWrite(reversPin, LOW);
    Serial.print("STOP");
  }
}

void swithTrimmerOutput(uint8_t value) {
  Serial.print(" ");
  if (value) {
    digitalWrite(trimmerPin, HIGH);
    Serial.print("TRIMMER: ON");
  } else {
    digitalWrite(trimmerPin, LOW);
    Serial.print("TRIMMER: OFF");
  }
}


void robotStop() {
  digitalWrite(leftForwardPin, LOW);
  digitalWrite(leftReversePin, LOW);
  digitalWrite(rightForwardPin, LOW);
  digitalWrite(rightReversePin, LOW);
  digitalWrite(trimmerPin, LOW);
  Serial.println("STOP");
  delay(1000);
}
