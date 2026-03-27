#define PIN_LED 8
#define PIN_BUTTON 7

byte state = LOW;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  if (digitalRead(PIN_BUTTON) == HIGH) {
    state = state == HIGH ? LOW : HIGH;
    digitalWrite(PIN_LED, state);
    // by doing it this way, if button is pressed fast we don't get a read
    // or if we leave it pressed it starts switching states while being pressed
    delay(500);
  }
}
