#include "chord_parse.h"
#include <Arduino.h>
#include <stdbool.h>

#ifndef USE_KEYBOARD
#define USE_KEYBOARD false
#endif

namespace ChordParse{
  static void init_library();

  void on_key_change(KeyDetection::KeyState event, int key){
    init_library();
    if (USE_KEYBOARD){
      // FIXME: actually send keys
    } else {
      Serial.print("key ");
      Serial.print(key);
      Serial.print(event == KeyDetection::KEY_UP ? " up\r\n" : " down\r\n");
    }
  }


  static void init_library(){
    static bool init_complete = false;
    if (init_complete) { return; }
    init_complete = true;

    if (USE_KEYBOARD){
      // FIXME: START KEYBOARD!
    } else {
      Serial.println("Simulate starting keyboard now.");
    }
  }
};
