class HomeMenu {
  String lines[2];
  void (*goToMenu)();

  String formatTime (unsigned int minutes) {
    const uint8_t hh = minutes / 60;
    const uint8_t mm = minutes - hh * 60;

    return padStart(String(hh), 2) + ":" + padStart(String(mm), 2);
  }

  public:
    HomeMenu(
      void (*onGoToMenu)()
    ) :
      goToMenu(onGoToMenu) {
    }

    void loop() {
      if (encoder.swUp) {
        return goToMenu();
      }

      CURRENT_RENDER_TIMESTAMP = millis();

      if (CURRENT_RENDER_TIMESTAMP - RENDER_DELAY > RENDER_TIMESTAMP) {
        RENDER_TIMESTAMP = CURRENT_RENDER_TIMESTAMP;

        if (dryer.isWorking()) {
          lines[0] = String(dht11.getTemperature()) + "/" + String(configStore.getTemperature()) + "C "+String(heater.getTemperature()) + "C | " + String(dht11.getHumidity()) + "%";
          lines[1] = formatTime(dryer.elapsedMinutes()) + "/" + formatTime(configStore.getMinutes());
        } else {
          lines[0] = String(dht11.getTemperature()) + "C "+String(heater.getTemperature()) + "C | " + String(dht11.getHumidity()) + "%";
          lines[1] = "Click for menu";
        }

        display.print(lines);
      }
    }
};
