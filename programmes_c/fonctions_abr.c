#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fichier.h"

pArbre creerArbre(Case r){
	pArbre noeud = malloc(sizeof(Arbre));
	if (noeud==NULL){
		exit(4);
	}
	noeud->elmt=r;
	noeud->gauche=NULL;
	noeud->droit=NULL;
	return noeud;
}

pArbre insertionABR_date(pArbre a, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy, int moyenne){
	if (a==NULL){
		return creerArbre(creerCase(tab,nb_colonnes,colonne_moy,-1));
	}else if (strcmp(tab[colonne_tri],(a->elmt).tab[colonne_tri])<0){
		a->gauche=insertionABR_date(a->gauche, tab, nb_colonnes, colonne_tri, colonne_moy, moyenne);
	}else if (strcmp(tab[colonne_tri],(a->elmt).tab[colonne_tri])>0){
		a->droit=insertionABR_date(a->droit, tab, nb_colonnes, colonne_tri, colonne_moy, moyenne);
	}else{
        if (strcmp(tab[colonne_moy],"\n")!=0){
            if (strcmp((a->elmt).tab[colonne_tri],tab[colonne_tri])==0 && colonne_moy>-1){
                if (moyenne==1){
                    (a->elmt).somme1=(a->elmt).somme1+strtod(tab[colonne_moy],NULL);
                    (a->elmt).nb_times=(a->elmt).nb_times+1;
                }
                libererTab2(tab,nb_colonnes);
            }
        }

	}
	return a;
}

pArbre insertionABR(pArbre a, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy1, int colonne_moy2, int moyenne1, int moyenne2, int minimum, int maximum){
	if (a==NULL){
		return creerArbre(creerCase(tab,nb_colonnes,colonne_moy1,colonne_moy2));
	}else if (strtod(tab[colonne_tri], NULL)<strtod((a->elmt).tab[colonne_tri],NULL)){
		a->gauche=insertionABR(a->gauche, tab, nb_colonnes, colonne_tri, colonne_moy1, colonne_moy2, moyenne1, moyenne2, minimum, maximum);
	}else if (strtod(tab[colonne_tri], NULL)>strtod((a->elmt).tab[colonne_tri],NULL)){
		a->droit=insertionABR(a->droit, tab, nb_colonnes, colonne_tri, colonne_moy1, colonne_moy2, moyenne1, moyenne2, minimum, maximum);
	}else{
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
		        libererTab2(tab,nb_colonnes);
		    }
		}
	}
	return a;
}

pArbre insertionABR3(pArbre a, char** tab, int nb_colonnes, int colonne_tri1, int colonne_tri2, int colonne_tri3){
	if (a==NULL){
		return creerArbre(creerCase(tab,nb_colonnes,-1,-1));
	}else if (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])>0 ||
    (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((a->elmt).tab[colonne_tri2],tab[colonne_tri2])>0) ||
	(strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((a->elmt).tab[colonne_tri2],tab[colonne_tri2])==0 &&
	strcmp((a->elmt).tab[colonne_tri3],tab[colonne_tri3])>0)){
		a->gauche=insertionABR3(a->gauche, tab, nb_colonnes, colonne_tri1, colonne_tri2, colonne_tri3);
	}else if (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])<0 ||
            (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((a->elmt).tab[colonne_tri2],tab[colonne_tri2])<0) ||
            (strcmp((a->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((a->elmt).tab[colonne_tri2],tab[colonne_tri2])==0 &&
            strcmp((a->elmt).tab[colonne_tri3],tab[colonne_tri3])<0)){
		a->droit=insertionABR3(a->droit, tab, nb_colonnes, colonne_tri1, colonne_tri2, colonne_tri3);
	}
	return a;
}

pArbre insertionABR_avec_max(pArbre a, Case c){
	if (a==NULL){
		return creerArbre(c);
	}else if (c.maximum<=(a->elmt).maximum){
		a->gauche=insertionABR_avec_max(a->gauche, c);
	}else if (c.maximum>(a->elmt).maximum){
		a->droit=insertionABR_avec_max(a->droit, c);
	}
	return a;
}

void triABR(pArbre arbre, pArbre* nouv_arbre,int nb_colonnes){
    if (arbre!=NULL){
        triABR(arbre->gauche, nouv_arbre,nb_colonnes);
        *nouv_arbre=insertionABR_avec_max(*nouv_arbre,arbre->elmt);
        triABR(arbre->droit,nouv_arbre,nb_colonnes);
		free(arbre);
    }
}

int ecrire_abr_in_file_croissant(FILE* fichier_sortie, Arbre* arbre, char type[4], int* i, int nb_colonnes){
    int r=0,r1=0,r2=0;
    if (arbre!=NULL){
        r1=ecrire_abr_in_file_croissant(fichier_sortie,arbre->gauche,type,i, nb_colonnes);
        if (!strcmp(type,"-w")){
            double x1=strtod((arbre->elmt).tab[4],NULL);
            double y1=strtod((arbre->elmt).tab[3],NULL);
            r=fprintf(fichier_sortie, "%lf %lf %lf %lf\n", x1,y1,(arbre->elmt).somme1/(arbre->elmt).nb_times,(arbre->elmt).somme2/(arbre->elmt).nb_times);
        }else if (!strcmp(type,"-t1") || !strcmp(type,"-p1")){
            r=fprintf(fichier_sortie, "%d %s %lf %lf %lf\n", *i, (arbre->elmt).tab[0], (arbre->elmt).somme1/(arbre->elmt).nb_times, (arbre->elmt).minimum, (arbre->elmt).maximum);
        }else if (!strcmp(type,"-t2") || !strcmp(type,"-p2")){
            r=fprintf(fichier_sortie, "%s %lf\n",(arbre->elmt).tab[0], (arbre->elmt).somme1/(arbre->elmt).nb_times);
        }
        if (r==EOF){
            return 1;
        }
        *i=*i+1;
        r2=ecrire_abr_in_file_croissant(fichier_sortie,arbre->droit,type,i, nb_colonnes);
        libererCase(arbre->elmt,nb_colonnes);
		free(arbre);
    }
    return (r || r1 || r2);
}

int ecrire_abr_in_file_decroissant(FILE* fichier_sortie, Arbre* arbre, char type[4], int nb_colonnes){
    int r=0,r1=0,r2=0;
    if (arbre!=NULL){
        r1=ecrire_abr_in_file_decroissant(fichier_sortie,arbre->droit,type, nb_colonnes);
        if (!strcmp(type,"-h")){
            r=fprintf(fichier_sortie, "%s %s %s\n",(arbre->elmt).tab[1],(arbre->elmt).tab[0],(arbre->elmt).tab[2]);
        }else if (!strcmp(type,"-m")){
            r=fprintf(fichier_sortie, "%s %s %lf\n\n",(arbre->elmt).tab[3],(arbre->elmt).tab[2],(arbre->elmt).maximum);
        }
        if (r==EOF){
            return 1;
        }
        r2=ecrire_abr_in_file_decroissant(fichier_sortie,arbre->gauche,type, nb_colonnes);
        //libererCase(arbre->elmt,nb_colonnes);
		//free(arbre);
    }
    return (r || r1 || r2);
}


int ecrire_abr_in_file_p3t3(FILE* fichier_sortie, Arbre* arbre, char type[4], char heure[], char id[], int nb_colonnes){
    int r=0,r1=0,r2=0;
    if (arbre!=NULL){
        r1=ecrire_abr_in_file_p3t3(fichier_sortie,arbre->gauche,type,heure,id, nb_colonnes);
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
        r2=ecrire_abr_in_file_p3t3(fichier_sortie,arbre->droit,type,heure,id, nb_colonnes);
        //libererCase(arbre->elmt,nb_colonnes);
		//free(arbre);
    }
    return (r || r1 || r2);
}

