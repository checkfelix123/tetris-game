#ifndef TIMER_H
#define TIMER_H

typedef void (*timer_func)(void);

extern void timer_start(double interval, timer_func on_tick);
extern void timer_restart(timer_func on_tick);
extern void timer_fire(void);
extern void timer_stop(void);
extern void timer_reduce_interval(const double reduction);
#endif
