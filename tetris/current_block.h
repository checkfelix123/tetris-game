#ifndef CURRENT_BLOCK_H
#define CURRENT_BLOCK_H

#include "types.h"

extern void cb_move(int dx, int dy, int dr);
extern void cb_render(void); //schreibweise mit void nur in c in c++ nicht mehr
extern block cb_new_block(void);
extern block cb_get_block(void);
extern void cb_init(void);



#endif