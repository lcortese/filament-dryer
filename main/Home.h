#include <DHT.h>
#include <DHT_U.h>

class Home {
  Display& mainDisplay;
  Encoder& mainEncoder;
  void (*goToMenu)();
  DHT sensor;

  public:
    Home(
      Display& display,
      Encoder& encoder,
      void (*onGoToMenu)()
    ) :
      mainDisplay(display),
      mainEncoder(encoder),
      goToMenu(onGoToMenu),
      sensor(7, DHT11)
    {
      sensor.begin();
    }

    void update() {
      const String lines[] = {
        "Data:",
        String(sensor.readTemperature()) + "c | " + String(sensor.readHumidity()) + "%",
      };

      mainDisplay.print(lines);

      if (mainEncoder.swUp) {
        goToMenu();
      }
    }
};
