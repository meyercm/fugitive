#include "chord_parse.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <stdbool.h>

#ifndef USE_KEYBOARD
#define USE_KEYBOARD false
#endif

namespace ChordParse{
  static void init_library();

  void on_key_change(KeyDetection::KeyState event, int key){
    init_library();
    typedef size_t (*key_method)(uint8_t);
    if (USE_KEYBOARD){

      switch (key) {
        case 0: event == KeyDetection::KEY_DOWN ? Keyboard.press('0') : Keyboard.release('0'); break;
        case 1: event == KeyDetection::KEY_DOWN ? Keyboard.press('1') : Keyboard.release('1'); break;
        case 2: event == KeyDetection::KEY_DOWN ? Keyboard.press('2') : Keyboard.release('2'); break;
        case 3: event == KeyDetection::KEY_DOWN ? Keyboard.press('3') : Keyboard.release('3'); break;
        case 4: event == KeyDetection::KEY_DOWN ? Keyboard.press('4') : Keyboard.release('4'); break;
        case 5: event == KeyDetection::KEY_DOWN ? Keyboard.press('5') : Keyboard.release('5'); break;
        case 6: event == KeyDetection::KEY_DOWN ? Keyboard.press('6') : Keyboard.release('6'); break;
        default: break;
      }
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
      Keyboard.begin();
    } else {
      Serial.println("Simulate starting keyboard now.");
    }
  }
};
