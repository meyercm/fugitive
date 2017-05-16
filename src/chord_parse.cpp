#include "chord_parse.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <stdbool.h>

#include "shared_clock.h"
#include "key_detection.h"
#include "voices_mods.h"
#include "chords.h"
#include "output.h"

#define CHORD_STABILIZE_MS 30

namespace ChordParse{
  typedef enum {
    STATE_IDLE,
    STATE_COLLECTING,
    STATE_COMPLETE,
  } STATE;


  static void on_chord_complete(void* context, void* extra, size_t timer_id);
  static void on_chord_end();
  static int current_chord();
  static void change_state(STATE);
  static void clear_mods();
  static void set_mod(int key);

  // local variables
  static STATE state = STATE_IDLE;
  static int last_chord = 0;
  static size_t timer = -1;
  static int last_key = 0;
  static Chords::Voice current_voice = Chords::VOICE_NORMAL;
  static bool mod_cmd = false;
  static bool mod_alt = false;
  static bool mod_shift = false;
  static bool mod_ctrl = false;

  void on_key_change(KeyDetection::KeyState event, int key){
    switch (state) {
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
        timer = SharedClock_start_timer(on_chord_complete, NULL, NULL, CHORD_STABILIZE_MS);
      } break;
      case STATE_IDLE: {
        SharedClock_cancel_timer(timer);
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
    timer = -1;
    change_state(STATE_COMPLETE);
    last_key = Chords::get_key(last_chord, current_voice);

    if (Chords::is_mod(last_key)){
      Serial.println("mod detected");
      set_mod(last_key);
    } else if (Chords::is_voice(last_key)){
      Serial.println("voice detected");
      current_voice = (Chords::Voice)last_key;
    } else {
      Output::press(last_key);
    }
  }

  static void on_chord_end(){
    timer = -1;
    if (Chords::is_regular(last_key)){
      Output::release(last_key);
      clear_mods();
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


  static void clear_mods() {
    if (mod_cmd) {
      Output::release(Chords::KEY_CMD);
      mod_cmd = false;
    }
    if (mod_alt) {
      Output::release(KEY_LEFT_ALT);
      mod_alt = false;
    }
    if (mod_shift) {
      Output::release(KEY_LEFT_SHIFT);
      mod_shift = false;
    }
    if (mod_ctrl) {
      Output::release(KEY_LEFT_CTRL);
      mod_ctrl = false;
    }
  }

  static void set_mod(int key) {
    switch (key) {
      case Chords::MOD_CMD: {
        Output::press(Chords::KEY_CMD);
        mod_cmd = true;
      } break;
      case Chords::MOD_ALT: {
        Output::press(KEY_LEFT_ALT);
        mod_alt = true;
      } break;
      case Chords::MOD_SHIFT: {
        Output::press(KEY_LEFT_SHIFT);
        mod_shift = true;
      } break;
      case Chords::MOD_CTRL: {
        Output::press(KEY_LEFT_CTRL);
        mod_ctrl = true;
      } break;
      default: break;
    }
  }
}
