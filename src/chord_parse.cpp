#include "chord_parse.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <stdbool.h>

#include "shared_clock.h"
#include "key_detection.h"
#include "voices_mods.h"
#include "chords.h"
#include "output.h"

#define CHORD_STABILIZE_MS 60

namespace ChordParse{
  typedef enum {
    STATE_IDLE,
    STATE_PRESSING,
    STATE_RELEASING,
    STATE_COMPLETE,
  } STATE;


  static void on_chord_complete(void* context, void* extra, size_t timer_id);
  static void release_key();
  static int next_chord();
  static int current_chord();
  static void change_state(STATE);
  static void clear_mods();
  static void set_mod(int key);
  static void cancel_timer();
  static void press_key(bool);
  static void press_mods();

  // local variables
  static STATE state = STATE_IDLE;
  static int last_chord = 0;
  static size_t timer = -1;
  static int last_key = 0;
  static Chords::Voice current_voice = Chords::VOICE_NORMAL;

  typedef enum {
    MOD_SHIFT = 0x01,
    MOD_CTRL  = 0x02,
    MOD_ALT   = 0x04,
    MOD_CMD   = 0x08,
  } MODS;

  static int mods = 0;

  void on_key_change(KeyDetection::KeyState event, int key){
    switch (state) {
      case STATE_IDLE: {
        if (event == KeyDetection::KEY_DOWN){
          change_state(STATE_PRESSING);
        }
      } break;
      case STATE_PRESSING: {
        if (event == KeyDetection::KEY_UP){
          press_key(false);
          change_state(STATE_RELEASING);
        }
      } break;
      case STATE_RELEASING: {
        if (event == KeyDetection::KEY_DOWN){
          change_state(STATE_PRESSING);
        } else if (event == KeyDetection::KEY_UP){
          change_state(STATE_RELEASING);
        }
      } break;
      case STATE_COMPLETE: {
        if (event == KeyDetection::KEY_UP){
          change_state(STATE_RELEASING);
        } else if (event == KeyDetection::KEY_DOWN){
          change_state(STATE_PRESSING);
        }
      } break;
      default: break;
    }
  }

  static void change_state(STATE new_state) {
    switch (new_state){
      case STATE_PRESSING: {
        Serial.println("new state: STATE_PRESSING");
        timer = SharedClock_start_timer(on_chord_complete, NULL, NULL, CHORD_STABILIZE_MS);
      } break;
      case STATE_RELEASING: {
        Serial.println("new state: STATE_RELEASING");
        cancel_timer();
        release_key();
        if (next_chord() == 0) {
          change_state(STATE_IDLE);
        }
      } break;
      case STATE_IDLE: {
        Serial.println("new state: STATE_IDLE");
        cancel_timer();
        Output::release_all();
      } break;
      case STATE_COMPLETE: {
        press_key(true);
        Serial.println("new state: STATE_COMPLETE");
      } break;
      default: break;
    }
    state = new_state;
}

  static void on_chord_complete(void* context, void* extra, size_t timer_id){
    timer = -1;
    change_state(STATE_COMPLETE);
  }

  static void press_key(bool use_next){
    if (use_next){
      last_chord = next_chord();
    } else {
      last_chord = current_chord();
    }

    last_key = Chords::get_key(last_chord, current_voice);

    if (Chords::is_mod(last_key)){
      Serial.println("mod detected");
      set_mod(last_key);
    } else if (Chords::is_voice(last_key)){
      Serial.println("voice detected");
      current_voice = (Chords::Voice)last_key;
    } else {
      press_mods();
      Output::press(last_key);
    }
  }

  static void release_key(){
    cancel_timer();
    if (Chords::is_regular(last_key) || Chords::is_mouse(last_key)){
      Output::release(last_key);
      clear_mods();
    }
  }

  static uint8_t BITS[] = {1,2,4,8,16,32,64};
  static int next_chord() {
    uint8_t result = 0;
    for (int i = 0; i < KeyDetection::KEY_COUNT; i++){
      if (KeyDetection::next_key_state(i) == KeyDetection::KEY_DOWN){
        result |= BITS[i];
      }
    }
    return result;
  }
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
    if (mods & MOD_SHIFT) {
      Output::release(KEY_LEFT_SHIFT);
      mods &= ~MOD_SHIFT;
    }
    if (mods & MOD_CTRL) {
      Output::release(KEY_LEFT_CTRL);
      mods &= ~MOD_CTRL;
    }
    if (mods & MOD_ALT) {
      Output::release(KEY_LEFT_ALT);
      mods &= ~MOD_ALT;
    }
    if (mods & MOD_CMD) {
      Output::release(Chords::KEY_CMD);
      mods &= ~MOD_CMD;
    }
  }

  static void press_mods(){
    if (mods & MOD_SHIFT) {
      Output::press(KEY_LEFT_SHIFT);
    }
    if (mods & MOD_CTRL) {
      Output::press(KEY_LEFT_CTRL);
    }
    if (mods & MOD_ALT) {
      Output::press(KEY_LEFT_ALT);
    }
    if (mods & MOD_CMD) {
      Output::press(Chords::KEY_CMD);
    }
  }

  static void set_mod(int key) {
    switch (key) {
      case Chords::MOD_SHIFT: {
        mods |= MOD_SHIFT;
      } break;
      case Chords::MOD_CTRL: {
        mods |= MOD_CTRL;
      } break;
      case Chords::MOD_ALT: {
        mods |= MOD_ALT;
      } break;
      case Chords::MOD_CMD: {
        mods |= MOD_CMD;
      } break;
      default: break;
    }
  }

  static void cancel_timer(){
    SharedClock_cancel_timer(timer);
    timer = -1;
  }
}
