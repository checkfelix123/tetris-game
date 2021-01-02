#include "game_engine.h"
#include "current_block.h"
#include "game_board.h"
#include "timer.h"

static bool game_over = false;
static bool init_handle_move_new = false;

static position get_next_move(const block current, int dx, int dy, int dr) {
	position pos = current.pos;
	pos.x += dx;
	pos.y += dy;
	pos.rotation = ((pos.rotation + dr) % 4);
	return pos;
}
static bool is_valid_move(const block current, int dx, int dy, int dr) {
	for (int j = 0; j < PIXELS; j++) {
		position position_next =get_next_move(current, dx, dy, dr);
		position p = type_get_position(position_next, current.type->pixels[position_next.rotation][j]);
		if (!gb_is_valid_position(p)){
				return false;
		}
	}
	return true;
}
bool ge_handle_move(int dx, int dy, int dr) {

	if (game_over) {
		return false;
	}
	block current = cb_get_block();	
	bool is_valid_t = is_valid_move(current, dx , dy, dr);
	if ((!is_valid_t) && dy == -1) { //dy -1 ist der untere Bildschirmrand
			gb_add_block(current);
			current = cb_new_block();
			if (!is_valid_move(current, dx, dy, dr)) {
				game_over = true;
			}
			else timer_reduce_interval(0.020);
	}
	gb_is_line_valid();
	if (is_valid_t) {
		cb_move(dx, dy, dr);
	}
	return !game_over;
}

bool ge_is_game_over() {
	return game_over;
}
void ge_set_game_over_false(){
	game_over = false;
}