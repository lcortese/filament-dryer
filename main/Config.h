class Config {
  static const uint8_t DEFAULT_TEMPERATURE = 40;
  static const uint8_t DEFAULT_MINUTES = 60;
  static const uint8_t DEFAULT_ITEMS_LENGTH = 5;
  const String DEFAULT_ITEMS[DEFAULT_ITEMS_LENGTH] = { "Temp: ", "Minutes: ", "Reset", "Apply", "Cancel" };
  String formattedItems[DEFAULT_ITEMS_LENGTH];

  List itemsList;

  Display& mainDisplay;
  Encoder& mainEncoder;
  void (*goToMenu)();
  uint8_t newTemperature = DEFAULT_TEMPERATURE;
  uint8_t newMinutes = DEFAULT_MINUTES;
  bool edit;

  void buildFormattedItems () {
    for (uint8_t i = 0; i < DEFAULT_ITEMS_LENGTH; i++) {
      if (i == 0) {
        formattedItems[i] = DEFAULT_ITEMS[i] + newTemperature + "c";
      } else if (i == 1) {
        formattedItems[i] = DEFAULT_ITEMS[i] + newMinutes;
      } else {
        formattedItems[i] = DEFAULT_ITEMS[i];
      }
    }
  }

  void close () {
    formattedItems[0] = "";
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
      itemsList(formattedItems, DEFAULT_ITEMS_LENGTH) {
    }

    void loop() {
      if (edit) {
        if (itemsList.selectedIndex == 0) {
          if (mainEncoder.left && newTemperature > 0) {
            newTemperature--;
            buildFormattedItems();
          }
          if (mainEncoder.right && newTemperature < 100) {
            newTemperature++;
            buildFormattedItems();
          }
        }
        if (itemsList.selectedIndex == 1) {
          if (mainEncoder.left && newMinutes > 0) {
            newMinutes -= 5;
            buildFormattedItems();
          }
          if (mainEncoder.right && newMinutes < DEFAULT_MINUTES * 8) {
            newMinutes += 5;
            buildFormattedItems();
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
            newTemperature = DEFAULT_TEMPERATURE;
            newMinutes = DEFAULT_MINUTES;
            buildFormattedItems();
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

      if (!formattedItems[0].length()) {
        buildFormattedItems();
      } else {
        if (mainEncoder.swUp) {
          if (itemsList.selectedIndex == 0 || itemsList.selectedIndex == 1) {
            edit = !edit;
            edit ? itemsList.setCursor("*") : itemsList.setCursor();
          }
        }
      }

      mainDisplay.print(itemsList.getItems());
    }
};
