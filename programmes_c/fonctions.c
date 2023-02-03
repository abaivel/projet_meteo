#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

Case creerCase(char** tab, int nb_colonnes, int colonne_moy1, int colonne_moy2){
	Case c;
	c.tab=tab;
	c.nb_colonnes=nb_colonnes;
	if (colonne_moy1!=-1){
        c.somme1=strtod(tab[colonne_moy1],NULL);
        c.nb_times=1;
        c.minimum=strtod(tab[colonne_moy1],NULL);
        c.maximum=strtod(tab[colonne_moy1],NULL);
	}if (colonne_moy2!=-1){
        c.somme2=strtod(tab[colonne_moy2],NULL);
	}
	return c;
}

Chainon* entrer_donnees_liste(FILE* fichier_entree, FILE* fichier_sortie, int colonne_tri, int colonne_moy1, int colonne_moy2, int nb_colonnes, int moy1, int moy2, int mini, int maxi, int decroissant, int date, int tri_multiple, int colonnes_tri_mutiple[3]){
    /* Explications des paramètres :
        fichier_entree : le fichier à lire
        fichier_sortie : le fichier dans lequel il faut écrire
        colonne_tri : le numéro de la colonne à trier (débute à 0)
        colonne_moy1 : le numéro de la colonne avec laquelle la moyenne (et le minimum et maximum si demandé) sera calculé (débute à 0)
        colonne_moy2 : pareil, elle sert uniquement lorsqu'il y a deux moyennes à calculer (pour le graphique avec les vecteurs), vaut -1 si il y a pas de deuxième moyenne à calculer
        nb_colonnes : le nombre de colonnes dans le fichier file_in
        moy1 : vaut 1 si il y a au moins une moyenne à calculer (avec la colonne n°column_moy1 évidemment), 0 sinon
        moy2 : vaut 1 si il y a une deuxième moyenne à calculer (avec la colonne n°column_moy2 évidemment), 0 sinon
        mini : vaut 1 si il y a un minimum à calculer (avec la colonne n°column_moy1 évidemment), 0 sinon
        maxi : vaut 1 si il y a un maximum à calculer (avec la colonne n°column_moy1 évidemment), 0 sinon
        decroissant : vaut 0 si le tri doit être croissant, 1 sinon
        date : vaut 1 si la donnée à trier est une date (une date sera prise en compte comme une chaine de caractère par rapport à autre type de données

    La fonction retourne un chiffre signifiant qu'il y a une erreur, pour l'instant retourne 0 si il n'y a pas d''erreur et 1 si il y en a. A voir si il y a besoin de plus de précisions
    */
    char ligne[TAILLE_MAX_LIGNE];
    Chainon* liste=NULL;
    char** tab=NULL;
    char* ligne2;
    if (tri_multiple==1){
        do{
            ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
            if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                tab=LigneVersTab(ligne,nb_colonnes);
                liste=ajout_croissant3(liste,tab,nb_colonnes,colonnes_tri_mutiple[0],colonnes_tri_mutiple[1],colonnes_tri_mutiple[2]);
            }
        }while (ligne2!=NULL);
    }else if (date==1){
        do{
            ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
            if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                tab=LigneVersTab(ligne,nb_colonnes);
                liste=ajout_croissant_date(liste,tab,nb_colonnes,colonne_tri,colonne_moy1,moy1);
            }
        }while (ligne2!=NULL);
    }else{
        if (decroissant==0){
            do{
                ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
                if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                    tab=LigneVersTab(ligne,nb_colonnes);
                    liste=ajout_croissant(liste,tab,nb_colonnes,colonne_tri,colonne_moy1, colonne_moy2,moy1,moy2,mini,maxi);
                }
            }while (ligne2!=NULL);
        }else{
            do{
                ligne2=fgets(ligne, TAILLE_MAX_LIGNE, fichier_entree);
                if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                    tab=LigneVersTab(ligne,nb_colonnes);
                    liste=ajout_decroissant(liste,tab,nb_colonnes,colonne_tri,colonne_moy1, colonne_moy2,moy1, moy2,mini,maxi);
                }
            }while (ligne2!=NULL);
        }
    }
    return liste;
}

Arbre* entrer_donnees_abr(FILE* fichier_entree, FILE* fichier_sortie, int colonne_tri, int colonne_moy1, int colonne_moy2, int nb_colonnes, int moy1, int moy2, int mini, int maxi, int date, int tri_multiple, int colonnes_tri_mutiple[3]){
    char ligne[TAILLE_MAX_LIGNE];
    Arbre* arbre=NULL;
    char** tab=NULL;
    char* ligne2;
    if (tri_multiple==1){
        do{
            ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
            if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                tab=LigneVersTab(ligne,nb_colonnes);
                arbre=insertionABR3(arbre,tab,nb_colonnes,colonnes_tri_mutiple[0],colonnes_tri_mutiple[1],colonnes_tri_mutiple[2]);
            }
        }while (ligne2!=NULL);
    }else if (date==1){
        do{
            ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
            if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                tab=LigneVersTab(ligne,nb_colonnes);
                arbre=insertionABR_date(arbre,tab,nb_colonnes,colonne_tri,colonne_moy1,moy1);
            }
        }while (ligne2!=NULL);
    }else{
        do{
            ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
            if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                tab=LigneVersTab(ligne,nb_colonnes);
                arbre=insertionABR(arbre,tab,nb_colonnes,colonne_tri,colonne_moy1,colonne_moy2,moy1,moy2,mini,maxi);
            }
        }while (ligne2!=NULL);
    }
    return arbre;
}

ArbreAVL* entrer_donnees_avl(FILE* fichier_entree, FILE* fichier_sortie, int colonne_tri, int colonne_moy1, int colonne_moy2, int nb_colonnes, int moy1, int moy2, int mini, int maxi, int date, int tri_multiple, int colonnes_tri_mutiple[3]){
    char ligne[TAILLE_MAX_LIGNE];
    ArbreAVL* arbre=NULL;
    char** tab=NULL;
    char* ligne2;
    if (tri_multiple==1){
        do{
            ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
            if (strstr(ligne,";;") ==NULL && ligne2!=NULL){
                tab=LigneVersTab(ligne,nb_colonnes);
                if (arbre!=NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                    arbre=insertionAVL3(arbre,&(arbre->equilibre),tab,nb_colonnes,colonnes_tri_mutiple[0],colonnes_tri_mutiple[1],colonnes_tri_mutiple[2]);
                    arbre=equilibrerAVL(arbre);
                }else if (arbre==NULL){
                    arbre=creerArbreAVL(creerCase(tab,nb_colonnes,-1,-1));
                }
            }
        }while (ligne2!=NULL);
    }else if (date==1){
        do{
            ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
            if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                tab=LigneVersTab(ligne,nb_colonnes);
                if (arbre!=NULL){
                    arbre=insertionAVL_date(arbre,&(arbre->equilibre),tab,nb_colonnes,colonne_tri,colonne_moy1,moy1);
                    arbre=equilibrerAVL(arbre);
                }else if (arbre==NULL){
                    arbre=creerArbreAVL(creerCase(tab,nb_colonnes,colonne_moy1,-1));
                }
            }
        }while (ligne2!=NULL);
    }else{
        do{
            ligne2=fgets(ligne, TAILLE_MAX_LIGNE-1, fichier_entree);
            if (strstr(ligne,";;") ==NULL && ligne2!=NULL && ligne[strlen(ligne)-2]!=';'){
                tab=LigneVersTab(ligne,nb_colonnes);
                if (arbre!=NULL){
                    arbre=insertionAVL(arbre,&(arbre->equilibre),tab,nb_colonnes,colonne_tri,colonne_moy1,colonne_moy2,moy1,moy2,mini,maxi);
                    arbre=equilibrerAVL(arbre);
                }else if (arbre==NULL){
                    arbre=creerArbreAVL(creerCase(tab,nb_colonnes,colonne_moy1,colonne_moy2));
                }
            }
        }while (ligne2!=NULL);
    }
    return arbre;
}

char** LigneVersTab(char* ligne, int nb_colonnes){
    char** tab=malloc(sizeof(char*)*nb_colonnes);
    if (tab==NULL){
        exit(4);
    }
    int k=0;
    int j=0;
    for (int i=0;i<strlen(ligne);i++){
        if (ligne[i]!='\n'){
            if (ligne[i]==';'){
                j=0;
                k++;
            }else{
                if (j==0){
                    tab[k]=calloc(TAILLE_MAX_CASE, sizeof(char));
                    if (tab[k]==NULL){
                        exit(4);
                    }
                }
                tab[k][j]=ligne[i];
                j++;
            }
        }
    }
    return tab;
}

void libererTab2(char** tab, int t){
    for (int i=0;i<t;i++){
        free(tab[i]);
    }
}

void libererCase(Case c, int nb_colonnes){
    libererTab2(c.tab, nb_colonnes);
    free(c.tab);
}
