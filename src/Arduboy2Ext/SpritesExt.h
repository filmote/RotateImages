#pragma once

#include <Arduboy2.h>

class SpritesExt {

  public:

    SpritesExt();

    static void draw(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame, const uint8_t *mask, uint8_t sprite_frame, uint8_t drawMode, bool inProgMem);
    static void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, const uint8_t *mask, uint8_t w, uint8_t h, uint8_t draw_mode, bool inProgMem);

    static void drawExternalMask(int16_t x, int16_t y, const uint8_t *bitmap, const uint8_t *mask, uint8_t frame, uint8_t mask_frame);  
    static void drawOverwrite(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
    static void drawErase(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
    static void drawSelfMasked(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
    static void drawPlusMask(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);

    static void drawOverwriteRAM(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
    static void drawEraseRAM(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
    static void drawSelfMaskedRAM(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame);
    static void drawExternalMaskRAM(int16_t x, int16_t y, const uint8_t *bitmap, const uint8_t *mask, uint8_t frame, uint8_t mask_frame);

    static void rotate(bool ccw, const uint8_t *a, uint8_t *b, bool isMask, bool aInRam);
    static void rotateCCW(const uint8_t *a, uint8_t *b, bool isMask, bool aInRam);
    static void rotateCW(const uint8_t *a, uint8_t *b, bool isMask, bool aInRam);
    static void rotate180(const uint8_t *a, uint8_t *b, bool isMask, bool aInRam);

    static int16_t getWidth(const uint8_t *a, bool inProgMem);
    static int16_t getHeight(const uint8_t *a, bool inProgMem);

};