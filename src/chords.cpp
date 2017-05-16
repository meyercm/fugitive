#include "chords.h"

namespace Chords{

  int get_key(int chord_index, Voice voice){
    if (chord_index < 0 || chord_index >= NUM_CHORDS) {return _NO_KEY;}
    if (!is_voice(voice)) { return _NO_KEY; }
    switch (voice){
      case VOICE_NORMAL: return NORMAL_CHORDMAP[chord_index];
      case VOICE_MOUSE: return MOUSE_CHORDMAP[chord_index];
      // escape back to regular functionality if we messed up.
      default: return VOICE_NORMAL;
    }
  } // end
};
