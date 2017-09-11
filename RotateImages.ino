#include <Arduboy2.h>

#define reverseBits(b) (((b)&1?128:0)|((b)&2?64:0)|((b)&4?32:0)|((b)&8?16:0)|((b)&16?8:0)|((b)&32?4:0)|((b)&64?2:0)|((b)&128?1:0))

const uint8_t inpImg[] = {
  16, 16,
  16, 56, 56, 104, 120, 120, 254, 199, 254, 120, 120, 104, 56, 56, 16, 1,
  0, 0, 0, 0, 32, 48, 51, 127, 51, 48, 32, 0, 0, 0, 128, 192,
};

uint8_t outImg[] = {
  16, 16,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};

Arduboy2 arduboy;


void setup() {

  arduboy.begin();
  
  rotateCCW(inpImg, outImg);
//  rotateCW(inpImg, outImg);
//  rotate180(inpImg, outImg);


  // Echo out rotated image array ..
  
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
  
}

void loop() { }

void rotate(bool ccw, const uint8_t *a, uint8_t *b) {

  int bit = (ccw ? 128 : 1);
  int outputIdx = (ccw ? 18 : 2);

  for (int inputIdx = 2; inputIdx < 18; ++inputIdx) {
  
    unsigned char y1 =  (ccw ? a[inputIdx] : reverseBits(a[inputIdx + 16]));
   
    b[outputIdx] = b[outputIdx] | ((y1 & 1) > 0 ? bit : 0);
    b[outputIdx + 1] = b[outputIdx + 1] | ((y1 & 2) > 0 ? bit : 0);
    b[outputIdx + 2] = b[outputIdx + 2] | ((y1 & 4) > 0 ? bit : 0);
    b[outputIdx + 3] = b[outputIdx + 3] | ((y1 & 8) > 0 ? bit : 0);
    b[outputIdx + 4] = b[outputIdx + 4] | ((y1 & 16) > 0 ? bit : 0);
    b[outputIdx + 5] = b[outputIdx + 5] | ((y1 & 32) > 0 ? bit : 0);
    b[outputIdx + 6] = b[outputIdx + 6] | ((y1 & 64) > 0 ? bit : 0);
    b[outputIdx + 7] = b[outputIdx + 7] | ((y1 & 128) > 0 ? bit : 0);

    y1 = (ccw ? a[inputIdx + 16] : reverseBits(a[inputIdx]));

    b[outputIdx + 8] = b[outputIdx + 8] | ((y1 & 1) > 0 ? bit : 0);
    b[outputIdx + 9] = b[outputIdx + 9] | ((y1 & 2) > 0 ? bit : 0);
    b[outputIdx + 10] = b[outputIdx + 10] | ((y1 & 4) > 0 ? bit : 0);
    b[outputIdx + 11] = b[outputIdx + 11] | ((y1 & 8) > 0 ? bit : 0);
    b[outputIdx + 12] = b[outputIdx + 12] | ((y1 & 16) > 0 ? bit : 0);
    b[outputIdx + 13] = b[outputIdx + 13] | ((y1 & 32) > 0 ? bit : 0);
    b[outputIdx + 14] = b[outputIdx + 14] | ((y1 & 64) > 0 ? bit : 0);
    b[outputIdx + 15] = b[outputIdx + 15] | ((y1 & 128) > 0 ? bit : 0);

    if (ccw) {
   
      bit = bit >> 1;
      if (bit == 0) { 
        bit = 128;
        outputIdx = outputIdx - 16;
      }
   
    }
    else {
   
      bit = bit << 1;
      if (bit == 256) { 
        bit = 1;
        outputIdx = outputIdx + 16;
      }
   
    }

  }

}


void rotateCCW(const uint8_t *a, uint8_t *b) { rotate(true, a, b); }

void rotateCW(const uint8_t *a, uint8_t *b) { rotate(false, a, b); }

void rotate180(const uint8_t *a, uint8_t *b) {

  for (int x = 2; x < 34; ++x) {
  
    b[35 - x] = reverseBits(a[x]);

  }

}

