#ifndef TYPES_H
#define TYPES_H

#include <assert.h>
#include <stdbool.h>

#define GB_ROWS 22
#define GB_COLS 11

#define UNUSED(var) ((void)var)


#define SHAPE_SIZE 7
#define PIXELS 4
#define BLOCK_ROTATIONS 4


typedef enum {
	color_black = 0x000000U,
	color_red = 0x0000FFU,
	color_green = 0x00FF00U,
	color_blue = 0xFF0000U,
	color_yellow = color_red | color_green,
	color_magenta = color_red | color_blue,
	color_cyan = color_green | color_blue,
	color_white = color_red | color_green | color_blue,
	color_purple = 0x0800080u,
	color_orange = 0x0054FFu,
} color;

typedef struct {
	int x, y;
	int rotation;
} position;

typedef struct {
	char name;
	color color; 
	position pixels[BLOCK_ROTATIONS][PIXELS];
}  shapes_t;

typedef struct {
	shapes_t *type;
	position pos;
} block;
extern void render_quad(const position pos, const color color);
extern void render_block(const block block);
extern void render(const block);
extern position type_get_position(position pos1, position pos2);
extern shapes_t* get_shape();
#endif
