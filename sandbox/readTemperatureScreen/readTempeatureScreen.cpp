#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

OneWire pinWire(7);

DallasTemperature sensors(&pinWire);

void setup() {
    delay(1000);
    Serial.begin(9600);
    sensors.begin();
    lcd.begin(16, 2);
    lcd.setCursor(0, 0);
}

void loop() {
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(temp);
    delay(1000);
}