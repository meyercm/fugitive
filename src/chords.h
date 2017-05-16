#ifndef _CHORDS_H
#define _CHORDS_H

#include <stdint.h>
#include <Keyboard.h>
#include "voices_mods.h"

namespace Chords {
  const int NUM_CHORDS = 0x6F + 1; // all we've defined so far. TODO: ask clay.
  const int KEY_CMD = KEY_LEFT_GUI;
  int get_key(int chord_index, Voice voice);

  const int NORMAL_CHORDMAP[NUM_CHORDS] = {
    _NO_KEY, // 0
    'a',  // 01
    'o',  // 02
    'h',  // 03
    'e',  // 04
    'i',  // 05
    'n',  // 06
    's',  // 07
    't',  // 08
    'd',  // 09
    'r',  // 0A
    'f',  // 0B
    'u',  // 0C
    'l',  // 0D
    'c',  // 0E
    'w',  // 0F
    _NO_KEY, // 10
    MOD_SHIFT,  // 11
    MOD_CTRL,  // 12
    '`',  // 13
    MOD_ALT,  // 14
    _NO_KEY,  // 15
    _NO_KEY,  // 16
    _NO_KEY,  // 17
    MOD_CMD,  // 18
    _NO_KEY,  // 19
    _NO_KEY,  // 1A
    _NO_KEY,  // 1B
    KEY_TAB,  // 1C
    _NO_KEY,  // 1D
    _NO_KEY,  // 1E
    _NO_KEY,  // 1F  <MOD_LOCK>
    ' ',  // 20
    VOICE_MOUSE,  // 21
    VOICE_2,  // 22
    'm',  // 23
    VOICE_1,  // 24
    'k',  // 25
    'g',  // 26
    'p',  // 27
    VOICE_NORMAL,  // 28
    'x',  // 29
    'b',  // 2A
    'q',  // 2B
    'v',  // 2C
    'y',  // 2D
    'j',  // 2E
    'z',  // 2F
    _NO_KEY,  // 30
    '1',  // 31
    '2',  // 32
    '5',  // 33
    '3',  // 34
    _NO_KEY,  // 35
    '6',  // 36
    '8',  // 37
    '4',  // 38
    _NO_KEY,  // 39
    _NO_KEY,  // 3A
    _NO_KEY,  // 3B
    '7',  // 3C
    _NO_KEY,  // 3D
    '9',  // 3E
    '0',  // 3F
    KEY_BACKSPACE, // 40
    KEY_LEFT_ARROW,  // 41
    KEY_DOWN_ARROW,  // 42
    KEY_PAGE_DOWN,  // 43
    KEY_UP_ARROW,  // 44
    _NO_KEY,  // 45
    KEY_RETURN,  // 46
    KEY_HOME,  // 47
    KEY_RIGHT_ARROW,  // 48
    KEY_ESC,  // 49
    _NO_KEY,  // 4A
    _NO_KEY,  // 4B
    KEY_PAGE_UP,  // 4C
    _NO_KEY,  // 4D
    KEY_END,  // 4E
    KEY_DELETE,  // 4F
    _NO_KEY,  // 50 UNUSABLE
    _NO_KEY,  // 51 UNUSABLE
    _NO_KEY,  // 52 UNUSABLE
    _NO_KEY,  // 53 UNUSABLE
    _NO_KEY,  // 54 UNUSABLE
    _NO_KEY,  // 55 UNUSABLE
    _NO_KEY,  // 56 UNUSABLE
    _NO_KEY,  // 57 UNUSABLE
    _NO_KEY,  // 58 UNUSABLE
    _NO_KEY,  // 59 UNUSABLE
    _NO_KEY,  // 5A UNUSABLE
    _NO_KEY,  // 5B UNUSABLE
    _NO_KEY,  // 5C UNUSABLE
    _NO_KEY,  // 5D UNUSABLE
    _NO_KEY,  // 5E UNUSABLE
    _NO_KEY,  // 5F UNUSABLE
    MOD_SHIFT,  // 60
    ',',  // 61
    '-',  // 62
    '[',  // 63
    '/',  // 64
    ';',  // 65
    '=',  // 66
    '(',  // 67
    '.',  // 68
    '\'',  // 69
    '`',  // 6A
    _NO_KEY,  // 6B
    ']',  // 6C
    _NO_KEY,  // 6D
    ')',  // 6E
    '\\',  // 6F
  };

  const int MOUSE_CHORDMAP[NUM_CHORDS] = {
    _NO_KEY, // 0
    MOUSE_MOVE_LEFT,  // 01
    MOUSE_MOVE_DOWN,  // 02
    MOUSE_MOVE_LEFT_DOWN,  // 03
    MOUSE_MOVE_UP,  // 04
    MOUSE_MOVE_LEFT_UP,  // 05
    _NO_KEY,  // 06
    _NO_KEY,  // 07
    MOUSE_MOVE_RIGHT,  // 08
    _NO_KEY,  // 09
    MOUSE_MOVE_RIGHT_DOWN,  // 0A
    _NO_KEY,  // 0B
    MOUSE_MOVE_RIGHT_UP,  // 0C
    _NO_KEY,  // 0D
    _NO_KEY,  // 0E
    _NO_KEY,  // 0F
    MOUSE_CLICK_MIDDLE, // 10
    _NO_KEY,  // 11
    _NO_KEY,  // 12
    _NO_KEY,  // 13
    _NO_KEY,  // 14
    _NO_KEY,  // 15
    _NO_KEY,  // 16
    _NO_KEY,  // 17
    _NO_KEY,  // 18
    _NO_KEY,  // 19
    _NO_KEY,  // 1A
    _NO_KEY,  // 1B
    _NO_KEY,  // 1C
    _NO_KEY,  // 1D
    _NO_KEY,  // 1E
    _NO_KEY,  // 1F  <MOD_LOCK>
    MOUSE_CLICK_LEFT,  // 20
    VOICE_MOUSE,  // 21
    VOICE_2,  // 22
    _NO_KEY,  // 23
    VOICE_1,  // 24
    _NO_KEY,  // 25
    _NO_KEY,  // 26
    _NO_KEY,  // 27
    VOICE_NORMAL,  // 28
    _NO_KEY,  // 29
    _NO_KEY,  // 2A
    _NO_KEY,  // 2B
    _NO_KEY,  // 2C
    _NO_KEY,  // 2D
    _NO_KEY,  // 2E
    _NO_KEY,  // 2F
    _NO_KEY,  // 30
    _NO_KEY,  // 31
    _NO_KEY,  // 32
    _NO_KEY,  // 33
    _NO_KEY,  // 34
    _NO_KEY, // 35
    _NO_KEY,  // 36
    _NO_KEY,  // 37
    _NO_KEY,  // 38
    _NO_KEY,  // 39
    _NO_KEY,  // 3A
    _NO_KEY,  // 3B
    _NO_KEY,  // 3C
    _NO_KEY,  // 3D
    _NO_KEY,  // 3E
    _NO_KEY,  // 3F
    MOUSE_CLICK_RIGHT, // 40
    _NO_KEY,  // 41
    _NO_KEY,  // 42
    _NO_KEY,  // 43
    _NO_KEY,  // 44
    _NO_KEY,  // 45
    _NO_KEY,  // 46
    _NO_KEY,  // 47
    _NO_KEY,  // 48
    _NO_KEY,  // 49
    _NO_KEY,  // 4A
    _NO_KEY,  // 4B
    _NO_KEY,  // 4C
    _NO_KEY,  // 4D
    _NO_KEY,  // 4E
    _NO_KEY,  // 4F
    _NO_KEY,  // 50 UNUSABLE
    _NO_KEY,  // 51 UNUSABLE
    _NO_KEY,  // 52 UNUSABLE
    _NO_KEY,  // 53 UNUSABLE
    _NO_KEY,  // 54 UNUSABLE
    _NO_KEY,  // 55 UNUSABLE
    _NO_KEY,  // 56 UNUSABLE
    _NO_KEY,  // 57 UNUSABLE
    _NO_KEY,  // 58 UNUSABLE
    _NO_KEY,  // 59 UNUSABLE
    _NO_KEY,  // 5A UNUSABLE
    _NO_KEY,  // 5B UNUSABLE
    _NO_KEY,  // 5C UNUSABLE
    _NO_KEY,  // 5D UNUSABLE
    _NO_KEY,  // 5E UNUSABLE
    _NO_KEY,  // 5F UNUSABLE
    _NO_KEY,  // 60
    _NO_KEY,  // 61
    _NO_KEY,  // 62
    _NO_KEY,  // 63
    _NO_KEY,  // 64
    _NO_KEY,  // 65
    _NO_KEY,  // 66
    _NO_KEY,  // 67
    _NO_KEY,  // 68
    _NO_KEY,  // 69
    _NO_KEY,  // 6A
    _NO_KEY,  // 6B
    _NO_KEY,  // 6C
    _NO_KEY,  // 6D
    _NO_KEY,  // 6E
    _NO_KEY,  // 6F
  };

}

#endif
