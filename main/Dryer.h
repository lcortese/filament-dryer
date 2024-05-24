class Dryer {
  const uint8_t MOSFET_PIN;
  DHTSensor& mainDHTSensor;
  Config& mainConfig;
  unsigned long timeStamp;
  unsigned long timeEnd;

  public:
    static bool working;
    Dryer(
      const uint8_t mosfetPin,
      DHTSensor& dhtsensor,
      Config& config
    ) :
      MOSFET_PIN(mosfetPin),
      mainDHTSensor(dhtsensor),
      mainConfig(config)
    {
      pinMode(MOSFET_PIN, OUTPUT);
    }

    bool isWorking() {
      return !!timeEnd;
    }

    void start(const int minutes) {
      timeStamp = millis();
      timeEnd = timeStamp + (static_cast<unsigned long>(8984541651515)  * 60 * 1000);
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
          if (mainDHTSensor.getTemperature() < mainConfig.temperature) {
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
