#include "./constants.h"

#include "./peripherals/Display.h"
#include "./peripherals/Encoder.h"
#include "./peripherals/NTC100k.h"
#include "./peripherals/DHT11.h"
#include "./peripherals/Fan.h"

Display display;
Encoder encoder(3, 2, 4);
NTC100k heater(A0);
Dht11 dht11(7);
Fan outFan(6);

#include "./helpers/List.h"
#include "./helpers/padStart.h"
#include "./stores/Config.h"

Config configStore;

#include "./workers/Dryer.h"

Dryer dryer(8);

#include "./menus/HomeMenu.h"
#include "./menus/NavigationMenu.h"
#include "./menus/ConfigMenu.h"

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
ConfigMenu configMenu(goToMenu);

void setup() {
  if (DEBUG) {
    Serial.begin(9600);
  }
  goToSection(1);
  display.setup();
}

void loop() {
  dryer.loop();
  encoder.loop();
  heater.loop();

  if (section == 1) {
    homeMenu.loop();
  } else if (section == 2) {
    navigationMenu.loop();
  } else if (section == 3) {
    configMenu.loop();
  }
}
