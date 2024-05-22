class Menu {
  static const unsigned int TOTAL = 2;
  static const unsigned int HIDDEN_ITEMS = 0;
  const String list[TOTAL + HIDDEN_ITEMS] = { "Configuration", "Back" };
  static const unsigned int PAGE_LENGTH = 2;
  unsigned int  selectedIndex = 0;
  Display& mainDisplay;
  Encoder& mainEncoder;
  void (*goBack)();
  void (*goToConfig)();

  void close () {
    selectedIndex = 0;
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
      goToConfig(onGoToConfig) {
    }

    void update() {
      if (mainEncoder.swUp && selectedIndex == 0) {
        goToConfig();
        return;
      }
      if (mainEncoder.swUp && selectedIndex == TOTAL - 1) {
        close();
        return;
      }
      if (mainEncoder.left && selectedIndex > 0) {
        selectedIndex--;
      }
      if (mainEncoder.right && selectedIndex < TOTAL - 1) {
        selectedIndex++;
      }

      String range[PAGE_LENGTH];
      int unsigned page = selectedIndex / PAGE_LENGTH;

      for (int unsigned i = 0; i < PAGE_LENGTH; i++) {
        int unsigned listIndex = page * PAGE_LENGTH + i;
        range[i] = selectedIndex == listIndex ? ">" + list[listIndex] : " " + list[listIndex];
      }

      mainDisplay.print(range);
    }
};
