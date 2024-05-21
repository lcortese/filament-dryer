class Encoder {
  private:
    const byte LEFT_PIN;
    const byte RIGHT_PIN;
    const byte BUTTON_PIN;
    bool prevDown;
    int rotaryPosition;
    unsigned long lastMillis;

    bool isDown() {
      return !digitalRead(BUTTON_PIN);
    }
    bool isLeft() {
      return digitalRead(LEFT_PIN);
    }
    bool isRight() {
      return digitalRead(RIGHT_PIN);
    }
  
  public:
    Encoder(byte leftPin, byte rightPin, byte buttonPin): LEFT_PIN(leftPin), RIGHT_PIN(rightPin), BUTTON_PIN(buttonPin)  {
      pinMode(LEFT_PIN, INPUT);
      pinMode(RIGHT_PIN, INPUT);
      pinMode(BUTTON_PIN, INPUT);
    };

    bool left;
    bool right;
    bool swDown;
    bool swUp;

    void update() {
      swDown = false;
      swUp = false;
      left = false;
      right = false;

      if (!rotaryPosition && isLeft() != isRight()) {
        rotaryPosition = isRight() - isLeft();
      }

      if (rotaryPosition && isLeft() && isRight()) {
        left = rotaryPosition > 0;
        right = !left;
        rotaryPosition = 0;
      }

      if (millis() > lastMillis + DEBOUNCE_DELAY) {
        swDown = isDown();
        swUp = prevDown && !swDown;

        prevDown = swDown;
        lastMillis = millis();
      }
    }
};
