#include "./constants.h"
#include "./List.h"
#include "./Display.h"
#include "./Encoder.h"
#include "./Home.h"
#include "./Config.h"
#include "./Menu.h"

uint8_t section;

void goToSection (int newSection) {
  section = newSection;
}

void goToHome () {
  goToSection(1);
}

void goToMenu () {
  goToSection(2);
}

void goToConfig () {
  goToSection(3);
}

Display mainDisplay;
Encoder mainEncoder(3, 2, 4);
Config configMenu(mainDisplay, mainEncoder, goToMenu);
Menu mainMenu(mainDisplay, mainEncoder, configMenu, goToHome, goToConfig);
Home mainHome(mainDisplay, mainEncoder, goToMenu);

void setup() {
  Serial.begin(9600);
  goToSection(1);
  mainDisplay.setup();
}

void loop() {
  mainEncoder.update();

  if (section == 1) {
    mainHome.update();
  } else if (section == 2) {
    mainMenu.update();
  } else if (section == 3) {
    configMenu.loop();
  }
}
