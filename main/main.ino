
#include "./constants.h"
#include "./Display.h"
#include "./Encoder.h"
#include "./Home.h"
#include "./Menu.h"

Display mainDisplay;
Encoder mainEncoder(3, 2, 4);

int unsigned section;

void goToSection (int newSection) {
  section = newSection;
}

void goToHome () {
  goToSection(1);
}

Menu mainMenu(mainDisplay, mainEncoder, goToHome);

void goToMenu () {
  mainMenu.reset();
  goToSection(2);
}

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
  }
}
