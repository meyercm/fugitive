#ifndef _KEY_DETECTION_H
#define _KEY_DETECTION_H
#include <stdint.h>

#define DEBOUNCE_INTERVAL_MS 1
#define DEBOUNCE_COUNT 5

#define KEY_COUNT 7
#define KEY0 3
#define KEY1 4
#define KEY2 5
#define KEY3 6
#define KEY4 7
#define KEY5 8
#define KEY6 9

namespace KeyDetection {
  typedef enum {
    KEY_DOWN,
    KEY_UP,
    KEY_ERROR,
  } KeyState;

  typedef void (*KeyCallback)(KeyState, int);

  void begin(KeyCallback callback);
  KeyState current_key_state(int key_num);

};

#endif
