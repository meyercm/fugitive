#ifndef _VOICES_MODS_H
#define _VOICES_MODS_H


namespace Chords {
  const int _NO_KEY = -1;
  bool is_voice(int key);
  bool is_mod(int key);
  bool is_regular(int key);

  typedef enum {
    VOICE_NORMAL = 256,
    VOICE_1 = 257,
    VOICE_2 = 258,
    VOICE_3 = 259,
  } Voice;

  typedef enum {
    MOD_SHIFT = 512,
    MOD_ALT = 513,
    MOD_CTRL = 514,
    MOD_CMD = 515,
  } Mod;
};

#endif
