class Dryer {
  const uint8_t MOSFET_PIN;
  DHTSensor& mainDHTSensor;
  Config& mainConfig;
  long unsigned timeStamp;
  long unsigned timeEnd;

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

    void start(const uint8_t minutes) {
      timeStamp = millis();
      timeEnd = timeStamp + (minutes * 60 * 1000);
    }

    void stop() {
      timeEnd = 0;
      digitalWrite(MOSFET_PIN, LOW);
    }

    void loop() {
      if (isWorking()) {
        if (millis() > timeStamp + 1000) {
          if (mainDHTSensor.getTemperature() < mainConfig.temperature) {
            digitalWrite(MOSFET_PIN, HIGH);
          } else {
            digitalWrite(MOSFET_PIN, LOW);
          }
          timeStamp = millis();
        }
      }
    }
};
