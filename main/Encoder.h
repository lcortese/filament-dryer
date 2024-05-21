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

      rotaryPosition = rotaryPosition - isLeft() + isRight();

      if (millis() < lastMillis + DEBOUNCE_DELAY) {
        return;
      }

      if (isLeft() && isRight()) {
        left = rotaryPosition > 0;
        right = rotaryPosition < 0;
        rotaryPosition = 0;
      }

      swDown = isDown();
      swUp = prevDown && !swDown;

      prevDown = swDown;
      lastMillis = millis();
    }
};