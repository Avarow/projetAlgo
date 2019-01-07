#include <histogram.h>

typedef struct _couleur{
	int R;
	int G;
	int B;
	int freq;
} couleur;

void quantification(histo h, int* tab, int K){
	histo_iter iter=create_histo_iter(h);

	int i=0;
	int* coul=malloc(sizeof(int)*3);
		
	couleur *liste=malloc(sizeof(couleur)*K);
	/*
	couleur c;
	int freq;
	
	while(next_histo_iter(iter)){
		give_color_histo_iter(iter,coul);
		freq=give_freq_histo_iter(iter);
		c.R=coul[0];
		c.G=coul[1];
		c.B=coul[2];
		c.freq=freq;
		int pos=0;
		// on cherche la position où insérer la couleur dans la liste triée par ordre croissant d'occurences 
		while(pos<K && c.freq>liste[pos].freq){
			pos++;
		}
		// on décale ensuite vers la "droite" les éléments
		for(int j=K;j>=pos;j--){
			liste[i]=liste[i-1];
		}	
		// enfin, on ajoute la couleur au bon endroit de la liste
		liste[pos]=c;
	}


	for(int k=0;k<K;k++){
		printf("%d\n",liste[k].freq );
	}
	
	*/

}

int main(int argc, char **argv){
	char* nom=argv[1];
	histo h=create_histo();
	init_histo(h,nom);
	// le nombre fixe de couleurs à afficher
	int nbCouleurs=10;
	int* tabCouleurs=malloc(nbCouleurs*3);
	quantification(h,tabCouleurs,nbCouleurs);
}