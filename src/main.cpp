#include <Arduino.h>
#include <stdint.h>
#include <stdlib.h>
#include <TimerOne.h>

#include "shared_clock.h"
#include "key_detection.h"
#include "chord_parse.h"

// should be 1000 even, for a tick every 1000 us = 1ms, but that's too slow
// after some trial and error, this seems good enough:
#define TIMER1_US_PER_MS 700

void setup() {
  Timer1.initialize(TIMER1_US_PER_MS);
  Timer1.attachInterrupt(SharedClock_tick);
  KeyDetection::begin(ChordParse::on_key_change);
}

void loop(){
  SharedClock_update();
}
