#include "./constants.h"

#include "./peripherals/DHT11.h"
#include "./peripherals/Display.h"
#include "./peripherals/Encoder.h"

#include "./helpers/List.h"

Display display;
Encoder encoder(3, 2, 4);
Dht11 dht11(7);

#include "./menus/ConfigMenu.h"

ConfigMenu configMenu(goToMenu);

#include "./workers/Dryer.h"
Dryer mainDryer(8);

#include "./menus/NavigationMenu.h"
#include "./menus/HomeMenu.h"

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

HomeMenu homeMenu(goToMenu);
NavigationMenu navigationMenu(goToHome, goToConfig);

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
  }
  goToSection(1);
  display.setup();
}

void loop() {
  mainDryer.loop();
  encoder.loop();

  if (section == 1) {
    homeMenu.loop();
  } else if (section == 2) {
    navigationMenu.loop();
  } else if (section == 3) {
    configMenu.loop();
  }
}
