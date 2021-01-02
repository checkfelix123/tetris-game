#include <GLFW/glfw3.h>
#include "types.h"

/*
	Den Block abhängig von der tatsächlichen Position im Spielfeld machen.
*/
position type_get_position(position pos1, position pos2) {

	return (position) { pos1.x + pos2.x, (pos1.y >= 1) ? (pos1.y + pos2.y >= 22) ? 21 : pos1.y + pos2.y : pos1.y + pos2.y};
}

void render_quad(const position pos, const color color) {
	static_assert(sizeof(color) == 4, "detected unexpected size for colors");
	
	glColor3ubv((unsigned char *)&color);
	
	glBegin(GL_QUADS);
	glVertex2i(pos.x,     pos.y);
	glVertex2i(pos.x,     pos.y + 1);
	glVertex2i(pos.x + 1, pos.y + 1);
	glVertex2i(pos.x + 1, pos.y);
	glEnd();
}



void render(const block block) {
		for (int j = 0; j < PIXELS; j++) {
			render_quad(type_get_position(block.pos, block.type->pixels[block.pos.rotation][j]), block.type->color);
		}
}

 shapes_t* get_shape() {
    static shapes_t shapes[SHAPE_SIZE] = {
         {'Z', color_red, {
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
            {{2, 0}, {2, 1}, {1, 1}, {1, 2}},
            {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
            {{1, 0}, {1, 1}, {0, 1}, {0, 2}},}
        },
         {'T', color_purple, {
            {{0, 1}, {1, 1}, {2, 1}, {1, 2}},
            {{1, 0}, {0, 1}, {1, 1}, {1, 2}},
            {{1, 0}, {0, 1}, {1, 1}, {2, 1}},
            {{1, 0}, {1, 1}, {2, 1}, {1, 2}},}},
        {'S', color_green, {
            {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
            {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
            {{1, 1}, {2, 1}, {0, 2}, {1, 2}},
            {{0, 0}, {0, 1}, {1, 1}, {1, 2}},}
        },
         {'O', color_yellow, {
             {{1, 0}, {2, 0}, {1, 1}, {2, 1}},
            {{1, 0}, {2, 0}, {1, 1}, {2, 1}},
            {{1, 0}, {2, 0}, {1, 1}, {2, 1}},
            {{1, 0}, {2, 0}, {1, 1}, {2, 1}},
        }},
        {'L', color_orange, {
            {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
            {{0, 1}, {1, 1}, {2, 1}, {0, 2}},
            {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
            {{2, 0}, {0, 1}, {1, 1}, {2, 1}},}
        },
        {'J', color_blue, {
            {{1, 0}, {1, 1}, {0, 2}, {1, 2}},
            {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
            {{1, 0}, {2, 0}, {1, 1}, {1, 2}},
            {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
        }},
        {'I',color_cyan, {
            {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
            {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
            {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
            {{0, 1}, {1, 1}, {2, 1}, {3, 1}},}
        },
    };
    return shapes;
}