void workIndication() {
  if (millis() > startProgramTimer + checkInterval) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
  }
}

                                                                                                                                                                
