#include <stdio.h>
#include <stdlib.h>

typedef struct _cell{
	unsigned char B;
	int freq;
	struct _cell* next;
} cell;

cell* create_cell(int B, cell* next);

void insert_cell(int B, cell* head);