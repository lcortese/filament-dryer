class Dryer {
  static const uint8_t MAX_HEATER_TEMP = 80;
  const uint8_t MOSFET_PIN;
  unsigned long startTimeStamp;
  unsigned long timeStamp;
  unsigned long timeEnd;

  public:
    Dryer(
      const uint8_t relayPin
    ) :
      MOSFET_PIN(relayPin)
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
      outFan.setSpeed(0);
    }

    void loop() {
      unsigned long currenTimeStamp = millis();

      if (currenTimeStamp - timeStamp > 1000) {
        timeStamp = currenTimeStamp;

        if (isWorking()) {
          const uint8_t maxHeaterTemp = min(configStore.getTemperature() * 1.4, MAX_HEATER_TEMP);

          bool ambientBelowTarget = dht11.getTemperature() < configStore.getTemperature();
          bool heaterBelowTarget = heater.getTemperature() < configStore.getTemperature();
          bool heaterExceeded = heater.getTemperature() > maxHeaterTemp;

          if ((ambientBelowTarget || heaterBelowTarget) && !heaterExceeded) {
            digitalWrite(MOSFET_PIN, HIGH);
          } else {
            digitalWrite(MOSFET_PIN, LOW);
          }

          outFan.setSpeed(max(dht11.getTemperature() / float(configStore.getTemperature()) * 100, 30));

          if (timeStamp > timeEnd) {
            stop();
          }
        }
      }
    }
};
