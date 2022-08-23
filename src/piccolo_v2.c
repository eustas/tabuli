/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

int main() {
  const uint PIN = 15;
  gpio_init(PIN);
  gpio_set_dir(PIN, GPIO_OUT);

  io_wo_32* set = &sio_hw->gpio_set;
  uint32_t pwm[8 * 256];
  for (uint vol = 0; vol < 256; ++vol) {
    uint32_t q = 0;
    for (uint j = 0; j < 8; ++j) {
      uint32_t slice = 0;
      for (uint k = 0; k < 32; ++k) {
        uint32_t bit = 0;
        if (q >= vol) {
          q -= vol;
        } else {
          q = q + 256 - vol;
          bit = 1;
        }
        slice |= (bit << k);
      }
      pwm[vol * 8 + j] = slice;
    }
  }
  uint32_t pin = 1 << PIN;

  uint32_t sin[256] = {127, 131, 134, 137, 140, 143, 146, 149, 152, 156, 159, 162, 165, 168, 171, 174, 176, 179, 182, 185, 188, 191, 193, 196, 199, 201, 204, 206, 209, 211, 213, 216, 218, 220, 222, 224, 226, 228, 230, 232, 234, 236, 237, 239, 240, 242, 243, 245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 252, 252, 251, 250, 249, 248, 247, 246, 245, 243, 242, 240, 239, 237, 236, 234, 232, 230, 228, 226, 224, 222, 220, 218, 216, 213, 211, 209, 206, 204, 201, 199, 196, 193, 191, 188, 185, 182, 179, 176, 174, 171, 168, 165, 162, 159, 156, 152, 149, 146, 143, 140, 137, 134, 131, 127, 124, 121, 118, 115, 112, 109, 106, 103, 99, 96, 93, 90, 87, 84, 81, 79, 76, 73, 70, 67, 64, 62, 59, 56, 54, 51, 49, 46, 44, 42, 39, 37, 35, 33, 31, 29, 27, 25, 23, 21, 19, 18, 16, 15, 13, 12, 10, 9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 15, 16, 18, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 42, 44, 46, 49, 51, 54, 56, 59, 62, 64, 67, 70, 73, 76, 79, 81, 84, 87, 90, 93, 96, 99, 103, 106, 109, 112, 115, 118, 121, 124};
  for (uint i = 0; i < 256; ++i) sin[i] = sin[i] * 256;

  uint cntr1 = 0;
  uint cntr2 = 0;
  uint add = 1 << 18;
  while (true) {
    uint vol = sin[cntr2 >> 24];
    uint32_t addr = vol + (cntr1 & 0xFF);
    uint32_t slice = pwm[addr >> 5];
    uint32_t bit = slice >> (addr & 31);
    set[bit & 1] = pin;
    cntr1++;
    cntr2 += add;
  }
}
