#ifndef _OUTPUT_H
#define _OUTPUT_H

#include <Arduino.h>
#include <Keyboard.h>
#include <stdint.h>

#ifndef USE_KEYBOARD
#define USE_KEYBOARD true
#endif

namespace Output{
  static void library_init();

  void press(uint8_t key);
  void release(uint8_t key);

}

#endif
