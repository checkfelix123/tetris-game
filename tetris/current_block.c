#include <stdlib.h>
#include "current_block.h"
#include "game_board.h"
#include "game_engine.h"
#include <time.h>
#include "types.h"


static color random_color(void);
static block current;
static color random_color(void);
static bool init_rand = true;

void cb_init() {
	srand((unsigned int)time(NULL));
	shapes_t* s = get_shape();
	current.type = &s[rand() % SHAPE_SIZE];
	current.pos = (position){ GB_COLS / 2, GB_ROWS - 1 };
}

void cb_move(int dx, int dy, int dr) {
	position pos = current.pos;
	pos.x += dx;
	pos.y += dy;
	pos.rotation = ((pos.rotation + dr) % 4);

	current.pos = pos;
}
void cb_render(void) {//schreibweise mit void nur in c in c++ nicht mehr
	render(current);
}

block cb_new_block() {
	shapes_t* s = get_shape();
	current.type = &s[rand() % SHAPE_SIZE];
	current.pos.x = GB_COLS / 2;
	current.pos.y = GB_ROWS - 1;
	return current;
}
block cb_get_block() {
	return current;
}


