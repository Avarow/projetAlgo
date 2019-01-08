#include "traitement.h"

image readImage(char* nom){
  
	image img;
	char c;
	FILE * file=fopen(nom,"rb");

	if (file != NULL){
    fscanf(file,"%3s",img.magic_number);
   	//printf("img magic number : %s\n", img.magic_number);
    
    char c1,c2;
    char com[255];
    fscanf(file,"%c%c",&c1,&c2);
    // pour ignorer les commentaires
    // @todo : Adapter  lorsque l'on rencontre un commentaire vide
    while(c2 =='#'){
      do{
	     fscanf(file,"%s",com);
	     //printf("ON IGNORE : %s \n",com);
	     fscanf(file,"%c",&c1);
     }
      while(c1 != '\n');
      fscanf(file,"%c",&c2);
    }
   		
    // pour revenir un caractère avant 

    fseek(file,-1,SEEK_CUR);
   	int larg=0;
   	int haut=0;
   	int max;
   	fscanf(file,"%d",&larg);
   	fscanf(file,"%d",&haut);
   	fscanf(file,"%d",&max);
   	//printf("larg : %d haut : %d max : %d\n",larg,haut,max);
    img.largeur=larg;
    img.hauteur=haut;
    img.pixel_max=(unsigned char)max;  
      if (img.magic_number[1]=='2'){
        // alors c'est un PGM ASCII  
        int gris;      
        img.pixels=malloc(sizeof(char**)*img.largeur*img.hauteur);
        for (int i=0;i<img.largeur*img.hauteur;i++){
          img.pixels[i]=malloc(sizeof(char*));
          fscanf(file,"%d",&gris);
          img.pixels[i][0]=(unsigned char)gris;
          printf("PIXELS indice %d : %u\n",i,img.pixels[i][0]);
        }
      }
      if (img.magic_number[1]=='3' ){
        // alors c'est un PPM ASCII
        unsigned short r,v,b;
        img.pixels=malloc(sizeof(char**)*3*img.largeur*img.hauteur);
        for (int i=0;i<img.largeur*img.hauteur;i++){
          img.pixels[i]=malloc(3*sizeof(char*));
          fscanf(file,"%hu",&r);
          fscanf(file,"%hu",&v);
          fscanf(file,"%hu",&b);
          img.pixels[i][0]=(unsigned char)r;
          img.pixels[i][1]=(unsigned char)v;
          img.pixels[i][2]=(unsigned char)b;
          printf("ROUGE indice %d : %u\n",i,img.pixels[i][0]);
          printf("VERT indice %d : %u\n",i,img.pixels[i][1]);
          printf("BLEU indice %d : %u\n",i,img.pixels[i][2]);
          printf("\n");
        }
      }
      if (img.magic_number[1]=='6'){

        // en binaire, la première valeur affichée était toujours 10
        // j'en ai déduis que c'est un problème lié au retour à la ligne
        // il faut donc absorver le caractère avant de continuer
        char* retour=malloc(sizeof(char*));
        fread(retour,1,1,file);
        img.pixels=malloc(sizeof(char**)*3*img.largeur*img.hauteur);

        for (int i=0;i<img.largeur*img.hauteur;i++){

          img.pixels[i]=malloc(3*sizeof(char*));
          fread(img.pixels[i],3,1,file);
        }

      }

    fclose(file);
	}
  else{
    printf("Erreur lors de l'ouverture du fichier\n" );
    abort();
  }
  return img;
}


void writeImage(image img, char* nom){
    FILE * file=fopen(nom,"wb");
    if (file!=NULL){
      char* c="P6";
      fprintf(file, "%s\n",c);
      fprintf(file, "%d %d \n",img.largeur,img.hauteur);
      fprintf(file, "%d\n", (int)img.pixel_max);
      for(int i=0;i<img.hauteur*img.largeur;i++){
        fwrite(img.pixels[i],3,1,file);
      }
      fclose(file);
    }
    else{
     printf("Erreur lors de l'ouverture du fichier\n");
     abort();
  }
}







