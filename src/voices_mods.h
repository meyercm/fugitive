#ifndef _VOICES_MODS_H
#define _VOICES_MODS_H


namespace Chords {
  const int _NO_KEY = -1;
  bool is_voice(int key);
  bool is_mod(int key);
  bool is_mouse(int key);
  bool is_regular(int key);

  typedef enum {
    VOICE_NORMAL = 256,
    VOICE_1 = 257,
    VOICE_2 = 258,
    VOICE_MOUSE = 259,
  } Voice;

  typedef enum {
    MOD_SHIFT = 512,
    MOD_ALT = 513,
    MOD_CTRL = 514,
    MOD_CMD = 515,
  } Mod;

  typedef enum {
    MOUSE_MOVE_LEFT = 1024,
    MOUSE_MOVE_LEFT_UP = 1025,
    MOUSE_MOVE_LEFT_DOWN = 1026,
    MOUSE_MOVE_RIGHT = 1027,
    MOUSE_MOVE_RIGHT_UP = 1028,
    MOUSE_MOVE_RIGHT_DOWN = 1029,
    MOUSE_MOVE_UP = 1030,
    MOUSE_MOVE_DOWN = 1031,
    MOUSE_CLICK_LEFT = 1032,
    MOUSE_CLICK_MIDDLE = 1033,
    MOUSE_CLICK_RIGHT = 1034,
    MOUSE_MOVE_NULL = 1035,
  } MouseAction;
};

#endif
