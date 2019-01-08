#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

typedef struct{
	char magic_number[3];
	int largeur;
	int hauteur;
	unsigned char pixel_max;
	unsigned char** pixels; 
} image;

image readImage(char* nom);

void writeImage(image img, char* nom);

image allocImage(image img);