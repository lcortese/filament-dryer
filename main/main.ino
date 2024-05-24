#include "./constants.h"

#include "./List.h"
#include "./DHTSensor.h"
#include "./Display.h"
#include "./Encoder.h"

#include "./Home.h"
#include "./Config.h"
#include "./Dryer.h"
#include "./Menu.h"

DHTSensor mainDHTSensor(7);
Display mainDisplay;
Encoder mainEncoder(3, 2, 4);

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

Home mainHome(mainDisplay, mainDHTSensor, mainEncoder, goToMenu);
Config configMenu(mainDisplay, mainEncoder, goToMenu);
Dryer mainDryer(8, mainDHTSensor, configMenu);
Menu mainMenu(mainDisplay, mainEncoder, mainDryer, configMenu, goToHome, goToConfig);

void setup() {
  Serial.begin(9600);
  goToSection(1);
  mainDisplay.setup();
}

void loop() {
  mainDryer.loop();
  mainEncoder.update();

  if (section == 1) {
    mainHome.update();
  } else if (section == 2) {
    mainMenu.update();
  } else if (section == 3) {
    configMenu.loop();
  }
}
