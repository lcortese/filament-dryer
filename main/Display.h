#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

class Display {
  LiquidCrystal_I2C lcd;
  const static uint8_t ROWS_COUNT = 2;
  const static uint8_t COLUMNS_COUNT = 16;

  public:
    Display() : lcd(0x27, 2, 1, 0, 4, 5, 6, 7) {}

    void setup() {
      lcd.setBacklightPin(3, POSITIVE);
      lcd.begin(COLUMNS_COUNT, ROWS_COUNT);
    }

    void on() {
      lcd.setBacklight(HIGH);
    }

    void off() {
      lcd.setBacklight(LOW);
    }

    void clear() {
      lcd.clear();
    }

    void print(const String lines[]) {
      for (uint8_t i = 0; i < ROWS_COUNT; i++) {
          lcd.setCursor(0, i);
          String line = lines[i];

          while (line.length() < COLUMNS_COUNT) {
            line = line + " ";
          }

          lcd.print(line);
      }
    }
};