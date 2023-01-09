#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

int estVideAVL(pArbreAVL a){
	if (a==NULL){
		return 1;
	}
	return 0;
}

pArbre creerArbreAVL(int r){
	pArbre noeud = malloc(sizeof(ArbreAVL));
	if (noeud==NULL){
		exit(1);
	}
	noeud->elmt=r;
	noeud->gauche=NULL;
	noeud->droit=NULL;
	noeud->equilibre=0;
	return noeud;
}

int ajouterFilsGaucheAVL(pArbreAVL a, int e){
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

int ajouterFilsDroitAVL(pArbreAVL a, int e){
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

int max2(int a, int b){
	if (a<=b){
		return b;
	}
	return a;
}

int min2(int a, int b){
	if (a>=b){
		return b;
	}
	return a;
}

int min3(int a, int b, int c){
	if (a<=b && a<=c){
		return a;
	}else if (b<=a && b<=c){
		return b;
	}
	return c;
}

int max3(int a, int b, int c){
	if (a>=b && a>=c){
		return a;
	}else if (b>=a && b>=c){
		return b;
	}
	return c;
}

pArbre rotationGauche(pArbre a){
	pArbre pivot;
	int eq_a, eq_p;
	pivot = a->droit;
	a->droit = pivot->gauche;
	pivot->gauche = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a-max2(eq_p,0)-1;
	pivot->equilibre = min3(eq_a-2, eq_a+eq_p-2, eq_p-1);
	a=pivot;
	return a;
}

pArbre rotationDroite(pArbre a){
	pArbre pivot;
	int eq_a, eq_p;
	pivot = a->gauche;
	a->gauche = pivot->droit;
	pivot->droit = a;
	eq_a = a->equilibre;
	eq_p = pivot->equilibre;
	a->equilibre = eq_a-min2(eq_p,0)+1;
	pivot->equilibre = max3(eq_a+2, eq_a+eq_p+2, eq_p+1);
	a=pivot;
	return a;
}

pArbre doubleRotationGauche(pArbre a){
	a->droit = rotationDroite(a->droit);
	return rotationGauche(a);
}

pArbre doubleRotationDroite(pArbre a){
	a->droit = rotationGauche(a->droit);
	return rotationDroite(a);
}

pArbre equilibrerAVL(pArbre a){
	if (a->equilibre>=2){
		if (a->droit->equilibre>=0){
			return rotationGauche(a);
		}else{
			return doubleRotationGauche(a);
		}
	}else if (a->equilibre<=-2){
		if (a->gauche->equilibre<=0){
			return rotationDroite(a);
		}else{
			return doubleRotationDroite(a);
		}
	}
	return a;
}

pArbre insertionAVL(pArbre a, int e, int* h){
	if (a==NULL){
		*h=1;
		return creerArbre(e);
	}else if (e<a->elmt){
		a->gauche=insertionAVL(a->gauche,e,h);
		*h=-*h;
	}else if (e>a->elmt){
		a->droit=insertionAVL(a->droit,e,h);
	}else{
		*h=0;
		return a;
	}
	if (*h!=0){
		a->equilibre=a->equilibre+*h;
		if (a->equilibre ==0){
			*h=0;
		}else{
			*h=1;
		}
	}
	return a;
}

pArbre suppMinAVL(pArbre a, int* h, int* pe){
	pArbre tmp=NULL;
	if (a->gauche==NULL){
		*pe=a->elmt;
		*h=-1;
		tmp=a;
		a=a->droit;
		free(tmp);
		return a;
	}else{
		a->gauche=suppMinAVL(a->gauche,h, pe);
		*h=-*h;
	}
	if (*h!=0){
		a->equilibre=a->equilibre + *h;
		if (a->equilibre==0){
			*h=-1;
		}else{
			*h=0;
		}
	}
	return a;
}

pArbre suppAVL(pArbre a, int e, int* h){
	pArbre tmp;
	if (a==NULL){
		*h=1;
		return a;
	}else if (e>a->elmt){
		a->droit=suppAVL(a->droit,e,h);
	}else if (e<a->elmt){
		a->gauche=suppAVL(a->gauche,e,h);
		*h=-*h;
	}else if (existeFilsDroit(a)){
		a->droit=suppMinAVL(a->droit, h, &(a->elmt));
	}else{
		tmp=a;
		a=a->gauche;
		free(tmp);
		*h=-1;
	}
	if (*h!=0 && a!=NULL){
		a->equilibre=a->equilibre+*h;
		if (a->equilibre==0){
			*h=0;
		}else{
			*h=1;
		}
	}
	return a;
}

void freeAVL(pArbreAVL a){
	if (a!=NULL){
		freeArbre(a->gauche);
		freeArbre(a->droit);
		free(a);
	}
}
