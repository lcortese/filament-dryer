class Home {
  Display& mainDisplay;
  DHTSensor& mainDHTSensor;
  Encoder& mainEncoder;
  void (*goToMenu)();

  public:
    Home(
      Display& display,
      DHTSensor& dhtsensor,
      Encoder& encoder,
      void (*onGoToMenu)()
    ) :
      mainDisplay(display),
      mainDHTSensor(dhtsensor),
      mainEncoder(encoder),
      goToMenu(onGoToMenu) {
    }

    void update() {
      const String lines[] = {
        "Data:",
        String(mainDHTSensor.getTemperature()) + "c | " + String(mainDHTSensor.getHumidity()) + "%",
      };

      mainDisplay.print(lines);

      if (mainEncoder.swUp) {
        goToMenu();
      }
    }
};
