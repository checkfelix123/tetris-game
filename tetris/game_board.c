


#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "game_board.h"
#include "types.h"
#include "current_block.h"

static size_t block_count = 0;

typedef int arr[1][1];
static void gb_clear_line(int i);
static game_board_t gamepad = { false, {color_black} };
static int GAMEPAD_ROWS_CURRENT = 0;
static int GAMEPAD_START = 0;
static void set_position(position p) {
	if (!gamepad[p.y][p.x].is_valid ) gamepad[p.y][p.x].is_valid = true;
}

void gb_init() {
	for (int i = 0; i < GB_ROWS; i++) {
		for (int j = 0; j < GB_COLS; j++) {
			gamepad[i][j].is_valid = false; 
			gamepad[i][j].color = color_black;
		}
	}
}
bool gb_is_valid_position(const position pos) {

	if (!(pos.x >= 0 && pos.y >= 0 && pos.x < GB_COLS && pos.y < GB_ROWS)) {
		//cb_init();
		return false;
	}
	if (gamepad[pos.y][pos.x].is_valid) {
		return false;
	}
	return true;

}
/*
	Überprüft, ob eine Zeile gültig und gelöscht werden kann.	
*/
bool gb_is_line_valid() {
	//Zeile ist am Anfang valid.
	bool is_line_valid = true;
	for (int i = GAMEPAD_START; i < GAMEPAD_ROWS_CURRENT; i++) {
		for (int j = 0; j < GB_COLS; j++) {
			//wenn ein Element fehlt, dann ist die Zeile invalid.
			if (!gamepad[i][j].is_valid) {
				is_line_valid = false;
				continue;
			}
		}
		//wenn line valid dann lösche sie
		if (is_line_valid) {

			gb_clear_line(i); //löschen der Zeile und Verschieben der oberen Zeilen.
			return is_line_valid;
		}
		is_line_valid = true;
	}
	return is_line_valid;
}
static void gb_clear_line(int start) {
	for (int j = start; j < GAMEPAD_ROWS_CURRENT; j++) {
		gamepad[start][j].is_valid = false;
		gamepad[start][j].color = color_black;
	}
	for (int i = (start + 1); i < GB_ROWS; i++) {
		for (int j = 0; j < GB_COLS; j++) {
			gamepad[i -1][j].is_valid = gamepad[i][j].is_valid;
			gamepad[i -1][j].color = gamepad[i][j].color;
		}
	}
}
void gb_add_block(const block block) {
	for (int j = 0; j < PIXELS; j++) {
		position p = type_get_position(block.pos, block.type->pixels[block.pos.rotation][j]);
		if (!gamepad[p.y][p.x].is_valid)
		{
			gamepad[p.y][p.x].is_valid = true;
			gamepad[p.y][p.x].color = block.type->color;
		}
		if (p.y > GAMEPAD_ROWS_CURRENT) {
			GAMEPAD_ROWS_CURRENT = p.y;
		}
	}
}

void gb_render(void) {
	for (int i = 0; i < GB_ROWS; i++) {
		for (int j = 0; j < GB_COLS; j++) {
			if (gamepad[i][j].is_valid) {
				position p = { j, i };
				render_quad(p, gamepad[i][j].color);
			}
		}
	}
}