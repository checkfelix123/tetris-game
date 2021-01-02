#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <stdbool.h>
#include "types.h"

typedef struct {
	bool is_valid;
	position block_pos;
	color color;
} item_t;


typedef item_t game_board_t[GB_ROWS][GB_COLS];
//#define MAX_BLOCKS_COUNT ((GB_ROWS) * (GB_COLS))
extern bool gb_is_line_valid(void);
extern bool gb_is_valid_position(const position pos); //gb gameboard
extern void gb_add_block(const block block);
extern void gb_render(void);
extern void gb_init(void);
#endif
