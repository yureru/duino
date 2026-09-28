// Define the control pins based on your color map
const int latchPin = 4; // RED wire (STCP + PL)
const int dataPin  = 5; // BLACK wire (Pin 9 / Q)
const int clockPin = 6; // GREEN wire (Pin 11 / SHCP)

const int headShowerPin = 8; // MOSFET Board Channel 1 (PWM1)
const int handShowerPin = 9; // MOSFET Board Channel 2 (PWM1)
const int jetsFirstSidePin = 10; // MOSFET Board Channel 3 (PWM1)
const int jetsSecondSidePin = 11; // MOSFET Board Channel 4 (PWM1)

// Track the state (ON/OFF) of each output
bool headShowerState = false;
bool handShowerState = false;
bool jetsFirstState = false;
bool jetsSecondState = false;

const int ledPin   = 13; // Onboard LED

enum SpaButton {
  BUTTON_NONE,
  BUTTON_OFF,
  BUTTON_HEAD_SHOWER,
  BUTTON_HANDHELD,
  BUTTON_FULL_BODY,
  BUTTON_FULL_BODY_MASSAGE,
  BUTTON_STEAM,
  BUTTON_UNKNOWN
};

void setup() {
  Serial.begin(9600);
  
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  // Use INPUT_PULLUP to stop the pin from floating when disconnected
  pinMode(dataPin, INPUT_PULLUP); 

  pinMode(ledPin, OUTPUT); // Built-in LED setup

  // Set up Solenoid Pin
  pinMode(headShowerPin, OUTPUT);
  digitalWrite(headShowerPin, LOW); // Start with solenoid OFF
  pinMode(handShowerPin, OUTPUT);
  digitalWrite(handShowerPin, LOW); // Start with solenoid OFF
  pinMode(jetsFirstSidePin, OUTPUT);
  digitalWrite(jetsFirstSidePin, LOW); // Start with solenoid OFF
  pinMode(jetsSecondSidePin, OUTPUT);
  digitalWrite(jetsSecondSidePin, LOW); // Start with solenoid OFF
  
  digitalWrite(latchPin, HIGH);
  digitalWrite(clockPin, LOW);

  digitalWrite(ledPin, LOW);
  
  Serial.println("Monitoring Jacuzzi Panel...");
}

void loop() {
  // 1. Pulse Latch/Load (Red wire)
  digitalWrite(latchPin, LOW);
  delayMicroseconds(10);
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(10);

  // 2. Read the 8 bits from the chip
  byte rawData = shiftIn(dataPin, clockPin, MSBFIRST);

  // 3. Invert the bits! 
  // If idle is 11111111 (255), inverting it makes it 00000000 (0).
  // If a button pulls a line to GND, it becomes a 0 raw, which inverts to a 1.
  byte buttonPressed = ~rawData;

  // 4. Only print if a button is actually pressed (value is greater than 0)
  // and ignore the 255/floating state when disconnected (which inverts to 0)
  if (buttonPressed != 0) {
    // Serial.print("Button Pressed Pattern (Binary): ");
    digitalWrite(ledPin, HIGH);

    SpaButton activeButton = BUTTON_NONE;
    
    switch (buttonPressed) {
      // REPLACE these binary literals (e.g., 0b01000000) with the actual 
      // binary patterns you see on your monitor for each physical button!
      case 0b01000000: activeButton = BUTTON_OFF;          break;
      case 0b00100000: activeButton = BUTTON_HEAD_SHOWER;   break;
      case 0b00010000: activeButton = BUTTON_HANDHELD;     break;
      case 0b00000100: activeButton = BUTTON_FULL_BODY;    break;
      case 0b00001000: activeButton = BUTTON_FULL_BODY_MASSAGE;      break;
      case 0b00000010: activeButton = BUTTON_STEAM;  break;
      default:         activeButton = BUTTON_UNKNOWN;       break;
    }

    // 3. Convert the enum value to a printable string message
    doActionBy(activeButton, buttonPressed);
    
    
    // Print leading zeros so it always shows 8 bits
    // for (int i = 7; i >= 0; i--) {
    //   Serial.print(bitRead(buttonPressed, i));
    // }
    // Serial.println();
  }
  
  delay(250); // Prevent spamming the console while holding a button
  digitalWrite(ledPin, LOW);
}

// Helper function to print your messages
void doActionBy(SpaButton btn, byte rawValue) {
  Serial.print("Action Triggered: ");
  switch (btn) {
    case BUTTON_OFF:
      headShowerState = false;
      handShowerState = false;
      jetsFirstState = false;
      jetsSecondState = false;

      digitalWrite(headShowerPin, LOW);
      digitalWrite(handShowerPin, LOW);
      digitalWrite(jetsFirstSidePin, LOW);
      digitalWrite(jetsSecondSidePin, LOW);
      Serial.println("SYSTEM OFF");
    break;
    case BUTTON_HEAD_SHOWER:
      headShowerState = !headShowerState;
      digitalWrite(headShowerPin, headShowerState ? HIGH : LOW);
      Serial.println("HEAD SHOWER PRESSSED");
      break;
    case BUTTON_HANDHELD:
      handShowerState = !handShowerState;
      digitalWrite(handShowerPin, handShowerState ? HIGH : LOW);
      Serial.println("HANDHELD SHOWER PRESSSED");
      break;
    case BUTTON_FULL_BODY:
      jetsFirstState = !jetsFirstState;
      digitalWrite(jetsFirstSidePin, jetsFirstState ? HIGH : LOW);
      Serial.println("FULL BODY JETS PRESSSED");
      break;
    case BUTTON_FULL_BODY_MASSAGE:
      jetsSecondState = !jetsSecondState;
      digitalWrite(jetsSecondSidePin, jetsSecondState ? HIGH : LOW);
      Serial.println("MASSAGE SPRAY JETS PRESSSED");
      break;
    case BUTTON_STEAM:
      Serial.println("STEAM SHOWER PRESSSED");
      break;
    case BUTTON_UNKNOWN:
      Serial.print("UNKNOWN PATTERN DETECTED (0b");
      Serial.print(rawValue, BIN);
      Serial.println(")");
      break;
    default:
      Serial.println("NONE");
      break;
  }
}