#include "key_detection.h"
#include <Arduino.h>
#include "shared_clock.h"

namespace KeyDetection{
  static void on_timer_elapse(void* context, void* extra, size_t timer_id);
  static KeyCallback subscriber;
  static int keys[] = {KEY0, KEY1, KEY2, KEY3, KEY4, KEY5, KEY6,};
  static uint8_t key_state[KEY_COUNT];
  static KeyState last_pub[KEY_COUNT];

  //TODO: compute from DEBOUNCE_COUNT
  const uint8_t BOUNCE_MASK = 0x1f; // 5 bits set, hardcoded.

  void begin(KeyCallback callback){
    subscriber = callback;
    for (int i = 0; i < KEY_COUNT; i ++) {
      pinMode(keys[i], INPUT_PULLUP);
      key_state[i] = BOUNCE_MASK;
      last_pub[i] = KEY_UP;
    }
    SharedClock_start_timer(on_timer_elapse, NULL, NULL, DEBOUNCE_INTERVAL_MS);
  } // end begin()

  KeyState current_key_state(int key_num){
    if (key_num < 0 || key_num >= KEY_COUNT){ return KEY_ERROR; }
    return last_pub[key_num];
  }

  static void on_timer_elapse(void* context, void* extra, size_t timer_id) {
    // we could be super sophisticated and interrupt trigger, but lets start
    // with a simple polling loop.  Check all the pins every ms, and store
    // the last 5 readings.  if they are all the same, then bouncing is over!

    for (int i = 0; i < KEY_COUNT; i ++) {
      key_state[i] <<= 1;
      key_state[i] |= (digitalRead(keys[i]) & 0x01);
      key_state[i] &= BOUNCE_MASK;
      if (key_state[i] == 0 && last_pub[i] != KEY_DOWN) {
        last_pub[i] = KEY_DOWN;
        subscriber(KEY_DOWN, i);
      } else if(key_state[i] == BOUNCE_MASK && last_pub[i] != KEY_UP) {
        last_pub[i] = KEY_UP;
        subscriber(KEY_UP, i);
      }
    }
    SharedClock_start_timer(on_timer_elapse, NULL, NULL, DEBOUNCE_INTERVAL_MS);
  } // end on_timer_elapse

};
