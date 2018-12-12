#include <stdio.h>
#include <stdlib.h>

typedef struct _cell{
	unsigned char B;
	int freq;
	struct _cell* next;
} cell;

cell* create_cell(int B, cell* next);

cell* insert_cell(int B, cell* head);

cell* delete_list(cell* list);

void print_cell(cell* head);