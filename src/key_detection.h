#ifndef _KEY_DETECTION_H
#define _KEY_DETECTION_H
#include <stdint.h>

#define DEBOUNCE_INTERVAL_MS 1
#define DEBOUNCE_COUNT 5

#define KEY0 2
#define KEY1 3
#define KEY2 4
#define KEY3 5
#define KEY4 6
#define KEY5 8
#define KEY6 9

namespace KeyDetection {
  const int KEY_COUNT = 7;

  typedef enum {
    KEY_DOWN,
    KEY_UP,
    KEY_ERROR,
  } KeyState;

  typedef void (*KeyCallback)(KeyState, int);

  void begin(KeyCallback callback);
  KeyState current_key_state(int key_num);
  KeyState next_key_state(int key_num);
};

#endif
