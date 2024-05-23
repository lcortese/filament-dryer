class Config {
  static const uint8_t DEFAULT_TEMPERATURE = 40;
  static const uint8_t DEFAULT_MINUTES = 60;
  static const uint8_t  ITEMS_LENGTH = 4;
  String ITEMS[ITEMS_LENGTH] = { "Temp: ", "Minutes: ", "Back", "Apply" };
  List itemsList;

  Display& mainDisplay;
  Encoder& mainEncoder;
  void (*goToMenu)();
  uint8_t newTemperature = DEFAULT_TEMPERATURE;
  uint8_t newMinutes = DEFAULT_MINUTES;
  bool edit;

  void close () {
    goToMenu();
  }

  public:
    uint8_t temperature = DEFAULT_TEMPERATURE;
    uint8_t minutes = DEFAULT_MINUTES;

    Config(
      Display& display,
      Encoder& encoder,
      void (*onGoToMenu)()
    ) :
      mainDisplay(display),
      mainEncoder(encoder),
      goToMenu(onGoToMenu),
      itemsList(ITEMS, ITEMS_LENGTH) {
    }

    void loop() {
      if (edit) {
          if (mainEncoder.left && temperature > 0) {
            newTemperature--;
          }
          if (mainEncoder.right && temperature < 100) {
            newTemperature++;
          }
      } else {
        if (mainEncoder.left && itemsList.selectedIndex > 0) {
          itemsList.selectedIndex--;
        }
        if (mainEncoder.right && itemsList.selectedIndex < ITEMS_LENGTH - 1) {
          itemsList.selectedIndex++;
        }

        mainDisplay.print(itemsList.getItems());

        if (mainEncoder.swUp) {
          if (itemsList.selectedIndex == 0) {
            edit = !edit;
          }
          if(itemsList.selectedIndex == 2) {
            newTemperature = temperature;
            close();
          }
          if(itemsList.selectedIndex == 3) {
            temperature = newTemperature;
            close();
          }
        }
      }
    }
};
