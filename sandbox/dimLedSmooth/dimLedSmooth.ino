#define PIN_LED 10

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  for (int brightness = 0; brightness <= 255; brightness += 5) {
    analogWrite(PIN_LED, brightness);
    delay(50);
  }
  
  for (int brightness = 255; brightness >= 0; brightness -= 5) {
    analogWrite(PIN_LED, brightness);
    delay(50);
  }
}
