#include <histogram.h>
#include <traitement.h>


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
	hist=malloc(TAILLE*sizeof(cell *));
		for (int i=0;i<TAILLE;i++){
   			hist[i] =malloc(TAILLE*sizeof(cell));
		}

	// initialisation 
	for (int j=0;j<TAILLE;j++){
		for (int k=0;k<TAILLE;k++){
			hist[j][k]=NULL;
		}
	}

	return hist;
	

}

void init_histo(histo h){
	image img=readImage("./PROJET_FONDEMENTS/IMAGES/deg.ppm");
}

void delete_histo(histo h){
	for (int i=0;i<TAILLE;i++){
		for(int j=0;j<TAILLE;j++){
			h[i][j]=delete_list(h[i][j]);
		}
	}
	free(h);
	h=NULL;
}

