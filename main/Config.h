class Config {
  static const uint8_t DEFAULT_TEMPERATURE = 40;
  static const uint8_t DEFAULT_MINUTES = 60;
  static const uint8_t DEFAULT_ITEMS_LENGTH = 5;
  const String DEFAULT_ITEMS[DEFAULT_ITEMS_LENGTH] = { "Temp: ", "Minutes: ", "Reset", "Apply", "Back" };
  String formatedItems[DEFAULT_ITEMS_LENGTH];

  List itemsList;

  Display& mainDisplay;
  Encoder& mainEncoder;
  void (*goToMenu)();
  uint8_t newTemperature = DEFAULT_TEMPERATURE;
  uint8_t newMinutes = DEFAULT_MINUTES;
  bool edit;

  void close () {
    itemsList.selectedIndex = 0;
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
      itemsList(formatedItems, DEFAULT_ITEMS_LENGTH) {
    }

    void loop() {
      if (edit) {
        if (itemsList.selectedIndex == 0) {
          if (mainEncoder.left && newTemperature > 0) {
            newTemperature--;
          }
          if (mainEncoder.right && newTemperature < 100) {
            newTemperature++;
          }
        }
        if (itemsList.selectedIndex == 1) {
          if (mainEncoder.left && newMinutes > 0) {
            newMinutes = newMinutes -5;
          }
          if (mainEncoder.right && newMinutes < DEFAULT_MINUTES * 8) {
            newMinutes = newMinutes + 5;
          }
        }
      } else {
        if (mainEncoder.left && itemsList.selectedIndex > 0) {
          itemsList.selectedIndex--;
        }
        if (mainEncoder.right && itemsList.selectedIndex < DEFAULT_ITEMS_LENGTH - 1) {
          itemsList.selectedIndex++;
        }

        if (mainEncoder.swUp) {
          if(itemsList.selectedIndex == 2) {
            temperature = DEFAULT_TEMPERATURE;
            minutes = DEFAULT_MINUTES;
            newTemperature = temperature;
            newMinutes = minutes;
            close();
          }
          if(itemsList.selectedIndex == 3) {
            temperature = newTemperature;
            minutes = newMinutes;
            close();
          }
          if(itemsList.selectedIndex == 4) {
            newTemperature = temperature;
            newMinutes = minutes;
            close();
          }
        }
      }

      for (uint8_t i = 0; i < DEFAULT_ITEMS_LENGTH; i++) {
        if (i == 0) {
          formatedItems[i] = DEFAULT_ITEMS[i] + newTemperature + "c";
        } else if (i == 1) {
          formatedItems[i] = DEFAULT_ITEMS[i] + newMinutes;
        } else {
          formatedItems[i] = DEFAULT_ITEMS[i];
        }
      }

      mainDisplay.print(itemsList.getItems());

      if (mainEncoder.swUp) {
        if (itemsList.selectedIndex == 0 || itemsList.selectedIndex == 1) {
          edit = !edit;
        }
      }
    }
};
