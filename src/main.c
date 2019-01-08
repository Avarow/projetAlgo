#include <histogram.h>

int main(int argc, char **argv){
	char* nom=argv[1];
	histo h=create_histo();
	init_histo(h,nom);
	histo_iter iter=create_histo_iter(h);
	int* c=malloc(sizeof(int)*3);
	do{
		give_color_histo_iter(iter,c);
		printf("PIXEL : R:%d  V:%d  B:%d \n Lum : %d \n Nb d'occurences : %d \n \n",c[0],c[1],c[2],(c[0]+c[1]+c[2])/3,give_freq_histo_iter(iter)  );
	}
	while(next_histo_iter(iter));

	
	delete_histo_iter(iter);
	
	
	

}
