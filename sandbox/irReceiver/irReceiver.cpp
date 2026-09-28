#include <IRremote.hpp>

const int IR_RECEIVER_PIN = 7;

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
    if (IrReceiver.decode()) {
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        IrReceiver.printIRResultShort(&Serial);
        IrReceiver.resume();
    }
}