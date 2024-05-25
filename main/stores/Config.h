class Config {
  private:
    uint8_t temperature;
    unsigned int minutes;

  public:
    static const uint8_t DEFAULT_TEMPERATURE = 40;
    static const int DEFAULT_MINUTES = 60;

    Config() {
      reset();
    }
    uint8_t getTemperature() {
      return temperature;
    }
    void setTemperature(uint8_t value) {
      temperature = value;
    }

    unsigned int getMinutes() {
      return minutes;
    }
    void setMinutes(unsigned int value) {
      minutes = value;
    }

    void reset() {
      temperature = DEFAULT_TEMPERATURE;
      minutes = DEFAULT_MINUTES;
    }
};
