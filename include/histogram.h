#include <stdio.h>
#include <stdlib.h>

#define TAILLE 256


typedef struct _cell{
	unsigned char B;
	int freq;
	struct _cell* next;
} cell;


// On définit le type histo comme étant un tableau à double entrée de pointeurs sur cell 
typedef cell *** histo;


cell* create_cell(int B, cell* next);

cell* insert_cell(int B, cell* head);

cell* delete_list(cell* list);

void print_cell(cell* head);

histo create_histo();