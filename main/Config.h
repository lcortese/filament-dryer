class Config {
  static const int DEFAULT_TEMPERATURE = 40;
  static const int  ITEMS_COUNT = 3;
  const String items[ITEMS_COUNT] = { "Temp: ", "Back", "Apply" };

  String formatedItems[ITEMS_COUNT];
  Display& mainDisplay;
  Encoder& mainEncoder;
  void (*goToMenu)();
  int selectedIndex = 0; 
  int newTemperature = DEFAULT_TEMPERATURE;
  bool edit;

  void close () {
    selectedIndex = 0;
    goToMenu();
  }

  public:
    int temperature = DEFAULT_TEMPERATURE;

    Config(
      Display& display,
      Encoder& encoder,
      void (*onGoToMenu)()
    ) :
      mainDisplay(display),
      mainEncoder(encoder),
      goToMenu(onGoToMenu) {
    }

    void update() {
      if (edit) {
        if (mainEncoder.left && temperature > 0) {
          newTemperature--;
        }
        if (mainEncoder.right && temperature < 100) {
          newTemperature++;
        }
      } else {
        if (mainEncoder.left && selectedIndex > 0) {
          selectedIndex--;
        }
        if (mainEncoder.right && selectedIndex < ITEMS_COUNT - 1) {
          selectedIndex++;
        }
      }

      for (uint8_t i = 0; i < ITEMS_COUNT; i++) {
        String item = items[i];
        if(i == 0) {
          item += newTemperature;
        }
        formatedItems[i] = (i == selectedIndex ? ">" : " ") + item;
      }

      const String lines[] = {
        formatedItems[0],
        edit ? "" : formatedItems[1] + " | " + formatedItems[2]
      };

      mainDisplay.print(lines);

      if (mainEncoder.swUp) {
        if (selectedIndex == 0) {
          edit = !edit;
        }
        if(selectedIndex == 1) {
          newTemperature = temperature;
          close();
        }
        if(selectedIndex == 2) {
          temperature = newTemperature;
          close();
        }
      }
    }
};
