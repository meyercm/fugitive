#include "voices_mods.h"

namespace Chords{

  bool is_voice(int key) {
    return (key == VOICE_NORMAL ||
            key == VOICE_1 ||
            key == VOICE_2 ||
            key == VOICE_3);
  }

  bool is_mod(int key) {
    return (key == MOD_SHIFT ||
            key == MOD_ALT ||
            key == MOD_CTRL ||
            key == MOD_CMD);
  }

  bool is_regular(int key) {
    return (!is_mod(key) && !is_voice(key));
  }

}
