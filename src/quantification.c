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

	int* coul=malloc(sizeof(int)*3);
	couleur liste[K];	
	couleur vide;
	vide.R=0;
	vide.G=0;
	vide.B=0;
	vide.freq=-1;
	for(int i=0;i<K;i++){
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


	for(int k=0;k<K;k+=3){
		tab[k]=liste[k].R;
		tab[k+1]=liste[k].G;
		tab[k+2]=liste[k].B;
	}
	delete_histo_iter(iter);
}

void couleur_proche(unsigned char* color, int* tab, unsigned char* pixel){
	for(int i=0;i<3;i++){
		color[i]=pixel[i];
		
	}
}

image mapping(image input, int* tab, int K){
	
	image res=input;
	for(int i=0;i<res.hauteur*res.largeur;i++){
		// rechercher couleur dans tab 
		//printf("i %d\n",i);
		//res.pixels[i]=malloc(1);
		// ecrire couleur dans output
		for(int j=0;j<3;j++){ 
			res.pixels[i][j]=tab[j];
		}
			//printf("i %d \n",i);
			//printf("j %d \n",j);

	}

	return res;

}

int main(int argc, char **argv){
	char* nom=argv[1];
	image input = readImage(nom);
	histo h=create_histo();
	init_histo(h,nom);
	int nbCouleurs=10;
	int* tabCouleurs=malloc(nbCouleurs*3);
	quantification(h,tabCouleurs,nbCouleurs);
	printf("Quantification effectuee.\n");
	image res = mapping(input,tabCouleurs,nbCouleurs);
	writeImage(res,"test.ppm");
}