#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fichier.h"

int main(int argc, char **argv){
	int decroissantd = 0;
	int algo = 0;
	char *nom_fichier_entre;
	char *nom_fichier_sortie;
	int num_colonne_sort=-1;
	int num_colonne_moy=-1;
	char type_donne[4]="";
	char* fin_nom_fichier;
	for (int i = 1; i < argc; i++){
		if (strstr(argv[i], "-") != NULL){
			if (!strcmp(argv[i], "-f") && i+1 < argc){
				if (argv[i+1][0] != '-'){
					nom_fichier_entre = argv[i+1];
				}else{
                    return 1;
				}
			} else if (!strcmp(argv[i], "-o") && i+1 < argc){
				if (argv[i+1][0] != '-'){
					nom_fichier_sortie = argv[i+1];
				}else{
                    return 1;
				}
            }else if (!strcmp(argv[i], "--avl")){
				algo = 0;
			} else if (!strcmp(argv[i], "--abr")){
				algo = 1;
			} else if (!strcmp(argv[i], "--tab")){
				algo = 2;
			}else if (!strcmp(argv[i], "-r")){
				decroissantd = 1;
			}/*else if (strstr(argv[i],"-t") !=NULL || strstr(argv[i],"-p") != NULL || !strcmp(argv[i],"-w") || !strcmp(argv[i],"-h") || !strcmp(argv[i],"-m")){
                strcpy(type_donne,argv[i]);
			}*/
			else {
				return 1;
			}
		}
	}
	fin_nom_fichier=strchr(nom_fichier_entre,'_');
	int m=1;
	type_donne[0]='-';
	while (fin_nom_fichier[m]!='.' && m<strlen(fin_nom_fichier)){
        type_donne[m]=fin_nom_fichier[m];
        m++;
	}
	type_donne[m]='\0';
	if (nom_fichier_entre == NULL || nom_fichier_sortie == NULL || strlen(type_donne) <= 1){
		return 1;
	}
	FILE* fichier_entree=fopen(nom_fichier_entre,"r");
	if (fichier_entree==NULL){
        	return 2;
	}
	FILE* fichier_sortie=fopen(nom_fichier_sortie,"w");
	if (fichier_sortie==NULL){
        	return 3;
	}
	int nb_colonnes;
	int r=0;
	if (algo==0){
		ArbreAVL* arbre;
		if (!strcmp(type_donne,"-t1") || !strcmp(type_donne,"-p1")){
		    arbre= entrer_donnees_avl(fichier_entree,fichier_sortie,0,1,-1,2,1,0,1,1,0,0,NULL);
		    nb_colonnes=2;
		    int i=0;
		    r=ecrire_avl_in_file_croissant(fichier_sortie,arbre,type_donne,&i,2);
		}else if (!strcmp(type_donne,"-t2") || !strcmp(type_donne,"-p2")){
		    arbre= entrer_donnees_avl(fichier_entree,fichier_sortie,0,1,-1,2,1,0,0,0, 1,0,NULL);
		    nb_colonnes=2;
		    int i=0;
		    r=ecrire_avl_in_file_croissant(fichier_sortie,arbre,type_donne,&i,2);
		}else if (!strcmp(type_donne,"-t3") || !strcmp(type_donne,"-p3")){
		    char heure[TAILLE_MAX_CASE]="";
		    char id[TAILLE_MAX_CASE]="";
		    int colonnes_tri[3]={2,0,1};
		    arbre=entrer_donnees_avl(fichier_entree,fichier_sortie,-1,-1,-1,4,0,0,0,0,0,1,colonnes_tri);
		    nb_colonnes=4;
		    r=ecrire_avl_in_file_p3t3(fichier_sortie,arbre,type_donne,heure,id,4);
		}else if (!strcmp(type_donne,"-w")){
		    arbre= entrer_donnees_avl(fichier_entree,fichier_sortie,0,1,2,4,1,1,0,0,0,0,NULL);
		    nb_colonnes=4;
		    int i=0;
		    r=ecrire_avl_in_file_croissant(fichier_sortie,arbre,type_donne,&i,4);
		}else if (!strcmp(type_donne,"-h")){
		    arbre= entrer_donnees_avl(fichier_entree,fichier_sortie,2,2,-1,3,0,0,0,0,0,0,NULL);
		    nb_colonnes=3;
		    int i=0;
		    r=ecrire_avl_in_file_decroissant(fichier_sortie,arbre,type_donne,3);
		}else if (!strcmp(type_donne,"-m")){
		    int i=0;
		    arbre=entrer_donnees_avl(fichier_entree,fichier_sortie,0,1,-1,4,0,0,0,1,0,0,NULL);
		    ArbreAVL* nouv_arbre=NULL;
		    triAVL(arbre, &nouv_arbre,4);
		    nb_colonnes=4;
		    r=ecrire_avl_in_file_decroissant(fichier_sortie,nouv_arbre,type_donne,4);
		}
		if (r==1){
            return 3;
		}
	}else if (algo==1){
		Arbre* arbre;
		if (!strcmp(type_donne,"-t1") || !strcmp(type_donne,"-p1")){
		    arbre= entrer_donnees_abr(fichier_entree,fichier_sortie,0,1,-1,2,1,0,1,1,0,0,NULL);
		    nb_colonnes=2;
		    int i=0;
		    r=ecrire_abr_in_file_croissant(fichier_sortie,arbre,type_donne,&i,2);
		}else if (!strcmp(type_donne,"-t2") || !strcmp(type_donne,"-p2")){
		    arbre= entrer_donnees_abr(fichier_entree,fichier_sortie,0,1,-1,2,1,0,0,0, 1,0,NULL);
		    nb_colonnes=2;
		    int i=0;
		    r=ecrire_abr_in_file_croissant(fichier_sortie,arbre,type_donne,&i,2);
		}else if (!strcmp(type_donne,"-t3") || !strcmp(type_donne,"-p3")){
		    char heure[TAILLE_MAX_CASE]="";
		    char id[TAILLE_MAX_CASE]="";
		    int colonnes_tri[3]={2,0,1};
		    arbre=entrer_donnees_abr(fichier_entree,fichier_sortie,-1,-1,-1,4,0,0,0,0,0,1,colonnes_tri);
		    nb_colonnes=4;
		    r=ecrire_abr_in_file_p3t3(fichier_sortie,arbre,type_donne,heure,id,4);
		}else if (!strcmp(type_donne,"-w")){
		    arbre= entrer_donnees_abr(fichier_entree,fichier_sortie,0,1,2,4,1,1,0,0,0,0,NULL);
		    nb_colonnes=4;
		    int i=0;
		    r=ecrire_abr_in_file_croissant(fichier_sortie,arbre,type_donne,&i,4);
		}else if (!strcmp(type_donne,"-h")){
		    arbre= entrer_donnees_abr(fichier_entree,fichier_sortie,2,2,-1,3,0,0,0,0,0,0,NULL);
		    nb_colonnes=3;
		    int i=0;
		    r=ecrire_abr_in_file_decroissant(fichier_sortie,arbre,type_donne,3);
		}else if (!strcmp(type_donne,"-m")){
		    int i=0;
		    arbre=entrer_donnees_abr(fichier_entree,fichier_sortie,0,1,-1,4,0,0,0,1,0,0,NULL);
		    Arbre* nouv_arbre=NULL;
		    triABR(arbre, &nouv_arbre,4);
		    nb_colonnes=4;
		    r=ecrire_abr_in_file_decroissant(fichier_sortie,nouv_arbre,type_donne,4);
		}
		if (r==1){
            return 3;
		}
	}else if (algo==2){
		Chainon* liste;
		if (!strcmp(type_donne,"-t1") || !strcmp(type_donne,"-p1")){
		    liste= entrer_donnees_liste(fichier_entree,fichier_sortie,0,1,-1,2,1,0,1,1,decroissantd,0,0,NULL);
		    nb_colonnes=2;
		}else if (!strcmp(type_donne,"-t2") || !strcmp(type_donne,"-p2")){
		    liste= entrer_donnees_liste(fichier_entree,fichier_sortie,0,1,-1,2,1,0,0,0,decroissantd, 1,0,NULL);
		    nb_colonnes=2;
		}else if (!strcmp(type_donne,"-t3") || !strcmp(type_donne,"-p3")){
		    int colonnes_tri[3]={2,0,1};
		    liste=entrer_donnees_liste(fichier_entree,fichier_sortie,-1,-1,-1,4,0,0,0,0,decroissantd,0,1,colonnes_tri);
		    nb_colonnes=4;
		}else if (!strcmp(type_donne,"-w")){
		    liste= entrer_donnees_liste(fichier_entree,fichier_sortie,0,1,2,4,1,1,0,0,decroissantd,0,0,NULL);
		    nb_colonnes=4;
		}else if (!strcmp(type_donne,"-h")){
		    liste= entrer_donnees_liste(fichier_entree,fichier_sortie,2,2,-1,3,0,0,0,0,decroissantd,0,0,NULL);
		    nb_colonnes=3;
		}else if (!strcmp(type_donne,"-m")){
		    liste=entrer_donnees_liste(fichier_entree,fichier_sortie,0,1,-1,4,0,0,0,1,decroissantd,0,0,NULL);
		    liste=triInsertionMaxDecroissant(liste);
		    nb_colonnes=4;
		}
		r=ecrire_liste_in_file(fichier_sortie,liste,type_donne,nb_colonnes);
		if (r==1){
            return 3;
		}
	}
	fclose(fichier_entree);
	fclose(fichier_sortie);
	return 0;
}
