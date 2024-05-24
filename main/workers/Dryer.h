class Dryer {
  const uint8_t MOSFET_PIN;
  unsigned long timeStamp;
  unsigned long timeEnd;

  public:
    Dryer(
      const uint8_t mosfetPin
    ) :
      MOSFET_PIN(mosfetPin)
    {
      pinMode(MOSFET_PIN, OUTPUT);
    }

    bool isWorking() {
      return !!timeEnd;
    }

    void start(unsigned long minutes) {
      timeStamp = millis();
      timeEnd = timeStamp + minutes  * 60 * 1000;
    }

    void stop() {
      timeEnd = 0;
      digitalWrite(MOSFET_PIN, LOW);
    }

    void loop() {
      unsigned long currenTimeStamp = millis();

      if (currenTimeStamp - timeStamp > 1000) {
        timeStamp = currenTimeStamp;

        if (isWorking()) {
          if (dht11.getTemperature() < configMenu.temperature) {
            digitalWrite(MOSFET_PIN, HIGH);
          } else {
            digitalWrite(MOSFET_PIN, LOW);
          }

          if (timeStamp > timeEnd) {
            stop();
          }
        }
      }
    }
};
