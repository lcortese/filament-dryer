class Fan {
  const uint8_t PIN;

  public:
    Fan(uint8_t pin): PIN(pin) {
      pinMode(PIN, OUTPUT);
    }

    void setSpeed(uint8_t value) {
      analogWrite(PIN, min(255 * value / 100, 255));
    }
};