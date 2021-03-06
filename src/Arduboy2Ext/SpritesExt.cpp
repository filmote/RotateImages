#include "SpritesExt.h"

#define reverseBits(b) (((b)&1?128:0)|((b)&2?64:0)|((b)&4?32:0)|((b)&8?16:0)|((b)&16?8:0)|((b)&32?4:0)|((b)&64?2:0)|((b)&128?1:0))

SpritesExt::SpritesExt() { }

int16_t SpritesExt::getWidth(const uint8_t *bitmap, bool inProgMem) {
  return (inProgMem ? pgm_read_byte(bitmap) : *bitmap);
}

int16_t SpritesExt::getHeight(const uint8_t *bitmap, bool inProgMem) {
  ++bitmap;
  return (inProgMem ? pgm_read_byte(bitmap) : *bitmap);
}

void SpritesExt::drawExternalMask(int16_t x, int16_t y, const uint8_t *bitmap, const uint8_t *mask, uint8_t frame, uint8_t mask_frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, mask, mask_frame, SPRITE_MASKED, true, flipHoriz);
}

void SpritesExt::drawOverwrite(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, NULL, 0, SPRITE_OVERWRITE, true, flipHoriz);
}

void SpritesExt::drawErase(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, NULL, 0, SPRITE_IS_MASK_ERASE, true, flipHoriz);
}

void SpritesExt::drawSelfMasked(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, NULL, 0, SPRITE_IS_MASK, true, flipHoriz);
}

void SpritesExt::drawPlusMask(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, NULL, 0, SPRITE_PLUS_MASK, true, flipHoriz);
}

void SpritesExt::drawExternalMaskRAM(int16_t x, int16_t y, const uint8_t *bitmap, const uint8_t *mask, uint8_t frame, uint8_t mask_frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, mask, mask_frame, SPRITE_MASKED, false, flipHoriz);
}

void SpritesExt::drawOverwriteRAM(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, NULL, 0, SPRITE_OVERWRITE, false, flipHoriz);
}

void SpritesExt::drawEraseRAM(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, NULL, 0, SPRITE_IS_MASK_ERASE, false, flipHoriz);
}

void SpritesExt::drawSelfMaskedRAM(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t frame, bool flipHoriz) {
  draw(x, y, bitmap, frame, NULL, 0, SPRITE_IS_MASK, false, flipHoriz);
}


//common functions
void SpritesExt::draw(int16_t x, int16_t y,
                   const uint8_t *bitmap, uint8_t frame,
                   const uint8_t *mask, uint8_t sprite_frame,
                   uint8_t drawMode, bool inProgMem, bool flipHoriz) {
                     
  unsigned int frame_offset;

  if (bitmap == NULL)
    return;

  uint8_t width = (inProgMem ? pgm_read_byte(bitmap) : *bitmap);
  bitmap++;
  uint8_t height = (inProgMem ? pgm_read_byte(bitmap) : *bitmap);
  bitmap++;

  if (frame > 0 || sprite_frame > 0) {
    frame_offset = (width * ( height / 8 + ( height % 8 == 0 ? 0 : 1)));
    // sprite plus mask uses twice as much space for each frame
    if (drawMode == SPRITE_PLUS_MASK) {
      frame_offset *= 2;
    } else if (mask != NULL) {
      mask += sprite_frame * frame_offset;
    }
    bitmap += frame * frame_offset;
  }

  // if we're detecting the draw mode then base it on whether a mask
  // was passed as a separate object
  if (drawMode == SPRITE_AUTO_MODE) {
    drawMode = mask == NULL ? SPRITE_UNMASKED : SPRITE_MASKED;
  }

  drawBitmap(x, y, bitmap, mask, width, height, drawMode, inProgMem, flipHoriz);
}

void SpritesExt::drawBitmap(int16_t x, int16_t y,
                         const uint8_t *bitmap, const uint8_t *mask,
                         uint8_t w, uint8_t h, uint8_t draw_mode, bool inProgMem, bool flipHoriz)
{
  // no need to draw at all of we're offscreen
  if (x + w <= 0 || x > WIDTH - 1 || y + h <= 0 || y > HEIGHT - 1)
    return;

  if (bitmap == NULL)
    return;

  // xOffset technically doesn't need to be 16 bit but the math operations
  // are measurably faster if it is
  uint16_t xOffset, ofs;
  int8_t yOffset = abs(y) % 8;
  int8_t sRow = y / 8;
  uint8_t loop_h, start_h, rendered_width;

  if (y < 0 && yOffset > 0) {
    sRow--;
    yOffset = 8 - yOffset;
  }

  // if the left side of the render is offscreen skip those loops
  if (x < 0) {
    xOffset = abs(x);
  } else {
    xOffset = 0;
  }

  // if the right side of the render is offscreen skip those loops
  if (x + w > WIDTH - 1) {
    rendered_width = ((WIDTH - x) - xOffset);
  } else {
    rendered_width = (w - xOffset);
  }

  // if the top side of the render is offscreen skip those loops
  if (sRow < -1) {
    start_h = abs(sRow) - 1;
  } else {
    start_h = 0;
  }

  loop_h = h / 8 + (h % 8 > 0 ? 1 : 0); // divide, then round up

  // if (sRow + loop_h - 1 > (HEIGHT/8)-1)
  if (sRow + loop_h > (HEIGHT / 8)) {
    loop_h = (HEIGHT / 8) - sRow;
  }

  // prepare variables for loops later so we can compare with 0
  // instead of comparing two variables
  loop_h -= start_h;

  sRow += start_h;

  ofs = (sRow * WIDTH) + x + xOffset;

  uint8_t *bofs = 0;
uint16_t xxx = 0;

  if (!flipHoriz) {
    bofs = (uint8_t *)bitmap + (start_h * w) + xOffset;
  }
  else {
    bofs = (uint8_t *)bitmap + (start_h * w) + w + xOffset - 1;
    xxx = (start_h * w) + w + xOffset - 1;
  }

  uint8_t data;

  uint8_t mul_amt = 1 << yOffset;
  uint16_t mask_data;
  uint16_t bitmap_data;

  switch (draw_mode) {
    case SPRITE_UNMASKED:
      // we only want to mask the 8 bits of our own sprite, so we can
      // calculate the mask before the start of the loop
      mask_data = ~(0xFF * mul_amt);
      // really if yOffset = 0 you have a faster case here that could be
      // optimized
      for (uint8_t a = 0; a < loop_h; a++) {
        for (uint8_t iCol = 0; iCol < rendered_width; iCol++) {
          bitmap_data = (inProgMem ? pgm_read_byte(bofs) : *bofs) * mul_amt;

          if (sRow >= 0) {
            data = Arduboy2Base::sBuffer[ofs];
            data &= (uint8_t)(mask_data);
            data |= (uint8_t)(bitmap_data);
            Arduboy2Base::sBuffer[ofs] = data;
          }
          if (yOffset != 0 && sRow < 7) {
            data = Arduboy2Base::sBuffer[ofs + WIDTH];
            data &= (*((unsigned char *) (&mask_data) + 1));
            data |= (*((unsigned char *) (&bitmap_data) + 1));
            Arduboy2Base::sBuffer[ofs + WIDTH] = data;
          }

          ofs++;
          if (!flipHoriz) {
            bofs++;
          }
          else {
            bofs--;
            xxx--;
            Serial.println(xxx);
          }
        }
        sRow++;
        if (!flipHoriz) {
          bofs += w - rendered_width;
        }
        else {
          bofs += w + w - rendered_width;
        }

        ofs += WIDTH - rendered_width;
      }
      break;

    case SPRITE_IS_MASK:
      for (uint8_t a = 0; a < loop_h; a++) {
        for (uint8_t iCol = 0; iCol < rendered_width; iCol++) {
          bitmap_data = (inProgMem ? pgm_read_byte(bofs) : *bofs) * mul_amt;
          if (sRow >= 0) {
            Arduboy2Base::sBuffer[ofs] |= (uint8_t)(bitmap_data);
          }
          if (yOffset != 0 && sRow < 7) {
            Arduboy2Base::sBuffer[ofs + WIDTH] |= (*((unsigned char *) (&bitmap_data) + 1));
          }
          ofs++;
          bofs++;
        }
        sRow++;
        bofs += w - rendered_width;
        ofs += WIDTH - rendered_width;
      }
      break;

    case SPRITE_IS_MASK_ERASE:
      for (uint8_t a = 0; a < loop_h; a++) {
        for (uint8_t iCol = 0; iCol < rendered_width; iCol++) {
          bitmap_data = (inProgMem ? pgm_read_byte(bofs) : *bofs) * mul_amt;
          if (sRow >= 0) {
            Arduboy2Base::sBuffer[ofs]  &= ~(uint8_t)(bitmap_data);
          }
          if (yOffset != 0 && sRow < 7) {
            Arduboy2Base::sBuffer[ofs + WIDTH] &= ~(*((unsigned char *) (&bitmap_data) + 1));
          }
          ofs++;
          bofs++;
        }
        sRow++;
        bofs += w - rendered_width;
        ofs += WIDTH - rendered_width;
      }
      break;

    case SPRITE_MASKED:
      uint8_t *mask_ofs;
      mask_ofs = (uint8_t *)mask + (start_h * w) + xOffset;
      for (uint8_t a = 0; a < loop_h; a++) {
        for (uint8_t iCol = 0; iCol < rendered_width; iCol++) {
          // NOTE: you might think in the yOffset==0 case that this results
          // in more effort, but in all my testing the compiler was forcing
          // 16-bit math to happen here anyways, so this isn't actually
          // compiling to more code than it otherwise would. If the offset
          // is 0 the high part of the word will just never be used.

          // load data and bit shift
          // mask needs to be bit flipped
          mask_data = ~((inProgMem ? pgm_read_byte(mask_ofs) : *mask_ofs) * mul_amt);
          bitmap_data = (inProgMem ? pgm_read_byte(bofs) : *bofs) * mul_amt;

          if (sRow >= 0) {
            data = Arduboy2Base::sBuffer[ofs];
            data &= (uint8_t)(mask_data);
            data |= (uint8_t)(bitmap_data);
            Arduboy2Base::sBuffer[ofs] = data;
          }
          if (yOffset != 0 && sRow < 7) {
            data = Arduboy2Base::sBuffer[ofs + WIDTH];
            data &= (*((unsigned char *) (&mask_data) + 1));
            data |= (*((unsigned char *) (&bitmap_data) + 1));
            Arduboy2Base::sBuffer[ofs + WIDTH] = data;
          }
          ofs++;
          mask_ofs++;
          bofs++;
        }
        sRow++;
        bofs += w - rendered_width;
        mask_ofs += w - rendered_width;
        ofs += WIDTH - rendered_width;
      }
      break;


    case SPRITE_PLUS_MASK:
      // *2 because we use double the bits (mask + bitmap)
      bofs = (uint8_t *)(bitmap + ((start_h * w) + xOffset) * 2);

      uint8_t xi = rendered_width; // counter for x loop below

      asm volatile(
        "push r28\n" // save Y
        "push r29\n"
        "movw r28, %[buffer_ofs]\n" // Y = buffer_ofs_2
        "adiw r28, 63\n" // buffer_ofs_2 = buffer_ofs + 128
        "adiw r28, 63\n"
        "adiw r28, 2\n"
        "loop_y:\n"
        "loop_x:\n"
        // load bitmap and mask data
        "lpm %A[bitmap_data], Z+\n"
        "lpm %A[mask_data], Z+\n"

        // shift mask and buffer data
        "tst %[yOffset]\n"
        "breq skip_shifting\n"
        "mul %A[bitmap_data], %[mul_amt]\n"
        "movw %[bitmap_data], r0\n"
        "mul %A[mask_data], %[mul_amt]\n"
        "movw %[mask_data], r0\n"

        // SECOND PAGE
        // if yOffset != 0 && sRow < 7
        "cpi %[sRow], 7\n"
        "brge end_second_page\n"
        // then
        "ld %[data], Y\n"
        "com %B[mask_data]\n" // invert high byte of mask
        "and %[data], %B[mask_data]\n"
        "or %[data], %B[bitmap_data]\n"
        // update buffer, increment
        "st Y+, %[data]\n"

        "end_second_page:\n"
        "skip_shifting:\n"

        // FIRST PAGE
        // if sRow >= 0
        "tst %[sRow]\n"
        "brmi skip_first_page\n"
        "ld %[data], %a[buffer_ofs]\n"
        // then
        "com %A[mask_data]\n"
        "and %[data], %A[mask_data]\n"
        "or %[data], %A[bitmap_data]\n"
        // update buffer, increment
        "st %a[buffer_ofs]+, %[data]\n"
        "jmp end_first_page\n"

        "skip_first_page:\n"
        // since no ST Z+ when skipped we need to do this manually
        "adiw %[buffer_ofs], 1\n"

        "end_first_page:\n"

        // "x_loop_next:\n"
        "dec %[xi]\n"
        "brne loop_x\n"

        // increment y
        "next_loop_y:\n"
        "dec %[yi]\n"
        "breq finished\n"
        "mov %[xi], %[x_count]\n" // reset x counter
        // sRow++;
        "inc %[sRow]\n"
        "clr __zero_reg__\n"
        // sprite_ofs += (w - rendered_width) * 2;
        "add %A[sprite_ofs], %A[sprite_ofs_jump]\n"
        "adc %B[sprite_ofs], __zero_reg__\n"
        // buffer_ofs += WIDTH - rendered_width;
        "add %A[buffer_ofs], %A[buffer_ofs_jump]\n"
        "adc %B[buffer_ofs], __zero_reg__\n"
        // buffer_ofs_page_2 += WIDTH - rendered_width;
        "add r28, %A[buffer_ofs_jump]\n"
        "adc r29, __zero_reg__\n"

        "rjmp loop_y\n"
        "finished:\n"
        // put the Y register back in place
        "pop r29\n"
        "pop r28\n"
        "clr __zero_reg__\n" // just in case
        : [xi] "+&a" (xi),
        [yi] "+&a" (loop_h),
        [sRow] "+&a" (sRow), // CPI requires an upper register (r16-r23)
        [data] "=&l" (data),
        [mask_data] "=&l" (mask_data),
        [bitmap_data] "=&l" (bitmap_data)
        :
        [screen_width] "M" (WIDTH),
        [x_count] "l" (rendered_width), // lower register
        [sprite_ofs] "z" (bofs),
        [buffer_ofs] "x" (Arduboy2Base::sBuffer+ofs),
        [buffer_ofs_jump] "a" (WIDTH-rendered_width), // upper reg (r16-r23)
        [sprite_ofs_jump] "a" ((w-rendered_width)*2), // upper reg (r16-r23)

        // [sprite_ofs_jump] "r" (0),
        [yOffset] "l" (yOffset), // lower register
        [mul_amt] "l" (mul_amt) // lower register
        // NOTE: We also clobber r28 and r29 (y) but sometimes the compiler
        // won't allow us, so in order to make this work we don't tell it
        // that we clobber them. Instead, we push/pop to preserve them.
        // Then we need to guarantee that the the compiler doesn't put one of
        // our own variables into r28/r29.
        // We do that by specifying all the inputs and outputs use either
        // lower registers (l) or simple (r16-r23) upper registers (a).
        : // pushes/clobbers/pops r28 and r29 (y)
      );
      break;
  }
}

void SpritesExt::rotate(bool ccw, const uint8_t *a, uint8_t *b, bool isMask, bool inProgMem) {
  
  uint8_t offset = (isMask ? 0 : 2);
  
  memset(b + offset, 0, 32);

  uint16_t bit = (ccw ? 128 : 1);
  uint8_t outputIdx = (ccw ? 16 + offset : offset);

  for (uint8_t inputIdx = offset; inputIdx < 16 + offset; ++inputIdx) {
  
    uint8_t y1 = (ccw ? (inProgMem ? pgm_read_byte(&a[inputIdx]): a[inputIdx]) : reverseBits(inProgMem ? pgm_read_byte(&a[inputIdx + 16]) : a[inputIdx + 16]));

    for (uint8_t x = 0; x < 8; ++x) {
      b[outputIdx + x] = b[outputIdx + x] | ((y1 & (1 << x)) > 0 ? bit : 0);
    }

    y1 = (ccw ? (inProgMem ? pgm_read_byte(&a[inputIdx + 16]): a[inputIdx + 16]) : reverseBits(inProgMem ? pgm_read_byte(&a[inputIdx]) : a[inputIdx]));
    
    for (uint8_t x = 0; x < 8; ++x) {
      b[outputIdx + 8 + x] = b[outputIdx + 8 + x] | ((y1 & (1 << x)) > 0 ? bit : 0);
    }

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

void SpritesExt::rotateCCW(const uint8_t *a, uint8_t *b, bool isMask, bool inProgMem) { rotate(true, a, b, isMask, inProgMem); }

void SpritesExt::rotateCW(const uint8_t *a, uint8_t *b, bool isMask, bool inProgMem) { rotate(false, a, b, isMask, inProgMem); }

void SpritesExt::rotate180(const uint8_t *a, uint8_t *b, bool isMask, bool inProgMem) {

  uint8_t offset = (isMask ? 0 : 2);
  memset(b + offset, 0, 32);

  for (uint8_t x = offset; x < 32 + offset; ++x) {
  
    b[(isMask ? 31 : 35) - x] = reverseBits(inProgMem ? pgm_read_byte(&a[x]) : a[x]);

  }

}