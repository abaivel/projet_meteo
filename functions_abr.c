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

pArbre creerArbre(int r){
	pArbre noeud = malloc(sizeof(Arbre));
	if (noeud==NULL){
		exit(1);
	}
	noeud->elmt=r;
	noeud->gauche=NULL;
	noeud->droit=NULL;
	return noeud;
}

int ajouterFilsGauche(pArbre a, int e){
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

int ajouterFilsDroit(pArbre a, int e){
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

pArbre insertABR(pArbre a, int e){
	if (a==NULL){
		return creerArbre(e);
	}else if (e<a->elmt){
		a->gauche=insertABR(a->gauche, e);
	}else if (e>a->elmt){
		a->droit=insertABR(a->droit, e);
	}
	return a;
}

pArbre suppMax(pArbre a, int* pe){
	pArbre tmp;
	if (existeFilsDroit(a)==1){
		a->droit=suppMax(a->droit, pe);
	}else{
		*pe=a->elmt;
		tmp=a;
		a=a->gauche;
		free(tmp);
	}
	return a;
}

pArbre suppression(pArbre a, int e){
	pArbre tmp;
	if (a==NULL){
		return a;
	}else if (e>a->elmt){
		a->droit=suppression(a->droit, e);
	}else if (e<a->elmt){
		a->gauche=suppression(a->gauche, e);
	}else if (existeFilsGauche==0){
		tmp=a;
		a=a->droit;
		free(tmp);
	}else{
		a->gauche=suppMax(a->gauche, &(a->elmt));
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
