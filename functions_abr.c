#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

int estVide(pArbre a){
	if (a==NULL){
		return 1;
	}
	return 0;
}

pArbre creerArbre(Case r){
	pArbre noeud = malloc(sizeof(Arbre));
	if (noeud==NULL){
		exit(1);
	}
	noeud->elmt=r;
	noeud->gauche=NULL;
	noeud->droit=NULL;
	return noeud;
}

int ajouterFilsGauche(pArbre a, Case e){
	//retourne 1 si "a" a déjà un fils gauche, 0 sinon
	if (estVide(a)==1){
		a=creerArbre(e);
	}
	if (a->gauche!=NULL){
		return 1;
	}
	pArbre nouv = creerArbre(e);
	a->gauche = nouv;
	return 0; 
}

int ajouterFilsDroit(pArbre a, Case e){
	//retourne 1 si "a" a déjà un fils droit, 0 sinon
	if (estVide(a)==1){
		a=creerArbre(e);
	}
	if (a->droit!=NULL){
		return 1;
	}
	pArbre nouv = creerArbre(e);
	a->droit = nouv;
	return 0; 
}

pArbre insertABR(pArbre a, Case e, int column){
	if (a==NULL){
		return creerArbre(e);
	}else if (strtod(e.tab[column])<a->elmt){
		a->gauche=insertABR(a->gauche, e);
	}else if (strtod(e.tab[column])>a->elmt){
		a->droit=insertABR(a->droit, e);
	}
	return a;
}


void freeArbre(pArbre a){
	if (a!=NULL){
		freeArbre(a->gauche);
		freeArbre(a->droit);
		free(a);
	}
}
