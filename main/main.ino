
#include "./constants.h"
#include "./Display.h"
#include "./Encoder.h"
#include "./Home.h"
#include "./Menu.h"

Display mainDisplay;
Encoder mainEncoder(3, 2, 4);

int section;

void goToSection (int newSection) {
  section = newSection;
}

void goToHome () {
  goToSection(1);
}
void goToMenu () {
  goToSection(2);
}

Home mainHome(mainDisplay, mainEncoder, goToMenu);
Menu mainMenu(mainDisplay, mainEncoder, goToHome);

void setup() {
  Serial.begin(9600);  
  section = 1;
  temp = 20;
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
