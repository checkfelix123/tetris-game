#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <stdbool.h>


extern bool ge_handle_move(int dx, int dy, int dr);
extern bool ge_is_game_over(void);
extern void ge_set_game_over_false(void);
#endif
