#include "pos.h"
int offset[4][2] = { {-1, 0}, 
					 {0, 1},
					 {1, 0},
					 {0, -1} }; //ºÏ, µ¿, ³², ¼­ 

Position move_to(Position pos, int dir) { //ÁÂÇ¥ ÀÌµ¿
	Position next;
	next.x = pos.x + offset[dir][0];
	next.y = pos.y + offset[dir][1];

	return next;
}

