#include <histogram.h>


/*
* Fonction utilisée pour initialiser une cellule avec une valeur B
*/
cell* create_cell(int B, cell* next){
	cell* c;
	c=(cell*)malloc(sizeof(cell));
	c->B=(unsigned char)B;
	c->freq=1;
	c->next=next;
	return c;
}


/*
* Fonction qu'on peut utiliser pour afficher le contenu d'une liste 
* (ie : fréquence et valeur B)
*/
void print_cell(cell* head){
	cell* current=head;
	while(current != NULL){
		printf(" B : %d\n",current->B );
		printf(" Frequence : %d\n",current->freq );
		printf("\n");
		current=current->next;
	}
}

/*
* @todo : Réfléchir à la possibilité de faire un algorithme récursif pour un code plus optimisé...
* L'algorithme marche de la manière suivante : 
* Dans un premier temps, on boucle dans la liste pour savoir si la valeur de B est présente dans une cellule.
* Si c'est le cas, alors on incrémente la fréquence de la cellule correspondante
* On souhaite de plus ajouter les valeurs de manière croissante 
* Il y a 3 cas de figure qui se présentent : 
* -- La cellule à ajouter est en tête de liste 
*	 On doit donc créer une cellule qui aura pour queue la tête de la liste 
* -- La cellule à ajouter est en fin de liste
*    On doit donc créer une cellule qui aura pour queue NULL et la raccrocher à l'élément précédent
* -- La cellule à ajouter est au "milieu"
*    On doit donc chercher les deux cellules entre lesquelles on ajoutera notre nouvelle cellule 
*/
cell* insert_cell(int B, cell* head){
	// current est une cellule qui nous permettra de nous situer dans la liste
	cell* current=head;
	cell* last=head;
	cell* add;
	int found=0;
	int pos=0;
	while (current != NULL && !found){
		if (current->B == B){
		// alors on a trouvé la valeur de B et on incrémente la fréquence
			current->freq+=1;
			found=1;
			}	
		current=current->next;
		}

	// on remet à zéro notre cellule de parcours 
	current=head;
	
	while (!found){
		// alors B n'est pas présent dans la liste
		// on doit alors recréer une cellule 
		// on cherche alors l'endroit où l'on doit insérer la cellule
		
		if (current->B < B){
			// on continue à chercher 

			if (current->next==NULL){
				// alors on est dans le cas où la cellule à ajouter est en fin de liste
					add=create_cell(B,NULL);
					current->next=add;
					found=1;
				}
				current=current->next;
				pos++;
		}
		else{
			if (pos == 0){
				// alors on ajoute la cellule en début de liste
				head=create_cell(B,current);
				found=1;
			}
			else{
				int i=1;
				while(i<pos){
					last=last->next;
					i++;
				}
				// on a dépassé, on raccroche la cellule à la précédente
				add=create_cell(B,current);
				last->next=add;
				found=1;
				}
			}
		}
		return head;
	}


/*
* Fonction récursive qui supprime et libère la mémoire utilisée par une liste
*/
cell* delete_list(cell* list){
	if (list != NULL){
		free(list);
		list=delete_list(list->next);
	}
	else{
		return NULL;
	}
}



histo create_histo(){
	// déclaration
	histo hist;
	
	// allocation
	hist=malloc(TAILLE*sizeof(cell*));
		for (int i=0;i<TAILLE;i++){
   			hist[i]=malloc(TAILLE*sizeof(cell));
		}

	// initialisation 
	for (int j=0;j<TAILLE;j++){
		for (int k=0;k<TAILLE;k++){
			hist[j][k]=NULL;
		}
	}

	return hist;
	

}


void init_histo(histo h, char* nom){
	image img=readImage(nom);
	unsigned char r,g,b;
	for (int i=0;i<img.largeur*img.hauteur;i++){
		// img.pixels[i] représente un pixel, constitué de 3 couleurs (r,g,b)
		r=img.pixels[i][0];
		g=img.pixels[i][1];
		b=img.pixels[i][2];
		if (h[r][g] == NULL){
			h[r][g]=create_cell(b,NULL);
		}
		else{
			h[r][g]=insert_cell(b,h[r][g]);
		}
		/*
		printf("ROUGE pixel %d : %u\n",i,img.pixels[i][0]);
        printf("VERT pixel %d : %u\n",i,img.pixels[i][1]);
        printf("BLEU pixel %d : %u\n",i,img.pixels[i][2]);
        printf("\n");
        */    
	}
	free(img.pixels);
}



void delete_histo(histo h){
	for (int i=0;i<TAILLE;i++){
		for(int j=0;j<TAILLE;j++){
			h[i][j]=delete_list(h[i][j]);
		}
	}
	free(h);
}

int give_freq_histo(histo h, int r, int g, int b){
	cell* cell=h[r][g];
	if (cell != NULL){
		while(cell->B != b){
			if(cell->next != NULL){
				cell=cell->next;
			}
			else{
				// alors il n y a pas le pixel que l'on recherche
				return 0;
			}
		}
	}
	else{
		return 0;
	}
	return cell->freq;
}


histo_iter create_histo_iter(histo h){

	int i;
	int j;
	histo_iter iter=(histo_iter)malloc(sizeof(histo_iter));
	iter->current=(cell*)malloc(sizeof(cell));
	boolean found=false;
	iter->h=h;


	for(i=0;i<TAILLE && !found;i++){
		for(j=0;j<TAILLE;j++){
			if (h[i][j] != NULL){
				iter->R=i;
				iter->G=j;
				iter->current=h[i][j];
				found=true;
				break;
			}
		}
	}

	if (!found){
		printf("Erreur. Histogramme vide.");
		abort();
	}
	return iter;
}

void start_histo_iter(histo_iter iter){
	iter=create_histo_iter(iter->h);
}

boolean next_histo_iter(histo_iter iter){
	int i=iter->R;
	int j=iter->G;
	boolean res=false;
	boolean found=false;
	if (iter->current->next != NULL){
		res=true;
		iter->current=iter->current->next;	
	}
	// alors on est en fin de liste de B 
	else{
		// on cherche la couleur suivante 
		if (j<TAILLE-1){
			j++;
		}
		else{
			i++;
			j=0;
		}
		while(!found && i<TAILLE){
			if (iter->h[i][j] != NULL){
				iter->R=i;
				iter->G=j;
				iter->current=iter->h[i][j];
				found=true;
			}
			else{
				if (j<TAILLE-1){
				j++;
				}
				else{
					i++;
					j=0;
				}
			}	
		}	
	}

	if(found){
		res=true;
	}

	return res;
}

void give_color_histo_iter(histo_iter iter, int* colors){
	// 0 = R, 1 = G, 2 = B
	colors[0]=iter->R;
	colors[1]=iter->G;
	colors[2]=iter->current->B;


}

int give_freq_histo_iter(histo_iter iter){
	return iter->current->freq;
}

void delete_histo_iter(histo_iter iter){
	delete_list(iter->current);
	free(iter);
}

