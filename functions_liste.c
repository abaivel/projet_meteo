#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

Case creerCase(char** tab, int column_moy){
	Case c;
	c.tab=tab;
	c.somme=strtod(tab[column_moy]);
	c.nb_times=1;
	c.minimum=strtod(tab[column_moy]);
	c.maximum=strtod(tab[column_moy]);
	return c;
}

Chainon* creationChainon(Case a){
    Chainon* c = malloc(sizeof(Chainon));
    if (c==NULL){
        printf("c malloc a échoué");
        exit(1);
    }
    (*c).elmt = a;
    (*c).suivant = NULL;
    return c;
}

Chainon* insertDebut(Chainon* pliste, Case a){
    Chainon* c=creationChainon(a);
    (*c).suivant = pliste;
    return c;
}

Chainon* insertFin(Chainon* pliste, Case a){
    Chainon* c = pliste;
    if (pliste==NULL){
        return creationChainon(a);
    }
    while (c->suivant!=NULL){
        c=c->suivant;
    }
    c->suivant = creationChainon(a);
    return pliste;
}

/*Chainon* ajout_croissant(Chainon* pliste, int a){
	if (pliste==NULL){
		return creationChainon(a);
	}
	Chainon* c = pliste;
	Chainon* avant;
	while (c!=NULL && (c->elmt)<=a){
		if (c->suivant!=NULL){
			if ((c->suivant->elmt)>=a){
				avant=c;
			}
		}else{
			avant=c;
		}
		c=c->suivant;
	}
	Chainon* nouv_chainon = creationChainon(a);
	nouv_chainon->suivant=c;
	avant->suivant=nouv_chainon;
	return pliste;
}*/

Chainon* ajout_croissant_nb(Chainon* pliste, char** tab, int column_tri, int column_moy, int moyenne, int minimum, int maximum){
	if (pliste==NULL){
		return creationChainon(box);
	}
	Chainon* c = pliste;
	Chainon* avant;
	while (c!=NULL && ((c->elmt).tab[column_tri])<=strtod(tab[column_tri])){
		if (c->suivant!=NULL){
			if (((c->suivant->elmt).tab[column_tri])>=strtod(tab[column_tri])){
				avant=c;
			}
		}else{
			avant=c;
		}
		c=c->suivant;
	}
	if (((c->elmt).tab[column_tri])==strtod(tab[column_tri])){
		if (moyenne==1){
            (c->elmt).somme=(c->elmt).somme+strtod(tab[column_moy]);
            (c->elmt).nb_times=(c->elmt).nb_times+1;
		}if (minimum==1){
            double nb=strtod(tab[column_moy]);
            if (nb<(c->elmt).minimum){
                (c->elmt).minimum=nb;
            }
		}if (maximum==1){
            double nb=strtod(tab[column_moy]);
            if (nb>(c->elmt).maximum){
                (c->elmt).maximum=nb;
            }
		}

	}else{
		Chainon* nouv_chainon = creationChainon(creerCase(tab,column_moy));
		nouv_chainon->suivant=c;
		avant->suivant=nouv_chainon;
	}
	return pliste;
}

int write_list_in_file_filled_curve(FILE* file_out, Chainon* pliste){
    //$num_station $moyenne $min $max
    int i=0;
    while (pliste!=NULL){
        r=fprintf(file_out, "%d %lf %lf %lf", i, (pliste->elmt).somme, (pliste->elmt).minimum, (pliste->elmt).maximum);
        if (r==EOF){
            return 1;
        }
    }
    return 0;
}

void freeListe(Chainon* pliste){
    while (pliste!=NULL){
        Chainon* c = pliste;
        pliste=pliste->suivant;
        free(c);
    }
}

