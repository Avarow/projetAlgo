#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct{
	char magic_number[3];
	int largeur;
	int hauteur;
	unsigned char pixel_max;
	unsigned char** pixels; 
} image;

image readImage(char* nom);

image allocImage(image img);

void binaryToAscii(image img, char* nom);

void asciiToBinary(image img, char* nom);