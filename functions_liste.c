#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

Case creerCase(char** tab, int column_moy){
	Case c;
	c.tab=tab;
	c.somme=tab[column_moy];
	c.nb_times=1;
	c.minimum=tab[column_moy];
	c.maximum=tab[column_moy];
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

Chainon* ajout_croissant_int(Chainon* pliste, char** tab, int column_tri, int column_moy, int moyenne, int minimum, int maximum){
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
			
		}else if (minimum==1){
		}else if (maximum==1){
		}

	}else{
		Chainon* nouv_chainon = creationChainon(creerCase(tab,column_moy));
		nouv_chainon->suivant=c;
		avant->suivant=nouv_chainon;
	}
	return pliste;
}

void freeListe(Chainon* pliste){
    while (pliste!=NULL){
        Chainon* c = pliste;
        pliste=pliste->suivant;
        free(c);
    }
}

