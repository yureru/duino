#define PIN_LED 8
#define PIN_BUTTON 7

byte lastButtonState;
byte ledState = LOW;

unsigned long lastTimeButtonStateChanged = millis();
unsigned long debounceDuration = 50;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  lastButtonState = digitalRead(PIN_BUTTON);
}

void loop() {
  if (millis() - lastTimeButtonStateChanged >= debounceDuration) {
    byte buttonState = digitalRead(PIN_BUTTON);
    if (buttonState != lastButtonState) {
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;

      if (buttonState == HIGH) {
        if (ledState == HIGH) {
          ledState = LOW;
        } else {
          ledState = HIGH;
        }
        digitalWrite(PIN_LED, ledState);
      }
    }
  }
}
