class HomeMenu {
  void (*goToMenu)();

  public:
    HomeMenu(
      void (*onGoToMenu)()
    ) :
      goToMenu(onGoToMenu) {
    }

    void loop() {
      const String lines[] = {
        "Data:",
        String(dht11.getTemperature()) + "c | " + String(dht11.getHumidity()) + "%",
      };

      display.print(lines);

      if (encoder.swUp) {
        goToMenu();
      }
    }
};
