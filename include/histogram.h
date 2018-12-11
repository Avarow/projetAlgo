#include <stdio.h>
#include <stdlib.h>

typedef struct _cell{
	unsigned char B;
	int freq;
	struct cell* next;
} cell;

cell* create_cell(int B, cell* next);