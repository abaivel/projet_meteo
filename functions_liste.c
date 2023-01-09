#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

Chainon* creationChainon(int a){
    Chainon* c = malloc(sizeof(Chainon));
    if (c==NULL){
        printf("c malloc a échoué");
        exit(1);
    }
    (*c).elmt = a;
    (*c).suivant = NULL;
    return c;
}

Chainon* insertDebut(Chainon* pliste, int a){
    Chainon* c=creationChainon(a);
    (*c).suivant = pliste;
    return c;
}

Chainon* insertFin(Chainon* pliste, int a){
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

Chainon* ajout_croissant(Chainon* pliste, int a){
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


}

void freeListe(Chainon* pliste){
    while (pliste!=NULL){
        Chainon* c = pliste;
        pliste=pliste->suivant;
        free(c);
    }
}

