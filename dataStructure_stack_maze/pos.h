#pragma once
#include <stdbool.h>

typedef struct pos {
	int x, y;
} Position;

Position move_to(Position pos, int dir);