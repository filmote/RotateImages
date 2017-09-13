#include "src/Arduboy2Ext/Arduboy2.h"
#include "src/Arduboy2Ext/Sprites.h"


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

  arduboy.begin();
  
  Sprites::drawOverwriteRAM(0, 0, outImg, 0);

  Sprites::rotateCCW(inpImg, outImg, sizeof(inpImg), sizeof(outImg));
  Sprites::drawOverwriteRAM(20, 0, outImg, 0);

  Sprites::rotateCW(inpImg, outImg, sizeof(inpImg), sizeof(outImg));
  Sprites::drawOverwriteRAM(40, 0, outImg, 0);

  Sprites::rotate180(inpImg, outImg, sizeof(inpImg), sizeof(outImg));
  Sprites::drawOverwriteRAM(60, 0, outImg, 0);


  // Echo out rotated image array ..
  /*
  for (int x = 2; x< 18; ++x) {
    Serial.print(outImg[x]);
    Serial.print(" ");
  }
  Serial.println("");

  for (int x = 18; x< 34; ++x) {
    Serial.print(outImg[x]);
    Serial.print(" ");
  }
  Serial.println("");
  */
}

void loop() { }



