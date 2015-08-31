#include "servoSundial.h"

// Realtime-clock handling functions

// This sets up the interrupt clock
void initTimer0_Clock(void);

// These functions are called periodically
// to update the global time variables
// They cascade when needed (second -> minute)
void everySecond(void);
void everyMinute(void);
void everyHour(void);
