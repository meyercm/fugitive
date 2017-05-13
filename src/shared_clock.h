#ifndef _SHARED_CLOCK_H
#define _SHARED_CLOCK_H

#include "system_clock.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/// Shared Clock

// The following methods all map the the `SystemClock` methods of similar
// name/signature, but are targeted to a specific singleton instance of the
// SystemClock.

uint16_t SharedClock_current_time();
size_t SharedClock_start_timer(Timer_elapsed_callback callback, void* context, void* extra_context, uint16_t duration_ms);
void SharedClock_cancel_timer(size_t timer_id);
void SharedClock_set_time(uint16_t new_time);

// ticks are deferred on the shared clock until `update` is called.
// sleeping is ok if there are no pending ticks.
void SharedClock_tick();
void SharedClock_update();
bool SharedClock_ok_sleep();

// Return a reference to the shared clock.
SystemClock SharedClock_get_clock();

// Destroy the instance, reset the library. Used in testing.
void SharedClock_reset();

#endif // _SHARED_CLOCK_H
