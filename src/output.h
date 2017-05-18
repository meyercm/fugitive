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

  void press(int key);
  void release(int key);
  void release_all();
}

#endif
