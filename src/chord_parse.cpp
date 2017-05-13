#include "chord_parse.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <stdbool.h>

#include "shared_clock.h"
#include "key_detection.h"
#include "chords.h"

#ifndef USE_KEYBOARD
#define USE_KEYBOARD true
#endif

#define CHORD_STABILIZE_MS 40

namespace ChordParse{
  typedef enum {
    STATE_INIT,
    STATE_IDLE,
    STATE_COLLECTING,
    STATE_COMPLETE,
  } STATE;

  static void init_output();
  static void on_chord_complete(void* context, void* extra, size_t timer_id);
  static void on_chord_end();
  static int current_chord();
  static void change_state(STATE);

  // local variables
  static STATE state;
  static uint8_t last_chord = 0;

  void on_key_change(KeyDetection::KeyState event, int key){
    switch (state) {
      case STATE_INIT: init_output(); // do not break, continue into state_idle logic
      case STATE_IDLE: {
        if (event == KeyDetection::KEY_DOWN){
          change_state(STATE_COLLECTING);
        }
      } break;
      case STATE_COLLECTING: {
        if (event == KeyDetection::KEY_UP){
          change_state(STATE_IDLE);
        }
      } break;
      case STATE_COMPLETE: {
        if (event == KeyDetection::KEY_UP){
          change_state(STATE_IDLE);
        } else if (event == KeyDetection::KEY_DOWN){
          change_state(STATE_COLLECTING);
        }
      } break;
      default: break;
    }
  }

  static void change_state(STATE new_state) {
    switch (new_state){
      case STATE_COLLECTING: {
        SharedClock_start_timer(on_chord_complete, NULL, NULL, CHORD_STABILIZE_MS);
      } break;
      case STATE_IDLE: {
        on_chord_end();
      } break;
      case STATE_COMPLETE: {
        last_chord = current_chord();
      } break;
      default: break;
    }
    state = new_state;
  }

  static void on_chord_complete(void* context, void* extra, size_t timer_id){
    change_state(STATE_COMPLETE);
    //int key = Chords::get_key(last_chord);

    if (USE_KEYBOARD){
      Keyboard.press(Chords::get_key(last_chord));
    } else {
      Serial.print("key down: ");
      Serial.println(Chords::get_key(last_chord));
    }
  }

  static void on_chord_end(){
    if (USE_KEYBOARD){
      Keyboard.release(Chords::get_key(last_chord));
    } else {
      Serial.print("key up: ");
      Serial.println(Chords::get_key(last_chord));
    }
  }

  static uint8_t BITS[] = {1,2,4,8,16,32,64};
  static int current_chord() {
    uint8_t result = 0;
    for (int i = 0; i < KeyDetection::KEY_COUNT; i++){
      if (KeyDetection::current_key_state(i) == KeyDetection::KEY_DOWN){
        result |= BITS[i];
      }
    }
    return result;
  }

  static void init_output(){
    if (USE_KEYBOARD){
      Keyboard.begin();
    } else {
      Serial.println("Simulate starting keyboard now.");
    }
  }
};
