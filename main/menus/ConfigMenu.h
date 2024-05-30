class ConfigMenu {
  static const uint8_t MINUTES_STEPS = 5;
  static const uint8_t DEFAULT_ITEMS_LENGTH = 5;
  const String DEFAULT_ITEMS[DEFAULT_ITEMS_LENGTH] = { "Temp: ", "Minutes: ", "Reset", "Save", "Cancel" };
  String formattedItems[DEFAULT_ITEMS_LENGTH];

  List list;

  void (*goToMenu)();
  uint8_t newTemperature = configStore.DEFAULT_TEMPERATURE;
  unsigned int newMinutes = configStore.DEFAULT_MINUTES;
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
          if (encoder.left && newMinutes - MINUTES_STEPS >= 0) {
            newMinutes -= MINUTES_STEPS;
            buildFormattedItems();
          }
          if (encoder.right && newMinutes + MINUTES_STEPS <= 60 * 8) {
            newMinutes += MINUTES_STEPS;
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

        list.selectedIndex == 1 && dryer.isWorking()
          ? list.setCursor("x")
          : list.setCursor();

        if (encoder.swUp) {
          // reset
          if(list.selectedIndex == 2) {
            newTemperature = configStore.DEFAULT_TEMPERATURE;
            newMinutes = configStore.DEFAULT_MINUTES;
            buildFormattedItems();
          // apply
          } else if(list.selectedIndex == 3) {
            configStore.setTemperature(newTemperature);
            configStore.setMinutes(newMinutes);
            close();
          // cancel
          } else if(list.selectedIndex == 4) {
            newTemperature = configStore.getTemperature();
            newMinutes = configStore.getMinutes();
            close();
          }
        }
      }

      if (!formattedItems[0].length()) {
        buildFormattedItems();
      } else {
        if (encoder.swUp) {
          if (list.selectedIndex == 0 || list.selectedIndex == 1) {
            if(list.selectedIndex == 1 && dryer.isWorking()) {
              return;
            }
            edit = !edit;
            edit ? list.setCursor("*") : list.setCursor();
          }
        }
      }

      display.print(list.getItems());
    }
};
