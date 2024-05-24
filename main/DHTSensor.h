#include <DHT.h>
#include <DHT_U.h>

class DHTSensor {
  DHT sensor;

  public:
    DHTSensor(uint8_t pin): sensor(pin, DHT11) {
      sensor.begin();
    }

    float getTemperature() {
      return sensor.readTemperature();
    }

    uint8_t getHumidity() {
      return sensor.readHumidity();
    }

};