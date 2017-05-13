#ifndef _CHORD_PARSE_H
#define _CHORD_PARSE_H

#include "key_detection.h"


namespace ChordParse{
  void on_key_change(KeyDetection::KeyState, int);
};

#endif
