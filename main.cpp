#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD address and size
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED pins
int redLED = 8;
int greenLED = 9;

void setup() {
  Serial.begin(9600);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Dark Pattern");
  lcd.setCursor(0, 1);
  lcd.print("Detector Ready");

  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
}

void loop() {

  if (Serial.available() > 0) {

    String message = Serial.readStringUntil('\n');
    message.trim();

    lcd.clear();

    if (message.startsWith("DARK")) {

      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);

      lcd.setCursor(0, 0);
      lcd.print("DARK PATTERN");

      lcd.setCursor(0, 1);
      lcd.print(message.substring(5, 21));

    }

    else if (message.startsWith("SAFE")) {

      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);

      lcd.setCursor(0, 0);
      lcd.print("SAFE MESSAGE");

      lcd.setCursor(0, 1);
      lcd.print("No Dark Pattern");

    }
  }
}

