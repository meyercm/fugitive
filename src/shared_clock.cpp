#include "shared_clock.h"
#include <stdbool.h>

static SystemClock shared_clock;
static bool init_complete = false;
static uint16_t pending_ticks;
static void library_init();

uint16_t SharedClock_current_time(){
  library_init();
  return SystemClock_current_time(shared_clock) + pending_ticks;
}

size_t SharedClock_start_timer(Timer_elapsed_callback callback, void* context, void* extra_context, uint16_t duration){
  library_init();
  return SystemClock_start_timer(shared_clock, callback, context, extra_context, duration);
}

void SharedClock_cancel_timer(size_t timer_id){
  library_init();
  SystemClock_cancel_timer(shared_clock, timer_id);
}

void SharedClock_tick(){
  library_init();
  pending_ticks++;
}

bool SharedClock_ok_sleep(){
  return (pending_ticks == 0);
}

void SharedClock_update(){
  uint16_t ticks_to_execute;

  // critical section. if a timer interrupt happens between these two, we
  // will lose that tick, and fall behind by one.
  ticks_to_execute = pending_ticks;
  pending_ticks = 0;

  for (int i = 0; i < ticks_to_execute; i++){
    SystemClock_tick(shared_clock);
  }
}

void SharedClock_set_time(uint16_t new_time){
  library_init();
  SystemClock_set_time(shared_clock, new_time);
}

SystemClock SharedClock_get_clock(){
  library_init();
  return shared_clock;
}

void SharedClock_reset(){
  init_complete = false;
  SystemClock_destroy(shared_clock);
}

static void library_init(){
  if (init_complete) {return;}
  init_complete = true;

  shared_clock = SystemClock_create();
  pending_ticks = 0;
}
