class NTC100k {
  static constexpr float R1 = 100000.0;
  static constexpr float C1 = 0.6314915446e-3;
  static constexpr float C2 = 2.268077566e-4;
  static constexpr float C3 = 0.7295929024e-7;
  const uint8_t PIN;
  int temperature;
  float samplesTemperature;
  uint8_t samples;
  unsigned long timeStamp;

  const float getPinValue() {
    return analogRead(PIN);
  }

  const float calculate() {
      float R2 = R1 * (1023.0 / getPinValue() - 1.0);
      float logR2 = log(R2);
      float kTemp = 1.0 / (C1 + C2 * logR2 + C3 * logR2 * logR2 * logR2);
      return kTemp - 273.15;
  }

  public:
    NTC100k(uint8_t pin) : PIN(pin) {}

    void loop () {
      unsigned long currenTimeStamp = millis();

      if (currenTimeStamp - timeStamp > 100) {
        timeStamp = currenTimeStamp;
        samples++;
        samplesTemperature += calculate();

        if (samples == 5) {
          samples = 0;
          temperature = samplesTemperature / 5;
          samplesTemperature = 0;
        }
      }
    }

    const int getTemperature() {
      return temperature;
    }
};
