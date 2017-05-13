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
    VOICE_3,  // 21
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
    _NO_KEY,  // 65
    '=',  // 66
    '(',  // 67
    '.',  // 68
    '\'',  // 69
    _NO_KEY,  // 6A
    _NO_KEY,  // 6B
    ']',  // 6C
    _NO_KEY,  // 6D
    ')',  // 6E
    '\\',  // 6F
  };

}

#endif
