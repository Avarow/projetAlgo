#include <histogram.h>
int main(){
	cell* c1;
	c1=create_cell(10,create_cell(20,create_cell(30,NULL)));
	c1=insert_cell(32,c1);
	//print_cell(c1);

	c1=delete_list(c1);
	print_cell(c1);

	return 0;
}
