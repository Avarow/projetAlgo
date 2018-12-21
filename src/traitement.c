#include "traitement.h"

image readImage(char* nom){
	image img;
	char c;
	FILE * file=fopen(nom,"r");
	if (file != NULL){
    fscanf(file,"%3s",img.magic_number);
   	//printf("img magic number : %s\n", img.magic_number);
    
    char c1,c2;
    char com[255];
    fscanf(file,"%c%c",&c1,&c2);
    // pour ignorer les commentaires
    // @todo : Adapter le changement lorsque l'on rencontre un commentaire vide
    while(c2 =='#'){
      do{
	     fscanf(file,"%s",com);
	     printf("ON IGNORE : %s \n",com);
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
      if (img.magic_number[1]=='3'){
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
    fclose(file);
	}
  else{
    printf("ERREUR OUVERTURE DE FICHIER\n");
  }
  return img;
}


void asciiToBinary(image img, char* nom){
  if (img.magic_number[1]=='2' || img.magic_number[1]=='3'){
    char* c;
    if (img.magic_number[1]=='2')
      c="P5";
    else
      c="P6";
    FILE * file=fopen(nom,"wb");
    
    /*
    @todo : GERER LA TAILLE DES DONNEES 
    ACTUELLEMENT, PAS AUTOMATIQUE, VALEURS JUSTE POUR LE FICHIER DE TEST
    */
    char hauteur[2];
    char largeur[2];
    char pixel_max[2];

    // on convertit les données en string 
    sprintf(hauteur,"%d",img.hauteur);
    sprintf(largeur,"%d",img.largeur);
    sprintf(pixel_max,"%d",(int)img.pixel_max);

    // on concat la hauteur et la largeur
    char* res = malloc(sizeof(char*)*3);
    strcpy(res,hauteur);
    strcat(res," ");
    strcat(res,largeur);

    // on écrit le magic number
    fwrite(c,sizeof(char)*2,1,file);  
    fwrite("\n",1,1,file);
    // on écrit la hauteur et la largeur 
    fwrite(res,sizeof(char*)*3,1,file);
    fwrite("\n",1,1,file);
    // on écrit le pixel max
    fwrite(pixel_max,sizeof(char*)*2,1,file);
    fwrite("\n",1,1,file);

    for(int i=0;i<img.largeur*img.hauteur;i++){
      printf("i :%d\n",i );
      fwrite(img.pixels[i],3*sizeof(char*),1,file);
    }
    //fwrite(img.pixels,1,img.largeur*img.hauteur*3,file);
    fclose(file);
  }
  else{
    printf("Erreur : l'image n'est pas au format ASCII. Impossible de la convertir en binaire. \n");
  }
}






