#include "output.h"
#include "voices_mods.h"
#include <Mouse.h>
#include <Keyboard.h>
#include "shared_clock.h"

#ifndef MOUSE_UPDATE_RATE
#define MOUSE_UPDATE_RATE 50
#endif
#ifndef MOUSE_MAX_VEL
#define MOUSE_MAX_VEL 10
#endif

namespace Output{
  static void library_init();
  static void handle_mouse_press(Chords::MouseAction);
  static void handle_mouse_release(Chords::MouseAction);

  void press(int key){
    library_init();
    if (Chords::is_mouse(key)) {
      handle_mouse_press((Chords::MouseAction)key);
    } else {
      if (USE_KEYBOARD) {
        Keyboard.press(key);
      } else{
        Serial.print("key down: ");
        Serial.println(key);
      }
    }
  }
  void release(int key) {
    library_init();
    if (Chords::is_mouse(key)) {
      handle_mouse_release((Chords::MouseAction)key);
    } else {
      if (USE_KEYBOARD) {
        Keyboard.release(key);
      } else{
        Serial.print("key up: ");
        Serial.println(key);
      }
    }
  }


  static void library_init(){
    static bool init_complete = false;
    if (init_complete) { return; }
    init_complete = true;

    if (USE_KEYBOARD) {
      Keyboard.begin();
      Mouse.begin();
    } else{
      Serial.begin(115200);
      Serial.println("simulate starting keyboard");
    }
  }

  static float DRAG = 0.15;
  static float ACCEL = 0.3;
  static float v_x = 0;
  static float v_y = 0;
  static Chords::MouseAction current_action = Chords::MOUSE_MOVE_NULL;
  static void update_mouse(void* ctx, void* ext, size_t timer_id);

  static void handle_mouse_press(Chords::MouseAction action){
    switch (action) {
      case Chords::MOUSE_CLICK_LEFT: { Mouse.press(MOUSE_LEFT); break; }
      case Chords::MOUSE_CLICK_MIDDLE: { Mouse.press(MOUSE_MIDDLE); break; }
      case Chords::MOUSE_CLICK_RIGHT: { Mouse.press(MOUSE_RIGHT); break; }
      case Chords::MOUSE_MOVE_LEFT:
      case Chords::MOUSE_MOVE_LEFT_UP:
      case Chords::MOUSE_MOVE_LEFT_DOWN:
      case Chords::MOUSE_MOVE_RIGHT:
      case Chords::MOUSE_MOVE_RIGHT_UP:
      case Chords::MOUSE_MOVE_RIGHT_DOWN:
      case Chords::MOUSE_MOVE_UP:
      case Chords::MOUSE_MOVE_DOWN: {
        current_action = action;
        SharedClock_start_timer(update_mouse, NULL, NULL, MOUSE_UPDATE_RATE);
      }
      default: break;
    }
  }

  static void handle_mouse_release(Chords::MouseAction action){
    switch (action) {
      case Chords::MOUSE_CLICK_LEFT: { Mouse.release(MOUSE_LEFT); break; }
      case Chords::MOUSE_CLICK_MIDDLE: { Mouse.release(MOUSE_MIDDLE); break; }
      case Chords::MOUSE_CLICK_RIGHT: { Mouse.release(MOUSE_RIGHT); break; }
      case Chords::MOUSE_MOVE_LEFT:
      case Chords::MOUSE_MOVE_LEFT_UP:
      case Chords::MOUSE_MOVE_LEFT_DOWN:
      case Chords::MOUSE_MOVE_RIGHT:
      case Chords::MOUSE_MOVE_RIGHT_UP:
      case Chords::MOUSE_MOVE_RIGHT_DOWN:
      case Chords::MOUSE_MOVE_UP:
      case Chords::MOUSE_MOVE_DOWN: {
        current_action = Chords::MOUSE_MOVE_NULL;
      }
      default: break;
    }
  }

  static void update_mouse(void* ctx, void* ext, size_t timer_id){
    // apply accelleration
    switch (current_action){
      case Chords::MOUSE_MOVE_LEFT:{ v_x-=ACCEL; break; }
      case Chords::MOUSE_MOVE_LEFT_UP:{ v_x-=ACCEL; v_y-=ACCEL; break; }
      case Chords::MOUSE_MOVE_LEFT_DOWN:{ v_x-=ACCEL; v_y+=ACCEL; break; }
      case Chords::MOUSE_MOVE_RIGHT:{ v_x+=ACCEL; break; }
      case Chords::MOUSE_MOVE_RIGHT_UP:{ v_x+=ACCEL; v_y-=ACCEL; break; }
      case Chords::MOUSE_MOVE_RIGHT_DOWN:{ v_x+=ACCEL; v_y+=ACCEL; break; }
      case Chords::MOUSE_MOVE_UP:{ v_y-=ACCEL; break; }
      case Chords::MOUSE_MOVE_DOWN: { v_y+=ACCEL; break; }
      case Chords::MOUSE_MOVE_NULL:{ break; }
      default: break;
    }
    // apply drag
    if (v_x > 0) {
      v_x -= DRAG;
    } else if(v_x < 0) {
      v_x += DRAG;
    }
    if (v_y > 0) {
      v_y -= DRAG;
    } else if(v_y < 0) {
      v_y += DRAG;
    }
    // clamp velocity
    if (v_x > MOUSE_MAX_VEL) {
      v_x = MOUSE_MAX_VEL;
    } else if(v_x < -MOUSE_MAX_VEL) {
      v_x = -MOUSE_MAX_VEL;
    }
    if (v_y > MOUSE_MAX_VEL) {
      v_y = MOUSE_MAX_VEL;
    } else if(v_y < -MOUSE_MAX_VEL) {
      v_y = -MOUSE_MAX_VEL;
    }
    // stop if drag wins
    if ((v_x < DRAG && v_x > -DRAG) && (v_y < DRAG && v_y > -DRAG) && current_action == Chords::MOUSE_MOVE_NULL) {
      return;
    }
    Mouse.move(v_x, v_y);
    SharedClock_start_timer(update_mouse, NULL, NULL, MOUSE_UPDATE_RATE);
  }

}
