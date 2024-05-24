class ConfigMenu {
  static const uint8_t DEFAULT_TEMPERATURE = 40;
  static const int DEFAULT_MINUTES = 60;
  static const uint8_t DEFAULT_ITEMS_LENGTH = 5;
  const String DEFAULT_ITEMS[DEFAULT_ITEMS_LENGTH] = { "Temp: ", "Minutes: ", "Reset", "Apply", "Cancel" };
  String formattedItems[DEFAULT_ITEMS_LENGTH];

  List list;

  void (*goToMenu)();
  uint8_t newTemperature = DEFAULT_TEMPERATURE;
  int newMinutes = DEFAULT_MINUTES;
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
    list.selectedIndex = 0;
    goToMenu();
  }

  public:
    uint8_t temperature = DEFAULT_TEMPERATURE;
    int minutes = DEFAULT_MINUTES;

    ConfigMenu(
      void (*onGoToMenu)()
    ) :
      goToMenu(onGoToMenu),
      list(formattedItems, DEFAULT_ITEMS_LENGTH) {
    }

    void loop() {
      if (edit) {
        if (list.selectedIndex == 0) {
          if (encoder.left && newTemperature > 0) {
            newTemperature--;
            buildFormattedItems();
          }
          if (encoder.right && newTemperature < 100) {
            newTemperature++;
            buildFormattedItems();
          }
        }
        if (list.selectedIndex == 1) {
          if (encoder.left && newMinutes > 0) {
            newMinutes -= 5;
            buildFormattedItems();
          }
          if (encoder.right && newMinutes < DEFAULT_MINUTES * 8) {
            newMinutes += 5;
            buildFormattedItems();
          }
        }
      } else {
        if (encoder.left && list.selectedIndex > 0) {
          list.selectedIndex--;
        }
        if (encoder.right && list.selectedIndex < DEFAULT_ITEMS_LENGTH - 1) {
          list.selectedIndex++;
        }

        if (encoder.swUp) {
          if(list.selectedIndex == 2) {
            newTemperature = DEFAULT_TEMPERATURE;
            newMinutes = DEFAULT_MINUTES;
            buildFormattedItems();
          }
          if(list.selectedIndex == 3) {
            temperature = newTemperature;
            minutes = newMinutes;
            close();
          }
          if(list.selectedIndex == 4) {
            newTemperature = temperature;
            newMinutes = minutes;
            close();
          }
        }
      }

      if (!formattedItems[0].length()) {
        buildFormattedItems();
      } else {
        if (encoder.swUp) {
          if (list.selectedIndex == 0 || list.selectedIndex == 1) {
            edit = !edit;
            edit ? list.setCursor("*") : list.setCursor();
          }
        }
      }

      display.print(list.getItems());
    }
};
