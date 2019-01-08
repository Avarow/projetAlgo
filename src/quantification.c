#include <histogram.h>

typedef struct _couleur{
	int R;
	int G;
	int B;
	int freq;
} couleur;

void afficher_couleur(couleur c){
	printf("R:%d  G:%d  B:%d \n",c.R,c.G,c.B);
	printf("Frequence : %d \n \n", c.freq);
}

void quantification(histo h, int* tab, int K){
	histo_iter iter=create_histo_iter(h);

	int i;
	int* coul=malloc(sizeof(int)*3);
	couleur liste[K];	
	couleur vide;
	vide.R=0;
	vide.G=0;
	vide.B=0;
	vide.freq=-1;
	for(i=0;i<K;i++){
		liste[i]=vide;
	}
	
	couleur c;
	int freq;

	do{
		give_color_histo_iter(iter,coul);
		freq=give_freq_histo_iter(iter);
		c.R=coul[0];
		c.G=coul[1];
		c.B=coul[2];
		c.freq=freq;
		int pos=K;
		// on cherche la position où insérer la couleur dans la liste triée par ordre croissant d'occurences 
		while(pos>0 && c.freq>liste[pos-1].freq){
			pos--;
		}
		// on décale ensuite vers la "droite" les éléments
		for(int j=K-1;j>pos;j--){
			liste[j]=liste[j-1];
		}	
		// enfin, on ajoute la couleur au bon endroit de la liste
		if (pos<K)
			liste[pos]=c;
	}while(next_histo_iter(iter));


	for(int k=0;k<K;k++){
		afficher_couleur(liste[k]);
	}
	
	

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