class Menu {
  static const uint8_t LIST_LENGTH = 3;
  String LIST[LIST_LENGTH] = { "Configuration", "Back", "Start" };
  String formattedList[LIST_LENGTH];
  Display& mainDisplay;
  Encoder& mainEncoder;
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
      Config& config,
      void (*onGoBack)(),
      void (*onGoToConfig)()
    ) :
      mainDisplay(display),
      mainEncoder(encoder),
      configMenu(config),
      goBack(onGoBack),
      goToConfig(onGoToConfig),
      menuList(formattedList, LIST_LENGTH) {
    }

    void update() {
      for(uint8_t i = 0; i < LIST_LENGTH; i++) {
        if (i == 2) {
          formattedList[i] = LIST[i] + ": " + configMenu.temperature + "c " + configMenu.minutes+"m";
        } else {
          formattedList[i] = LIST[i];
        }
      }

      if (mainEncoder.swUp && menuList.selectedIndex == 0) {
        goToConfig();
        return;
      }
      if (mainEncoder.swUp && menuList.selectedIndex == 1) {
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
