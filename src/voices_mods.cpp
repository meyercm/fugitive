#include "voices_mods.h"

namespace Chords{

  bool is_voice(int key) {
    return (key == VOICE_NORMAL ||
            key == VOICE_1 ||
            key == VOICE_2 ||
            key == VOICE_MOUSE);
  }

  bool is_mod(int key) {
    return (key == MOD_SHIFT ||
            key == MOD_ALT ||
            key == MOD_CTRL ||
            key == MOD_CMD);
  }

  bool is_mouse(int key) {
    return (key == MOUSE_MOVE_LEFT ||
            key == MOUSE_MOVE_LEFT_UP ||
            key == MOUSE_MOVE_LEFT_DOWN ||
            key == MOUSE_MOVE_RIGHT ||
            key == MOUSE_MOVE_RIGHT_UP ||
            key == MOUSE_MOVE_RIGHT_DOWN ||
            key == MOUSE_MOVE_UP ||
            key == MOUSE_MOVE_DOWN ||
            key == MOUSE_CLICK_LEFT ||
            key == MOUSE_CLICK_MIDDLE ||
            key == MOUSE_CLICK_RIGHT ||
            key == MOUSE_MOVE_NULL);
  }

  bool is_regular(int key) {
    return (!is_mod(key) && !is_voice(key) && !is_mouse(key));
  }

}
