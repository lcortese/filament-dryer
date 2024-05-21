class Menu {
  private:
    const static unsigned int TOTAL = 5;
    const static unsigned int HIDDEN_ITEMS = 1;
    const String list[TOTAL + HIDDEN_ITEMS] = { "Corsa", "Peugeot", "Duster", "Focus", "Back" };
    const static unsigned int PAGE_LENGTH = 2;
    int unsigned selectedIndex = 0;
    Display& mainDisplay;
    Encoder& mainEncoder;
    void (*goBack)();

  public:
    Menu(Display& display, Encoder& encoder, void (*onGoBack)()) 
      : mainDisplay(display), mainEncoder(encoder), goBack(onGoBack) {}

    void update() {
      if (mainEncoder.swUp && selectedIndex == 4) {
        goBack();
        return;
      }
      if (mainEncoder.left && selectedIndex > 0) {
        selectedIndex = selectedIndex - 1;
      }
      if (mainEncoder.right && selectedIndex < TOTAL - 1) {
        selectedIndex = selectedIndex + 1;
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
