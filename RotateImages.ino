#include <Arduboy2.h>
#include "src/Arduboy2Ext/SpritesExt.h"

const uint8_t inpImgRAM[] = {
  16, 16,
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 0,
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 0, 0,
};

const uint8_t PROGMEM inpImg[] = {
  16, 32,
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 0,   // 0 - 15
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 128, 192,               // 16 - 31
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 0,   // 32 - 47
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 128, 192,               // 48 - 63
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


//Arduboy2Ext arduboy;
Arduboy2 arduboy;

void setup() {

  arduboy.boot();
  arduboy.clear();

  // for (uint8_t x = 0; x < 192; x= x + 6) {

  //   arduboy.drawLine(x, 0, 0, x);

  // }


  // // From array in memory ..
  
  // SpritesExt::drawOverwriteRAM(0, 0, inpImgRAM, 0);
  // SpritesExt::rotateCCW(inpImgRAM, outImg, false, false);
  // SpritesExt::drawOverwriteRAM(20, 0, outImg, 0);
  // SpritesExt::rotateCW(inpImgRAM, outImg, false, false);
  // SpritesExt::drawOverwriteRAM(40, 0, outImg, 0);
  // SpritesExt::rotate180(inpImgRAM, outImg, false, false);
  // SpritesExt::drawOverwriteRAM(60, 0, outImg, 0);


  // // From PROGMEM array ..

  // SpritesExt::drawOverwrite(0, 20, inpImg, 0);
  // SpritesExt::rotateCCW(inpImg, outImg, false, true);
  // SpritesExt::drawOverwriteRAM(20, 20, outImg, 0);
  // SpritesExt::rotateCW(inpImg, outImg, false, true);
  // SpritesExt::drawOverwriteRAM(40, 20, outImg, 0);
  // SpritesExt::rotate180(inpImg, outImg, false, true);
  // SpritesExt::drawOverwriteRAM(60, 20, outImg, 0);


  // // From PROGMEM array ..

  // SpritesExt::drawExternalMask(0, 40, inpImg, inpImg_Mask, 0, 0);
  // SpritesExt::rotateCCW(inpImg, outImg, false, true);
  // SpritesExt::rotateCCW(inpImg_Mask, outImg_Mask, true, true);
  // SpritesExt::drawExternalMaskRAM(20, 40, outImg, outImg_Mask, 0, 0);
  // SpritesExt::rotateCW(inpImg, outImg, false, true);
  // SpritesExt::rotateCW(inpImg_Mask, outImg_Mask, true, true);
  // SpritesExt::drawExternalMaskRAM(40, 40, outImg, outImg_Mask, 0, 0);
  // SpritesExt::rotate180(inpImg, outImg, false, true);
  // SpritesExt::rotate180(inpImg_Mask, outImg_Mask, true, true);
  // SpritesExt::drawExternalMaskRAM(60, 40, outImg, outImg_Mask, 0, 0);

  // SpritesExt::drawOverwrite(5, 10, inpImg, 0, false);
  // SpritesExt::drawOverwrite(5, 30, inpImg, 0, true);

//  SpritesExt::drawOverwrite(120, 10, inpImg, 0, false);
  // SpritesExt::drawOverwrite(80, 30, inpImg, 0, false);
  // SpritesExt::drawOverwrite(100, 30, inpImg, 0, true);
  SpritesExt::drawOverwrite(120, 30, inpImg, 0, true);

  arduboy.display();

}

void loop() { 

}



