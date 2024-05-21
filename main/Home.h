int temp;

class Home {
  private:
    Display& mainDisplay;
    Encoder& mainEncoder;
    void (*goToMenu)();

  public:
    Home(Display& display, Encoder& encoder, void (*onGoToMenu)()) 
      : mainDisplay(display), mainEncoder(encoder), goToMenu(onGoToMenu) {}

    void update() {
      if ((mainEncoder.left || mainEncoder.right)
        && (temp + (mainEncoder.left * -1) + mainEncoder.right > 0)
        && (temp + (mainEncoder.left * -1) + mainEncoder.right < 101)
      ) {
        temp = temp + (mainEncoder.left * -1) + mainEncoder.right;  
      }

      const String lines[] = {
        "Home",
        "Temp: " + String(temp)
      };

      mainDisplay.print(lines);

      if (mainEncoder.swUp) {
        goToMenu();
      }
    }
};
