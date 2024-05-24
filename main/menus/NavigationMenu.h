class NavigationMenu {
  static const uint8_t LIST_LENGTH = 3;
  const String DEFAULT_LIST[LIST_LENGTH] = { "Configuration", "Start", "Back" };
  String formattedList[LIST_LENGTH];
  void (*goBack)();
  void (*goToConfig)();
  List list;

  void close () {
    list.selectedIndex = 0;
    goBack();
  }

  public:
    NavigationMenu(
      void (*onGoBack)(),
      void (*onGoToConfig)()
    ) :
      goBack(onGoBack),
      goToConfig(onGoToConfig),
      list(formattedList, LIST_LENGTH) {
    }

    void loop() {
      if (encoder.swUp && list.selectedIndex == 0) {
        if (!mainDryer.isWorking()) {
          return goToConfig();
        }
      }
      if (encoder.swUp && list.selectedIndex == 1) {
        if (!mainDryer.isWorking()) {
          mainDryer.start(configMenu.minutes);
        } else {
          mainDryer.stop();
        }
        return close();
      }
      if (encoder.swUp && list.selectedIndex == LIST_LENGTH - 1) {
        return close();
      }
      if (encoder.left && list.selectedIndex > 0) {
        list.selectedIndex--;
      }
      if (encoder.right && list.selectedIndex < LIST_LENGTH - 1) {
        list.selectedIndex++;
      }

      // draw
      CURRENT_RENDER_TIMESTAMP = millis();

      if (CURRENT_RENDER_TIMESTAMP - RENDER_DELAY > RENDER_TIMESTAMP) {
        RENDER_TIMESTAMP = CURRENT_RENDER_TIMESTAMP;

        for(uint8_t i = 0; i < LIST_LENGTH; i++) {
          if (i == 1) {
            formattedList[i] = (mainDryer.isWorking() ? "Stop" : DEFAULT_LIST[i]) + ": " + configMenu.temperature + "c " + configMenu.minutes+"m";
          } else {
            formattedList[i] = DEFAULT_LIST[i];
          }
        }

        mainDryer.isWorking() && list.selectedIndex == 0
          ? list.setCursor("x")
          : list.setCursor();

        display.print(list.getItems());
      }
    }
};
