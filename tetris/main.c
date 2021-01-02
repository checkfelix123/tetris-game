#include <stdio.h>
#include <stdlib.h>
#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include "types.h"
#include "current_block.h"
#include "game_board.h"
#include "game_engine.h"
#include "timer.h"
#include "irrklang.h"

#define WIDTH  400
#define HEIGHT ((WIDTH * GB_ROWS) / GB_COLS)
#define TIMER_INTERVAL 0.5

static void window_initialized(GLFWwindow *window);
static void render_window(void);
static void on_key(GLFWwindow* window, int key, int scancode, int action, int mods);
static void on_tick(void);
static void get_dx_dy_dr(int key, int* dx, int* dy, int *dr);
static void stop_resume();
static void tetris_init();
static bool is_game_stopped = false;

static void stop_resume() {

	if(!is_game_stopped){
		timer_stop();
		is_game_stopped = true;
	}
	else {
		timer_start(TIMER_INTERVAL, &on_tick);
		is_game_stopped = false;
	}
}
static void get_dx_dy_dr(int key, int *dx, int *dy, int *dr) {

	switch (key) {
		case GLFW_KEY_DOWN:
			*dy = -1;
			break;
		case GLFW_KEY_LEFT:
			*dx = -1;
			break;
		case GLFW_KEY_RIGHT:
			*dx = 1;
			break;
		case GLFW_KEY_UP:
			*dr = 1;
		default:
			return;
		}
}
void on_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	


	UNUSED(scancode);
	UNUSED(mods);
	UNUSED(window);

	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_R:
			ge_set_game_over_false();
			timer_restart(on_tick);
			tetris_init();
			break;
		}
	}
	else if (ge_is_game_over()) {
		return;
	}
	int dx = 0;
	int dy = 0;	
	int dr = 0;
	get_dx_dy_dr(key, &dx, &dy, &dr);
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_P:
			stop_resume();
			break;
		}
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && !is_game_stopped) {
		if (!ge_handle_move(dx, dy, dr)) {
			timer_stop();
		}
	}
	
}
static void window_initialized(GLFWwindow *window) {

	glfwSetKeyCallback(window, &on_key); //&kann weggellassen werden

	tetris_init();
	timer_start(TIMER_INTERVAL, &on_tick);
}
void on_tick() {
	on_key(NULL, GLFW_KEY_DOWN, 0, GLFW_PRESS, 0);
}

static void render_window(void) {

	timer_fire();
	gb_render();
	cb_render();
}
static void tetris_init() {
	cb_init();
	gb_init();
	gb_render();
}
int main() {

	if(!glfwInit()) {
		fprintf(stderr, "could not initialize GLFW\n");
		return EXIT_FAILURE;
	}

  GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Tetris", NULL, NULL);
	if(!window) {
		glfwTerminate();
		fprintf(stderr, "could not open window\n");
		return EXIT_FAILURE;
	}

	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetWindowAspectRatio(window, width, height); //enforce correct aspect ratio
	glfwMakeContextCurrent(window);

	window_initialized(window);
	play();

	while(!glfwWindowShouldClose(window)) {
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT); //clear frame buffer
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, width, 0, height); //orthogonal projection - origin is in lower-left corner
		glScalef((float)width / (float)GB_COLS, (float)height / (float)GB_ROWS, 1); //scale logical pixel to screen pixels

		render_window();


		const GLenum error = glGetError();
		if(error != GL_NO_ERROR) fprintf(stderr, "ERROR: %s\n", gluErrorString(error));

		glfwSwapBuffers(window);//push image to display
		// glfwPollEvents();
		glfwWaitEventsTimeout(TIMER_INTERVAL/5); //process all events of the application
	}

	glfwDestroyWindow(window);
	stop();
	glfwTerminate();
	return EXIT_SUCCESS;
}
