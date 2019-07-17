#include "src/Arduboy2Ext/Arduboy2.h"
#include "src/Arduboy2Ext/Sprites.h"

const uint8_t inpImgRAM[] = {
  16, 16,
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 0,
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 0, 0,
};

const uint8_t PROGMEM inpImg[] = {
  16, 16,
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 0,
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 0, 0,
};

const uint8_t PROGMEM inpImg_Mask[] = {
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 0,
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 0, 0,
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

  for (uint8_t x = 0; x < 192; x= x + 6) {

    arduboy.drawLine(x, 0, 0, x);

  }


  // From array in memory ..
  
  Sprites::drawOverwriteRAM(0, 0, inpImgRAM, 0);
  Sprites::rotateCCW(inpImgRAM, outImg, false, false);
  Sprites::drawOverwriteRAM(20, 0, outImg, 0);
  Sprites::rotateCW(inpImgRAM, outImg, false, false);
  Sprites::drawOverwriteRAM(40, 0, outImg, 0);
  Sprites::rotate180(inpImgRAM, outImg, false, false);
  Sprites::drawOverwriteRAM(60, 0, outImg, 0);


  // From PROGMEM array ..

  Sprites::drawOverwrite(0, 20, inpImg, 0);
  Sprites::rotateCCW(inpImg, outImg, false, true);
  Sprites::drawOverwriteRAM(20, 20, outImg, 0);
  Sprites::rotateCW(inpImg, outImg, false, true);
  Sprites::drawOverwriteRAM(40, 20, outImg, 0);
  Sprites::rotate180(inpImg, outImg, false, true);
  Sprites::drawOverwriteRAM(60, 20, outImg, 0);


  // From PROGMEM array ..

  Sprites::drawExternalMask(0, 40, inpImg, inpImg_Mask, 0, 0);
  Sprites::rotateCCW(inpImg, outImg, false, true);
  Sprites::rotateCCW(inpImg_Mask, outImg_Mask, true, true);
  Sprites::drawExternalMaskRAM(20, 40, outImg, outImg_Mask, 0, 0);
  Sprites::rotateCW(inpImg, outImg, false, true);
  Sprites::rotateCW(inpImg_Mask, outImg_Mask, true, true);
  Sprites::drawExternalMaskRAM(40, 40, outImg, outImg_Mask, 0, 0);
  Sprites::rotate180(inpImg, outImg, false, true);
  Sprites::rotate180(inpImg_Mask, outImg_Mask, true, true);
  Sprites::drawExternalMaskRAM(60, 40, outImg, outImg_Mask, 0, 0);

  arduboy.display();

}

void loop() { 

}



