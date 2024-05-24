class Menu {
  static const uint8_t LIST_LENGTH = 3;
  const String DEFAULT_LIST[LIST_LENGTH] = { "Configuration", "Start", "Back" };
  String formattedList[LIST_LENGTH];
  Display& mainDisplay;
  Encoder& mainEncoder;
  Dryer& mainDryer;
  Config& configMenu;
  void (*goBack)();
  void (*goToConfig)();
  List menuList;

  void close () {
    menuList.selectedIndex = 0;
    goBack();
  }

  public:
    Menu(
      Display& display,
      Encoder& encoder,
      Dryer& dryer,
      Config& config,
      void (*onGoBack)(),
      void (*onGoToConfig)()
    ) :
      mainDisplay(display),
      mainEncoder(encoder),
      mainDryer(dryer),
      configMenu(config),
      goBack(onGoBack),
      goToConfig(onGoToConfig),
      menuList(formattedList, LIST_LENGTH) {
    }

    void update() {
      for(uint8_t i = 0; i < LIST_LENGTH; i++) {
        if (i == 1) {
          formattedList[i] = (mainDryer.isWorking() ? "Stop" : DEFAULT_LIST[i]) + ": " + configMenu.temperature + "c " + configMenu.minutes+"m";
        } else {
          formattedList[i] = DEFAULT_LIST[i];
        }
      }

      mainDryer.isWorking() && menuList.selectedIndex == 0
        ? menuList.setCursor("x")
        : menuList.setCursor();

      if (mainEncoder.swUp && menuList.selectedIndex == 0) {
        if (!mainDryer.isWorking()) {
          goToConfig();
          return;
        }
      }
      if (mainEncoder.swUp && menuList.selectedIndex == 1) {
        if (!mainDryer.isWorking()) {
          mainDryer.start(configMenu.minutes);
        } else {
          mainDryer.stop();
        }
        return;
      }
      if (mainEncoder.swUp && menuList.selectedIndex == LIST_LENGTH - 1) {
        close();
        return;
      }
      if (mainEncoder.left && menuList.selectedIndex > 0) {
        menuList.selectedIndex--;
      }
      if (mainEncoder.right && menuList.selectedIndex < LIST_LENGTH - 1) {
        menuList.selectedIndex++;
      }

      mainDisplay.print(menuList.getItems());
    }
};
