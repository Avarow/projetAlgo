#include <histogram.h>

typedef struct _couleur{
	unsigned char R;
	unsigned char G;
	unsigned char B;
	int freq;
} couleur;

/*
* 
*/
void afficher_couleur(couleur c){
	printf("R:%d  G:%d  B:%d \n",c.R,c.G,c.B);
	printf("Frequence : %d \n \n", c.freq);
}

void quantification(histo h, unsigned char* tab, int K){
	printf("Quantification en cours...\n");
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
	printf("Quantification effectuee\n");
}

void couleur_proche(unsigned char* pixel, unsigned char* tab, int K){
	double dr=TAILLE;
	double dg=TAILLE;
	double db=TAILLE; 
	int index=0;
	unsigned char r = pixel[0];
	unsigned char g = pixel[1];
	unsigned char b = pixel[2];
	for(int i=0;i<K;i+=3){
		double new_dr=abs(tab[i]-pixel[0]);
		double new_dg=abs(tab[i+1]-pixel[1]);
		double new_db=abs(tab[i+2]-pixel[2]);

		if (new_dr+new_dg+new_db==0){
			index=i;
		}
		else{

		if( (new_dr+new_dg+new_db) < (dr+dg+db) ) {
			dr=new_dr;
			dg=new_dg;
			db=new_db;
			index=i;
			}
		}
	}
	for(int j=0;j<3;j++){
		pixel[j]=tab[index+j];
	}
}

image mapping(image input, unsigned char* tab, int K){
	
	printf("Mapping en cours...\n");
	image res=input;
	for(int i=0;i<res.hauteur*res.largeur;i++){
		couleur_proche(res.pixels[i],tab, K);
	}
	printf("Mapping effectue\n");
	return res;

}

int main(int argc, char **argv){
	char* nom=argv[1];
	int nbCouleurs=atoi(argv[2]);
	image input = readImage(nom);
	histo h=create_histo();
	init_histo(h,nom);
	unsigned char* tabCouleurs=malloc(sizeof(char)*nbCouleurs*3);
	quantification(h,tabCouleurs,nbCouleurs);
	image res = mapping(input,tabCouleurs,nbCouleurs);
	strcat(nom,"_reduit");
	strcat(nom,".ppm");
	writeImage(res,nom);
}