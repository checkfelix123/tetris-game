#include <assert.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include "timer.h"

static double interval = 1.0;
static timer_func callback = NULL;
static bool timer_is_running = false;

static void reset_time(void);
void timer_start(double itvl, timer_func on_tick) {
	assert(on_tick != NULL);
	assert(itvl > 0);

	interval = itvl;
	callback = on_tick;
	timer_is_running = true;
	reset_time();
}
void timer_fire(void) {
	if (!timer_is_running) {
	
		return;
	}
	if (glfwGetTime() >= interval) {
		callback();
		reset_time();
		
	}
}
void timer_reduce_interval(const double reduction) {
	if ((interval-reduction) >= 0.15) {
		interval -= reduction;
	}
}
void timer_stop(void) {
	timer_is_running = false;
}
void timer_restart(void) {
	timer_is_running = true;
	reset_time();
}
static void reset_time(void) {
	glfwSetTime(0.0);
}
