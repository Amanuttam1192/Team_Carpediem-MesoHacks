//clap refers to the noise or the sound
int lastSoundValue;
int soundValue;
long lastNoiseTime = 0;
long currentNoiseTime = 0;
long lastLightChange = 0;
int relayStatus = HIGH;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(signalToRelayPin, OUTPUT);
}

void loop() {
  soundValue = digitalRead(sensorPin);
  currentNoiseTime = millis();

  if (soundValue == 1) { // if there is currently a noise

    if (
      (currentNoiseTime > lastNoiseTime + 200) && // to debounce a sound occurring in more than a loop cycle as a single noise
      (lastSoundValue == 0) &&  // if it was silent before
      (currentNoiseTime < lastNoiseTime + 800) && // if current clap is less than 0.8 seconds after the first clap
      (currentNoiseTime > lastLightChange + 1000) // to avoid taking a third clap as part of a pattern
    ) {

      relayStatus = !relayStatus;
      digitalWrite(signalToRelayPin, relayStatus);
      lastLightChange = currentNoiseTime;
     }

     lastNoiseTime = currentNoiseTime;
  }

  lastSoundValue = soundValue;
}
