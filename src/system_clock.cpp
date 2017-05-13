#include <stdlib.h>
#include <stdio.h>
#include "system_clock.h"
//TODO: switch to using pool
struct SystemClock_Timer_Struct{
  size_t id;
  uint16_t elapse_at;
  Timer_elapsed_callback callback;
  void* context;
  void* extra_context;
  bool available;
};

struct SystemClock_Struct{
  uint16_t current_time;
  uint16_t next_elapsed;
  uint16_t tick_rate;
  bool available;
  uint8_t timer_count;
  struct SystemClock_Timer_Struct timers[NUM_SYSTEM_CLOCK_TIMERS];
};


static struct SystemClock_Struct clocks[NUM_SYSTEM_CLOCKS];

static void library_init();
static SystemClock get_free_clock();
static SystemClock_Timer get_free_timer(SystemClock system_clock);
static void free_timer(SystemClock system_clock, SystemClock_Timer timer);
static void process_timers(SystemClock system_clock);
static bool has_elapsed(uint16_t timer_time, uint16_t clock_time);
static void update_next_elapsed(SystemClock system_clock);

static void SystemClock_dummy_callback(void* context, void* extra_context, size_t timer_id){}

uint16_t SystemClock_current_time(SystemClock system_clock){
  return system_clock->current_time;
}

size_t SystemClock_start_timer(SystemClock system_clock, Timer_elapsed_callback callback, void* context, void* extra_context, uint16_t duration){
  if (callback == NULL){callback = SystemClock_dummy_callback;}
  SystemClock_Timer timer = get_free_timer(system_clock);
  if (timer == NULL) {return -1;}
  timer->callback = callback;
  timer->context = context;
  timer->extra_context = extra_context;
  timer->elapse_at = system_clock->current_time + duration;
  update_next_elapsed(system_clock);
  return timer->id;
}

void SystemClock_cancel_timer(SystemClock system_clock, size_t timer_id){
  if (timer_id == -1) {return;}
  free_timer(system_clock, &system_clock->timers[timer_id]);
  update_next_elapsed(system_clock);
}

void SystemClock_set_bool_callback(void* context, void* extra_context, size_t timer_id) {
  (void)extra_context;
  (void)timer_id;
  *((bool *)context) = true;
}

SystemClock SystemClock_create(){
  library_init();
  SystemClock system_clock = get_free_clock();
  if(NULL == system_clock) { return NULL; }
  system_clock->tick_rate = SYSTEM_CLOCK_TICK_RATE;
  system_clock->timer_count = 0;
  return system_clock;
}

void SystemClock_destroy(SystemClock system_clock){
  system_clock->available = true;
  system_clock->current_time = 0;
  for (int i = 0; i < NUM_SYSTEM_CLOCK_TIMERS; i++){
    system_clock->timers[i].available = true;
  }
}

void SystemClock_tick(SystemClock system_clock){
  system_clock->current_time+= system_clock->tick_rate;
  if (system_clock->timer_count > 0 && has_elapsed(system_clock->next_elapsed, system_clock->current_time)) {process_timers(system_clock);}
}

void SystemClock_set_time(SystemClock system_clock, uint16_t new_time){
  system_clock->current_time = new_time;
  update_next_elapsed(system_clock);
}

// Internal functions


static void library_init(){
  static bool init_complete = false;
  if (init_complete) {return;}
  init_complete = true;

  for (size_t i = 0; i < NUM_SYSTEM_CLOCKS; i++){
    clocks[i].available = true;
    clocks[i].current_time = 0;
    for (size_t j = 0; j < NUM_SYSTEM_CLOCK_TIMERS; j++){
      clocks[i].timers[j].id = j;
      clocks[i].timers[j].available = true;
    }
  }
}

static SystemClock get_free_clock(){
  SystemClock result = NULL;
  for (size_t i = 0; i < NUM_SYSTEM_CLOCKS; i++){
    if (clocks[i].available) {clocks[i].available = false; result =  &clocks[i]; break;}
  }
  return result;
}

static SystemClock_Timer get_free_timer(SystemClock system_clock){
  SystemClock_Timer result = NULL;
  for (size_t i = 0; i < NUM_SYSTEM_CLOCK_TIMERS; i++){
    if (system_clock->timers[i].available) {
      system_clock->timers[i].available = false;
      system_clock->timer_count++;
      result = &system_clock->timers[i];
      break;
    }
  }
  return result;
}

static void free_timer(SystemClock system_clock, SystemClock_Timer timer){
  timer->available = true;
  timer->callback = SystemClock_dummy_callback;
  timer->context = NULL;
  timer->extra_context = NULL;
  timer->elapse_at = 42;
  system_clock->timer_count--;
}

static void process_timers(SystemClock system_clock) {
  size_t todo[NUM_SYSTEM_CLOCK_TIMERS];
  size_t timers_elapsed = 0;
  for (int i = 0; i < NUM_SYSTEM_CLOCK_TIMERS; i++){
    SystemClock_Timer timer = &system_clock->timers[i];
    if (timer->available) { continue; }
    if (has_elapsed(timer->elapse_at, system_clock->current_time)){
      todo[timers_elapsed++] = i;
    }
  }

  for (int i = 0; i < timers_elapsed; i++){
    SystemClock_Timer timer = &system_clock->timers[todo[i]];
    timer->callback(timer->context, timer->extra_context, timer->id);
    free_timer(system_clock, timer);
  }
  update_next_elapsed(system_clock);
}

static void update_next_elapsed(SystemClock system_clock){
  if (system_clock->timer_count == 0) { return; }
  int32_t min_dist = 65537;
  SystemClock_Timer min_timer = NULL;


  for(int i = 0; i < NUM_SYSTEM_CLOCK_TIMERS; i++){
    SystemClock_Timer timer = &system_clock->timers[i];
    if (timer->available){ continue; }
    int32_t dist = SystemClock_wraparound_distance(timer->elapse_at, system_clock->current_time);
    if (dist < min_dist){
      min_timer = timer;
      min_dist = dist;
    }
  }

  if (min_timer) {
    system_clock->next_elapsed = min_timer->elapse_at;
  }
}

static bool has_elapsed(uint16_t timer_time, uint16_t clock_time) {
  return (SystemClock_wraparound_distance(timer_time, clock_time) <= 0);
}

// range is -TIMER_WINDOW..(uint16_max - TIMER_WINDOW)
int32_t SystemClock_wraparound_distance(uint16_t timer_time, uint16_t clock_time) {
  // uint16_t l = clock_time - SYSTEM_CLOCK_TIMER_WINDOW;
  // if (clock_time < l && l < timer_time){
  //   return clock_time - timer_time;
  // }
  // if (timer_time < l && l < clock_time){
  //   return (65536 - clock_time) + timer_time;
  // }
  // return timer_time - clock_time;

  int16_t delta = timer_time - clock_time;
  if(delta > SYSTEM_CLOCK_TIMER_WINDOW) {
    delta = clock_time - timer_time;
  }
  return delta;
}
