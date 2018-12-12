#include <histogram.h>

cell* create_cell(int B, cell* next){
	cell* c;
	c=(cell*)malloc(sizeof(cell));
	c->B=(unsigned char)B;
	c->freq=1;
	c->next=next;
	return c;
}


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

	// on remet à zéro notre élément de parcours 
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
