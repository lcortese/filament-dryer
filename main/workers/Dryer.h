class Dryer {
  const uint8_t MOSFET_PIN;
  unsigned long startTimeStamp;
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
      startTimeStamp = timeStamp;
      timeEnd = timeStamp + minutes  * 60 * 1000;
    }

    unsigned long elapsedMinutes() {
      return (timeStamp - startTimeStamp) / 1000 / 60;
    }

    void stop() {
      startTimeStamp = 0;
      timeEnd = 0;
      digitalWrite(MOSFET_PIN, LOW);
    }

    void loop() {
      unsigned long currenTimeStamp = millis();

      if (currenTimeStamp - timeStamp > 1000) {
        timeStamp = currenTimeStamp;

        if (isWorking()) {
          if (dht11.getTemperature() < configStore.getTemperature()) {
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
