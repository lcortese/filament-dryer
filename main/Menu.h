class Menu {
  static const uint8_t LIST_LENGTH = 2;
  const String LIST[LIST_LENGTH] = { "Configuration", "Back" };
  Display& mainDisplay;
  Encoder& mainEncoder;
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
      void (*onGoBack)(),
      void (*onGoToConfig)()
    ) :
      mainDisplay(display),
      mainEncoder(encoder),
      goBack(onGoBack),
      goToConfig(onGoToConfig),
      menuList(LIST, LIST_LENGTH) {
    }

    void update() {
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
