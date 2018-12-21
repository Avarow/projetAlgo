#include <histogram.h>
#include <assert.h>

void test_create_cell(){
	cell* c1;
	c1=create_cell(10,create_cell(20,create_cell(30,NULL)));
	assert(c1->B==10);
	assert(c1->next->B==20);
	assert(c1->next->freq==1);
	assert(c1->next->next->B==30);
	assert(c1->next->next->next==NULL);
	printf("TESTS CREATE_CELL : OK \n" );
}

void test_insert_cell(){
	cell* c1;
	c1=create_cell(10,create_cell(20,create_cell(30,NULL)));

	c1=insert_cell(2,c1);
	assert(c1->B==2);
	assert(c1->next->B==10);
	printf("TEST INSERT_CELL DEBUT : OK \n" );

	c1=insert_cell(12,c1);
	assert(c1->B==2);
	assert(c1->next->B==10);
	assert(c1->next->next->B==12);
	assert(c1->next->next->next->B==20);
	printf("TEST INSERT_CELL MILIEU : OK \n" );

	c1=insert_cell(32,c1);
	assert(c1->B==2);
	assert(c1->next->B==10);
	assert(c1->next->next->B==12);
	assert(c1->next->next->next->B==20);
	assert(c1->next->next->next->next->B==30);
	assert(c1->next->next->next->next->next->B==32);
	assert(c1->next->next->next->next->next->next==NULL);
	printf("TEST INSERT_CELL FIN : OK \n" );

	c1=insert_cell(2,c1);
	assert(c1->freq==2);
	printf("TEST INSERT_CELL VALEUR DEJA PRESENTE : OK \n" );
}

void test_delete_list(){
	cell* c1;
	c1=create_cell(10,create_cell(20,create_cell(30,NULL)));
	c1=delete_list(c1);
	assert(c1==NULL);
	printf("TEST DELETE : OK \n" );

}

void test_create_histo(){
	histo h;
	h=create_histo();
	cell* c=create_cell(10,NULL);
	h[0][0]=c;
	assert(h[0][0]->B==10);
	assert(h[0][0]->next==NULL);
	printf("TEST CREATION D'HISTO : OK \n" );

}

void test_delete_histo(){
	histo h;
	h=create_histo();
	cell* c1=create_cell(10,NULL);
	cell* c2=create_cell(100,NULL);	
	h[0][0]=c1;
	h[100][0]=c2;
	delete_histo(h);
	printf("TEST SUPPRESSION D'HISTO : OK \n" );
}

void test_init_histo(){
	histo h=create_histo();
	init_histo(h);
}

int main(){
	test_create_cell();
	test_insert_cell();
	test_delete_list();
	test_create_histo();
	test_delete_histo();
	test_init_histo();
	return 0;
}