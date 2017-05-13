#ifndef _CHORDS_H
#define _CHORDS_H

#include <stdint.h>
#include <Keyboard.h>


namespace Chords {

  const int _NO_KEY = -1;
  const int MODE_NORMAL = 255;
  const int MODE_1 = 256;
  const int MODE_2 = 257;
  const int MODE_3 = 258;
  const int NUM_CHORDS = 0x6F + 1; // all we've defined so far. TODO: ask clay.
  const int KEY_CMD = KEY_LEFT_GUI;
  int get_key(int chord_index);

  int chordmap[NUM_CHORDS] = {
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
    KEY_LEFT_SHIFT, // 10
    'A',  // 11
    'O',  // 12
    'H',  // 13
    'E',  // 14
    'I',  // 15
    'N',  // 16
    'S',  // 17
    'T',  // 18
    'D',  // 19
    'R',  // 1A
    'F',  // 1B
    'U',  // 1C
    'L',  // 1D
    'C',  // 1E
    'W',  // 1F
    ' ',  // 20
    MODE_3,  // 21
    MODE_2,  // 22
    'm',  // 23
    MODE_1,  // 24
    'k',  // 25
    'g',  // 26
    'p',  // 27
    MODE_NORMAL,  // 28
    'x',  // 29
    'b',  // 2A
    'q',  // 2B
    'v',  // 2C
    'y',  // 2D
    'j',  // 2E
    'z',  // 2F
    _NO_KEY,  // 30
    _NO_KEY,  // 31
    _NO_KEY,  // 32
    'M',  // 33
    _NO_KEY,  // 34
    'K',  // 35
    'G',  // 36
    'P',  // 37
    _NO_KEY,  // 38
    'X',  // 39
    'B',  // 3A
    'Q',  // 3B
    'V',  // 3C
    'Y',  // 3D
    'J',  // 3E
    'Z',  // 3F
    KEY_BACKSPACE, // 40
    KEY_LEFT_ARROW,  // 41
    KEY_DOWN_ARROW,  // 42
    KEY_PAGE_DOWN,  // 43
    KEY_UP_ARROW,  // 44
    _NO_KEY,  // 45
    KEY_RETURN,  // 46
    _NO_KEY,  // 47
    KEY_RIGHT_ARROW,  // 48
    KEY_ESC,  // 49
    _NO_KEY,  // 4A
    _NO_KEY,  // 4B
    KEY_PAGE_UP,  // 4C
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

  int get_key(int chord_index){
    if (chord_index < 0 || chord_index >= NUM_CHORDS) {return _NO_KEY;}
    return chordmap[chord_index];
  }
};

#endif
