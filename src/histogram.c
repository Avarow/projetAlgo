#include <histogram.h>

cell* create_cell(int B, cell* next){
	cell* c;
	c=(cell*)malloc(sizeof(cell));
	c->B=(unsigned char)B;
	c->freq=1;
	return c;
}