class NTC100k {
  static constexpr float R1 = 100000.0;
  static constexpr float C1 = 0.6314915446e-3;
  static constexpr float C2 = 2.268077566e-4;
  static constexpr float C3 = 0.7295929024e-7;
  static const uint8_t SAMPLES_COUNT = 10;
  static const int INVALID_SAMPLE = -255;
  const uint8_t PIN;
  float temperature = 0;
  float samples[SAMPLES_COUNT];
  unsigned long timeStamp = 0;

  const float getPinValue() {
    return analogRead(PIN);
  }

  const float getSensorTemperature() {
      float R2 = R1 * (1023.0 / getPinValue() - 1.0);
      float logR2 = log(R2);
      float kTemp = 1.0 / (C1 + C2 * logR2 + C3 * logR2 * logR2 * logR2);
      return kTemp - 273.15;
  }

  void pushSample(float value) {
    for(uint8_t i = 0; i < SAMPLES_COUNT - 1; i++) {
      samples[i] = samples[i + 1];
    }
    samples[SAMPLES_COUNT - 1] = value;
  }

  void updateTemperature() {
    float temperatures = 0;
    float count = 0;

    for(uint8_t i = 0; i < SAMPLES_COUNT; i++) {
      if (samples[i] != INVALID_SAMPLE) {
        temperatures += samples[i];
        count++;
      }
    }

    temperature = temperatures / count;
  }

  public:
    NTC100k(uint8_t pin) : PIN(pin) {
      for(uint8_t i = 0; i < SAMPLES_COUNT; i++) {
        samples[i] = INVALID_SAMPLE;
      }
    }

    void loop () {
      unsigned long currentTimeStamp = millis();

      if (currentTimeStamp - timeStamp > RENDER_DELAY) {
        timeStamp = currentTimeStamp;
        pushSample(getSensorTemperature());
        updateTemperature();
      }
    }

    const int getTemperature() {
      return temperature;
    }
};
