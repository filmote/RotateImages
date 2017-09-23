#include "src/Arduboy2Ext/Arduboy2.h"
#include "src/Arduboy2Ext/Sprites.h"

const uint8_t inpImgRAM[] = {
  16, 16,
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 1,
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 128, 192,
};

const uint8_t PROGMEM inpImg[] = {
  16, 16,
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 1,
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 128, 192,
};

const uint8_t PROGMEM inpImg_Mask[] = {
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 1,
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 128, 192,
};

uint8_t outImg[] = {
  16, 16,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

uint8_t outImg_Mask[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

Arduboy2 arduboy;

void setup() {

  arduboy.boot();
  arduboy.clear();


  // From array in memory ..
  
  Sprites::drawOverwriteRAM(0, 10, inpImgRAM, 0);
  Sprites::rotateCCW(inpImgRAM, outImg, false, false);
  Sprites::drawOverwriteRAM(20, 10, outImg, 0);
  Sprites::rotateCW(inpImgRAM, outImg, false, false);
  Sprites::drawOverwriteRAM(40, 10, outImg, 0);
  Sprites::rotate180(inpImgRAM, outImg, false, false);
  Sprites::drawOverwriteRAM(60, 10, outImg, 0);


  // From PROGMEM array ..

  Sprites::drawOverwrite(0, 30, inpImg, 0);
  Sprites::rotateCCW(inpImg, outImg, false, true);
  Sprites::drawOverwriteRAM(20, 30, outImg, 0);
  Sprites::rotateCW(inpImg, outImg, false, true);
  Sprites::drawOverwriteRAM(40, 30, outImg, 0);
  Sprites::rotate180(inpImg, outImg, false, true);
  Sprites::drawOverwriteRAM(60, 30, outImg, 0);


  arduboy.display();

}

void loop() { 

}



