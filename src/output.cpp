#include "output.h"

namespace Output{
  static void library_init();

  void press(uint8_t key){
    library_init();
    if (USE_KEYBOARD) {
      Keyboard.press(key);
    } else{
      Serial.print("key down: ");
      Serial.println(key);
    }
  }
  void release(uint8_t key) {
    library_init();
    if (USE_KEYBOARD) {
      Keyboard.release(key);
    } else{
      Serial.print("key up: ");
      Serial.println(key);
    }
  }


  static void library_init(){
    static bool init_complete = false;
    if (init_complete) { return; }
    init_complete = true;

    if (USE_KEYBOARD) {
      Keyboard.begin();
    } else{
      Serial.begin(115200);
      Serial.println("simulate starting keyboard");
    }
  }
}
