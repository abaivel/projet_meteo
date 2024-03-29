#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fichier.h"

pArbreAVL creerArbreAVL(Case r){
	pArbreAVL noeud = malloc(sizeof(ArbreAVL));
	if (noeud==NULL){
		exit(4);
	}
	noeud->elmt=r;
	noeud->gauche=NULL;
	noeud->droit=NULL;
	noeud->equilibre=0;
	return noeud;
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

pArbreAVL rotationGauche(pArbreAVL a){
	pArbreAVL pivot;
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

pArbreAVL rotationDroite(pArbreAVL a){
	pArbreAVL pivot;
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

pArbreAVL doubleRotationGauche(pArbreAVL a){
	a->droit = rotationDroite(a->droit);
	return rotationGauche(a);
}

pArbreAVL doubleRotationDroite(pArbreAVL a){
	a->droit = rotationGauche(a->droit);
	return rotationDroite(a);
}

pArbreAVL equilibrerAVL(pArbreAVL a){
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

pArbreAVL insertionAVL(pArbreAVL a,int* h, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy1, int colonne_moy2, int moyenne1, int moyenne2, int minimum, int maximum){
	/*  pArbreAVL : l'arbre
        tab : le tabelau contenant les éléments de la ligne à placer dans la liste
        nb_colonnes : le nombre d"élements dans tab
        colonne_tri : le numéro de la colonne à trier (débute à 0)
        colonne_moy1 : le numéro de la colonne avec laquelle la moyenne (et le minimum et maximum si demandé) sera calculé (débute à 0)
        colonne_moy2 : pareil, elle sert uniquement lorsqu'il y a deux moyennes à calculer (pour le graphique avec les vecteurs)
        moyenne1 : vaut 1 si il y a au moins une moyenne à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon
        moyenne2 : vaut 1 si il y a une deuxième moyenne à calculer (avec la colonne n°colonne_moy2 évidemment), 0 sinon
        minimum : vaut 1 si il y a un minimum à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon
        maximum : vaut 1 si il y a un maximum à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon

        Retourne le nouvel arbre
    */
	if (a==NULL){
		*h=1;
		return creerArbreAVL(creerCase(tab,nb_colonnes,colonne_moy1,colonne_moy2));
	}else if (strtod(tab[colonne_tri],NULL)<strtod((a->elmt).tab[colonne_tri],NULL)){
		a->gauche=insertionAVL(a->gauche,h,tab,nb_colonnes,colonne_tri,colonne_moy1,colonne_moy2,moyenne1,moyenne2,minimum,maximum);
		*h=-*h;
	}else if (strtod(tab[colonne_tri],NULL)>strtod((a->elmt).tab[colonne_tri],NULL)){
		a->droit=insertionAVL(a->droit,h,tab,nb_colonnes,colonne_tri,colonne_moy1,colonne_moy2,moyenne1,moyenne2,minimum,maximum);
	}else{
		*h=0;
		if (strcmp(tab[colonne_moy1],"\n")!=0){
            if (strtod((a->elmt).tab[colonne_tri],NULL)==strtod(tab[colonne_tri],NULL) && colonne_moy1>-1){
                if (colonne_moy2==-1){
                    if (moyenne1==1){
                        (a->elmt).somme1=(a->elmt).somme1+strtod(tab[colonne_moy1],NULL);
                        (a->elmt).nb_times=(a->elmt).nb_times+1;
                    }if (minimum==1){
                        double nb=strtod(tab[colonne_moy1],NULL);
                        if (nb<(a->elmt).minimum){
                            (a->elmt).minimum=nb;
                        }
                    }if (maximum==1){
                        double nb=strtod(tab[colonne_moy1],NULL);
                        if (nb>(a->elmt).maximum){
                            (a->elmt).maximum=nb;
                        }
                    }
                }else{
                    (a->elmt).somme1=(a->elmt).somme1+(sin(strtod(tab[colonne_moy1],NULL)*(M_PI/180.0))*strtod(tab[colonne_moy2],NULL));
                    (a->elmt).nb_times=(a->elmt).nb_times+1;
                    (a->elmt).somme2=(a->elmt).somme1+(cos(strtod(tab[colonne_moy1],NULL)*(M_PI/180.0))*strtod(tab[colonne_moy2],NULL));
                }
                //libererTab2(tab,nb_colonnes);
            }
        }
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

pArbreAVL insertionAVL_date(pArbreAVL a, int* h, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy, int moyenne){
    /*  pArbreAVL : l'arbre
        tab : le tabelau contenant les éléments de la ligne à placer dans la liste
        nb_colonnes : le nombre d"élements dans tab
        colonne_tri : le numéro de la colonne à trier (débute à 0)
        colonne_moy : le numéro de la colonne avec laquelle la moyenne (et le minimum et maximum si demandé) sera calculé (débute à 0)
        moyenne : vaut 1 si il y a au moins une moyenne à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon

        Retourne le nouvel arbre
    */
	if (a==NULL){
		*h=1;
		return creerArbreAVL(creerCase(tab,nb_colonnes,colonne_moy,-1));
	}else if (strcmp(tab[colonne_tri],(a->elmt).tab[colonne_tri])<0){
		a->gauche=insertionAVL_date(a->gauche, h, tab, nb_colonnes, colonne_tri, colonne_moy, moyenne);
		*h=-*h;
	}else if (strcmp(tab[colonne_tri],(a->elmt).tab[colonne_tri])>0){
		a->droit=insertionAVL_date(a->droit, h, tab, nb_colonnes, colonne_tri, colonne_moy, moyenne);
	}else{
		*h=0;
		if (strcmp(tab[colonne_moy],"\n")!=0){
            if (strcmp((a->elmt).tab[colonne_tri],tab[colonne_tri])==0 && colonne_moy>-1){
                if (moyenne==1){
                    (a->elmt).somme1=(a->elmt).somme1+strtod(tab[colonne_moy],NULL);
                    (a->elmt).nb_times=(a->elmt).nb_times+1;
                }
                libererTab2(tab,nb_colonnes);
            }
        }
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

pArbreAVL insertionAVL3(pArbreAVL a, int* h, char** tab, int nb_colonnes, int colonne_tri1, int colonne_tri2, int colonne_tri3){
    /*  pArbreAVL : l'arbre
        tab : le tabelau contenant les éléments de la ligne à placer dans la liste
        nb_colonnes : le nombre d"élements dans tab
        colonne_tri1,2 et 3 sont les colonnes par lequel on trie

        Retourne le nouvel arbre
    */
	if (a==NULL){
		*h=1;
		return creerArbreAVL(creerCase(tab,nb_colonnes,-1,-1));
	}else if ((strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])>0 ||
    (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((a->elmt).tab[colonne_tri2],tab[colonne_tri2])>0) ||
	(strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((a->elmt).tab[colonne_tri2],tab[colonne_tri2])==0 &&
	strcmp((a->elmt).tab[colonne_tri3],tab[colonne_tri3])>0))){
		a->gauche=insertionAVL3(a->gauche,h,tab,nb_colonnes,colonne_tri1,colonne_tri2,colonne_tri3);
		*h=-*h;
	}else if (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])<0 ||
            (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((a->elmt).tab[colonne_tri2],tab[colonne_tri2])<0) ||
            (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((a->elmt).tab[colonne_tri2],tab[colonne_tri2])==0 &&
            strcmp((a->elmt).tab[colonne_tri3],tab[colonne_tri3])<0)){
		a->droit=insertionAVL3(a->droit,h,tab,nb_colonnes,colonne_tri1,colonne_tri2,colonne_tri3);
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

pArbreAVL insertionAVL_avec_max(pArbreAVL a, int* h, Case c){
	if (a==NULL){
		*h=1;
		return creerArbreAVL(c);
	}else if (c.maximum<=(a->elmt).maximum){
		a->gauche=insertionAVL_avec_max(a->gauche,h,c);
		*h=-*h;
	}else if (c.maximum>(a->elmt).maximum){
		a->droit=insertionAVL_avec_max(a->droit,h,c);
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


void triAVL(pArbreAVL arbre, pArbreAVL* nouv_arbre,int nb_colonnes){
    if (arbre!=NULL){
        triAVL(arbre->gauche, nouv_arbre,nb_colonnes);
        if (*nouv_arbre==NULL){
            *nouv_arbre=creerArbreAVL(arbre->elmt);
        }else{
            *nouv_arbre=insertionAVL_avec_max(*nouv_arbre,&((*nouv_arbre)->equilibre),arbre->elmt);
            *nouv_arbre=equilibrerAVL(*nouv_arbre);
        }
        triAVL(arbre->droit,nouv_arbre,nb_colonnes);
		free(arbre);
    }
}

int ecrire_avl_in_file_croissant(FILE* fichier_sortie, ArbreAVL* arbre, char type[4], int* i,int nb_colonnes){
    int r=0,r1=0,r2=0;
    if (arbre!=NULL){
        r1=ecrire_avl_in_file_croissant(fichier_sortie,arbre->gauche,type,i, nb_colonnes);
        if (!strcmp(type,"-w")){
            double x1=strtod((arbre->elmt).tab[4],NULL);
            double y1=strtod((arbre->elmt).tab[3],NULL);
            r=fprintf(fichier_sortie, "%lf %lf %lf %lf\n", x1,y1,(arbre->elmt).somme1/(arbre->elmt).nb_times,(arbre->elmt).somme2/(arbre->elmt).nb_times);
        }else if (!strcmp(type,"-t1") || !strcmp(type,"-p1")){
            r=fprintf(fichier_sortie, "%d %s %lf %lf %lf\n", *i, (arbre->elmt).tab[0], (arbre->elmt).somme1/(arbre->elmt).nb_times, (arbre->elmt).minimum, (arbre->elmt).maximum);
        }else if (!strcmp(type,"-t2") || !strcmp(type,"-p2")){
            r=fprintf(fichier_sortie, "%s %lf\n", (arbre->elmt).tab[0], (arbre->elmt).somme1/(arbre->elmt).nb_times);
        }
        if (r==EOF){
            r=1;
        }else{
            r=0;
        }
        *i=*i+1;
        r2=ecrire_avl_in_file_croissant(fichier_sortie,arbre->droit,type,i, nb_colonnes);
        libererCase(arbre->elmt,nb_colonnes);
		free(arbre);
    }
    return (r || r1 || r2);
}

int ecrire_avl_in_file_decroissant(FILE* fichier_sortie, ArbreAVL* arbre, char type[4], int nb_colonnes){
    int r=0,r1=0,r2=0;
    if (arbre!=NULL){
        r1=ecrire_avl_in_file_decroissant(fichier_sortie,arbre->droit,type, nb_colonnes);
        if (!strcmp(type,"-h")){
            r=fprintf(fichier_sortie, "%s %s %s\n",(arbre->elmt).tab[1],(arbre->elmt).tab[0],(arbre->elmt).tab[2]);
        }else if (!strcmp(type,"-m")){
            r=fprintf(fichier_sortie, "%s %s %lf\n\n",(arbre->elmt).tab[3],(arbre->elmt).tab[2],(arbre->elmt).maximum);
        }
        if (r==EOF){
            return 1;
        }
        r2=ecrire_avl_in_file_decroissant(fichier_sortie,arbre->gauche,type, nb_colonnes);
        libererCase(arbre->elmt,nb_colonnes);
		free(arbre);
    }
    return (r || r1 || r2);
}


int ecrire_avl_in_file_p3t3(FILE* fichier_sortie, ArbreAVL* arbre, char type[4], char heure[], char id[], int nb_colonnes){
    int r=0,r1=0,r2=0;
    if (arbre!=NULL){
        r1=ecrire_avl_in_file_p3t3(fichier_sortie,arbre->gauche,type,heure,id, nb_colonnes);
        char * couleur[24]={"84AD41","6600AD","05A1AD","EC0700","FFD32E","F4116D","241279","81FF23",
                            "11A234","8AF4FF","075400","000000","FF3D9A","A60082","5E35FF","FF777B",
                            "00FF9C","627600","FF00FC","6D071A","9683EC","9B6337","665A53","924A53"};
        if (strlen(heure)==0){
            strcpy(heure,(arbre->elmt).tab[2]);
            strcpy(id,(arbre->elmt).tab[0]);
        }else{
            if (strcmp(heure,(arbre->elmt).tab[2])){
                strcpy(heure,(arbre->elmt).tab[2]);
                strcpy(id,(arbre->elmt).tab[0]);
                r=fprintf(fichier_sortie, "\n\n");
            }else if (strcmp(id,(arbre->elmt).tab[0])){
                strcpy(id,(arbre->elmt).tab[0]);
                r=fprintf(fichier_sortie, "\n\n");
            }
        }
        char* date=(arbre->elmt).tab[1];
        r=fprintf(fichier_sortie, "%s %lf %s\n",date,strtod((arbre->elmt).tab[3],NULL),couleur[atoi(heure)]);
        if (r==EOF){
            return 1;
        }
        r2=ecrire_avl_in_file_p3t3(fichier_sortie,arbre->droit,type,heure,id, nb_colonnes);
        libererCase(arbre->elmt,nb_colonnes);
		free(arbre);
    }
    return (r || r1 || r2);
}


