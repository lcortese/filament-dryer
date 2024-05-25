#include <DHT.h>
#include <DHT_U.h>

class Dht11 {
  DHT sensor;

  public:
    Dht11(uint8_t pin): sensor(pin, DHT11) {
      sensor.begin();
    }

    int8_t getTemperature() {
      return sensor.readTemperature();
    }

    uint8_t getHumidity() {
      return sensor.readHumidity();
    }
};