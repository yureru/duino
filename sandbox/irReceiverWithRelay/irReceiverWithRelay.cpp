#include <IRremote.hpp>

const int IR_RECEIVER_PIN = 7;
const int SSR_1_PIN = 8;
unsigned long lastActionTime = 0;
const unsigned long THRESHOLD = 500; // 500ms delay between allowed toggles
bool onOffState = false;
#define BTN_ON_OFF 0xBA45FF00

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);
    pinMode(SSR_1_PIN, OUTPUT);
}

void loop() {
    if (IrReceiver.decode()) {
        Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
        Serial.println("--");
        IrReceiver.printIRResultShort(&Serial);
        Serial.println("----");

        uint32_t rawData = IrReceiver.decodedIRData.decodedRawData;
        handleIrInput(rawData);
        IrReceiver.resume();
    }

    // // TODO: update condition; if IR detected on and off
    // if (false) {
    //     digitalWrite(SSR_1_PIN, HIGH);
    // } else if (false) {
    //     digitalWrite(SSR_1_PIN, LOW);
    // }
}

void handleIrInput(uint32_t cmd) {
    if (cmd != 0 && (millis() - lastActionTime > THRESHOLD)) {
        switch (cmd) {
            case BTN_ON_OFF:
                onOffState = !onOffState; // Toggle the variable
                digitalWrite(SSR_1_PIN, onOffState ? HIGH : LOW);
                Serial.println("Action: On or Off. Current: " + onOffState ? "HIGH" : "LOW");
                Serial.println(onOffState);
                break;
                default:
                Serial.print("Unknown Command: ");
                // Serial.println(onOffState);
                // Serial.println(command, HEX);
                break;
        }
    }
}

// void loop() {
//     if (IrReceiver.decode()) {
//         uint32_t rawData = IrReceiver.decodedIRData.decodedRawData;
        
//         // 1. Ignore "0" (repeats) 
//         // 2. Check if enough time has passed (threshold)
//         if (rawData != 0 && (millis() - lastActionTime > THRESHOLD)) {
            
//             // Check for your specific button code (e.g., 0xBA45FF00)
//             if (rawData == 0xBA45FF00) { 
//                 ledState = !ledState; // Toggle the variable
//                 digitalWrite(LED_PIN, ledState ? HIGH : LOW);
                
//                 lastActionTime = millis(); // Reset the timer
//                 Serial.println(ledState ? "ON" : "OFF");
//             }
//         }
        
//         IrReceiver.resume();
//     }
// }
