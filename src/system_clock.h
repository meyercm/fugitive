#ifndef _SYSTEM_CLOCK_H
#define _SYSTEM_CLOCK_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifndef NUM_SYSTEM_CLOCKS
#define NUM_SYSTEM_CLOCKS 1
#endif

#ifndef NUM_SYSTEM_CLOCK_TIMERS
#define NUM_SYSTEM_CLOCK_TIMERS 16
#endif

#ifndef SYSTEM_CLOCK_TICK_RATE
#define SYSTEM_CLOCK_TICK_RATE 1
#endif

#ifndef SYSTEM_CLOCK_TIMER_WINDOW
#define SYSTEM_CLOCK_TIMER_WINDOW INT16_MAX
#endif


typedef struct SystemClock_Struct* SystemClock;
typedef struct SystemClock_Timer_Struct* SystemClock_Timer;

typedef void (*Timer_elapsed_callback)(void* context, void* extra_context, size_t timer_id);

/// Client API:
/*
Consumes a SystemClock from the clock pool and initializes it for use. Returns
a pointer to the clock.
*/
SystemClock SystemClock_create();

/*
Releases a SystemClock back to the clock pool.
*/
void SystemClock_destroy(SystemClock clock);

/*
Returns the current time for this `SystemClock`.
*/
uint16_t SystemClock_current_time(SystemClock clock);

/*
Creates a timer on this clock, which will elapse after `duration` ticks. When
the timer elapses, the provided `Timer_elapsed_callback` will be called with the
provided `context` as well as the timer id.  Return value is a `timer_id` that
can be used to correlate timer creation with elapse, or more likely, to cancel
the timer before it elapses (see `SystemClock_cancel_timer`).
*/
size_t SystemClock_start_timer(SystemClock clock, Timer_elapsed_callback callback, void* context, void* extra_context, uint16_t duration_ms);

/*
Cancels a timer before it has elapsed. Of note, timers are recycled via a
pooling mechanism, so cancelling a timer after it has elapsed may negatively
impact another client.  Clients must only cancel their timers *before* the timer
has elapsed.  This re-use should be robust against most race conditions, but not
against sloppy clients. After cancelling a timer, the client has released it
back to the pool, and must not interact with it again.
*/
void SystemClock_cancel_timer(SystemClock clock, size_t timer_id);

/*
Timer callback provided for convenience: pass a bool* for the context and
this callback will set it to true when the timer expires.
*/
void SystemClock_set_bool_callback(void* context, void* extra_context, size_t timer_id);

// External, non-api functions
/*
This function is to be called by the hardware timer ISR, and is responsible for
advancing the state of the clock, triggering timers and updating the current
time.
*/
void SystemClock_tick(SystemClock clock);

/*
This function is provided for testing purposes, and allows setting the clock to
a specific time
*/
void SystemClock_set_time(SystemClock clock, uint16_t new_time);

/*
Exposed to rigorously test.
*/
int32_t SystemClock_wraparound_distance(uint16_t timer_time, uint16_t clock_time);
#endif // _SYSTEM_CLOCK_H
