#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fichier.h"

Chainon* creationChainon(Case a){
    Chainon* c = malloc(sizeof(Chainon));
    if (c==NULL){
        exit(4);
    }
    (*c).elmt = a;
    (*c).suivant = NULL;
    return c;
}

Chainon* insertionFin(Chainon* pliste, Chainon* c){
    Chainon* liste_originale=pliste;
    Chainon* l = pliste;
    if (pliste==NULL){
        return c;
    }
    while (pliste->suivant!=NULL){
        pliste=pliste->suivant;
    }
    pliste->suivant = c;
    return liste_originale;
}

Chainon* triInsertionMaxDecroissant(Chainon* liste){
    Chainon* nouv_liste=NULL;
    while (liste!=NULL){
        Chainon* chainon_max=liste;
        Chainon* chainon_avant_max;
        Chainon* pliste=liste;
        while (pliste->suivant!=NULL){
            if ((chainon_max->elmt).maximum<(pliste->suivant->elmt).maximum){
                chainon_max=pliste->suivant;
                chainon_avant_max=pliste;
            }
            pliste=pliste->suivant;
        }
        if (chainon_max==liste){
        	liste=liste->suivant;
        }else{
        	chainon_avant_max->suivant=chainon_max->suivant;
        }
        chainon_max->suivant=NULL;
        nouv_liste=insertionFin(nouv_liste,chainon_max);
    }
    return nouv_liste;
}

Chainon* ajout_croissant3(Chainon* pliste, char** tab, int nb_colonnes, int colonne_tri1, int colonne_tri2, int colonne_tri3){
    /*  pliste : la liste chainee
        tab : le tabelau contenant les éléments de la ligne à placer dans la liste
        nb_colonnes : le nombre d"élements dans tab
        colonne_tri1,2 et 3 sont les colonnes par lequel on trie

        Retourne la nouvelle liste
    */
	if (pliste==NULL){
		return creationChainon(creerCase(tab,nb_colonnes,-1, -1));
	}
	Chainon* c = pliste;
	Chainon* avant=NULL;
	while (c!=NULL && (strcmp((c->elmt).tab[colonne_tri1],tab[colonne_tri1])<0 ||
	(strcmp((c->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((c->elmt).tab[colonne_tri2],tab[colonne_tri2])<0) ||
	(strcmp((c->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((c->elmt).tab[colonne_tri2],tab[colonne_tri2])==0 &&
	strcmp((c->elmt).tab[colonne_tri3],tab[colonne_tri3])<0))){
        if (c->suivant!=NULL){
			if (strcmp((c->suivant->elmt).tab[colonne_tri1],tab[colonne_tri1])>0 ||
            (strcmp((c->suivant->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((c->suivant->elmt).tab[colonne_tri2],tab[colonne_tri2])>0) ||
            (strcmp((c->suivant->elmt).tab[colonne_tri1],tab[colonne_tri1])==0 && strcmp((c->suivant->elmt).tab[colonne_tri2],tab[colonne_tri2])==0 &&
            strcmp((c->suivant->elmt).tab[colonne_tri3],tab[colonne_tri3])>0)){
				avant=c;
			}
		}else{
			avant=c;
		}
		c=c->suivant;
	}
    Chainon* nouv_chainon = creationChainon(creerCase(tab,nb_colonnes,-1, -1));
    nouv_chainon->suivant=c;
    if (avant!=NULL){
        avant->suivant=nouv_chainon;
    }else{
        pliste=nouv_chainon;
    }
	return pliste;
}

Chainon* ajout_croissant(Chainon* pliste, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy1, int colonne_moy2, int moyenne1, int moyenne2, int minimum, int maximum){
	/*  pliste : la liste chainée
        tab : le tabelau contenant les éléments de la ligne à placer dans la liste
        nb_colonnes : le nombre d"élements dans tab
        colonne_tri : le numéro de la colonne à trier (débute à 0)
        colonne_moy1 : le numéro de la colonne avec laquelle la moyenne (et le minimum et maximum si demandé) sera calculé (débute à 0)
        colonne_moy2 : pareil, elle sert uniquement lorsqu'il y a deux moyennes à calculer (pour le graphique avec les vecteurs)
        moyenne1 : vaut 1 si il y a au moins une moyenne à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon
        moyenne2 : vaut 1 si il y a une deuxième moyenne à calculer (avec la colonne n°colonne_moy2 évidemment), 0 sinon
        minimum : vaut 1 si il y a un minimum à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon
        maximum : vaut 1 si il y a un maximum à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon

        Retourne la nouvelle liste
    */
	if (pliste==NULL){
		return creationChainon(creerCase(tab,nb_colonnes,colonne_moy1, colonne_moy2));
	}
	Chainon* c = pliste;
	Chainon* avant=NULL;
	while (c!=NULL && strtod((c->elmt).tab[colonne_tri],NULL)<strtod(tab[colonne_tri],NULL)){
		if (c->suivant!=NULL){
			if (strtod((c->suivant->elmt).tab[colonne_tri],NULL)>strtod(tab[colonne_tri],NULL)){
				avant=c;
			}
		}else{
			avant=c;
		}
		c=c->suivant;
	}
	if (strcmp(tab[colonne_moy1],"\n")!=0){
        if (c!=NULL){
            if (strtod((c->elmt).tab[colonne_tri],NULL)==strtod(tab[colonne_tri],NULL) && colonne_moy1>-1){
                if (colonne_moy2==-1){
                    if (moyenne1==1){
                        (c->elmt).somme1=(c->elmt).somme1+strtod(tab[colonne_moy1],NULL);
                        (c->elmt).nb_times=(c->elmt).nb_times+1;
                    }if (minimum==1){
                        double nb=strtod(tab[colonne_moy1],NULL);
                        if (nb<(c->elmt).minimum){
                            (c->elmt).minimum=nb;
                        }
                    }if (maximum==1){
                        double nb=strtod(tab[colonne_moy1],NULL);
                        if (nb>(c->elmt).maximum){
                            (c->elmt).maximum=nb;
                        }
                    }
                }else{
                    (c->elmt).somme1=(c->elmt).somme1+(sin(strtod(tab[colonne_moy1],NULL)*(M_PI/180.0))*strtod(tab[colonne_moy2],NULL));
                    (c->elmt).nb_times=(c->elmt).nb_times+1;
                    (c->elmt).somme2=(c->elmt).somme1+(cos(strtod(tab[colonne_moy1],NULL)*(M_PI/180.0))*strtod(tab[colonne_moy2],NULL));
                }
                libererTab2(tab,nb_colonnes);
            }else{
                Chainon* nouv_chainon = creationChainon(creerCase(tab,nb_colonnes,colonne_moy1, colonne_moy2));
                nouv_chainon->suivant=c;
                if (avant!=NULL){
                    avant->suivant=nouv_chainon;
                }else{
                    pliste=nouv_chainon;
                }
            }
        }else{
            Chainon* nouv_chainon = creationChainon(creerCase(tab,nb_colonnes,colonne_moy1, colonne_moy2));
            nouv_chainon->suivant=c;
            if (avant!=NULL){
                avant->suivant=nouv_chainon;
            }else{
                pliste=nouv_chainon;
            }
        }
    }
	return pliste;
}

Chainon* ajout_decroissant(Chainon* pliste, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy1, int colonne_moy2, int moyenne1, int moyenne2, int minimum, int maximum){
	/*  pliste : la liste chainée
        tab : le tabelau contenant les éléments de la ligne à placer dans la liste
        nb_colonnes : le nombre d"élements dans tab
        colonne_tri : le numéro de la colonne à trier (débute à 0)
        colonne_moy1 : le numéro de la colonne avec laquelle la moyenne (et le minimum et maximum si demandé) sera calculé (débute à 0)
        colonne_moy2 : pareil, elle sert uniquement lorsqu'il y a deux moyennes à calculer (pour le graphique avec les vecteurs)
        moyenne1 : vaut 1 si il y a au moins une moyenne à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon
        moyenne2 : vaut 1 si il y a une deuxième moyenne à calculer (avec la colonne n°colonne_moy2 évidemment), 0 sinon
        minimum : vaut 1 si il y a un minimum à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon
        maximum : vaut 1 si il y a un maximum à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon

        Retourne la nouvelle liste
    */
	if (pliste==NULL){
		return creationChainon(creerCase(tab,nb_colonnes,colonne_moy1, colonne_moy2));
	}
	Chainon* c = pliste;
	Chainon* avant=NULL;
	while (c!=NULL && strtod((c->elmt).tab[colonne_tri],NULL)>strtod(tab[colonne_tri],NULL)){
		if (c->suivant!=NULL){
			if (strtod((c->suivant->elmt).tab[colonne_tri],NULL)<strtod(tab[colonne_tri],NULL)){
				avant=c;
			}
		}else{
			avant=c;
		}
		c=c->suivant;
	}
	if (strcmp(tab[colonne_moy1],"\n")!=0){
        if (c!=NULL){
            if (strtod((c->elmt).tab[colonne_tri],NULL)==strtod(tab[colonne_tri],NULL) && colonne_moy1>-1){
                if (moyenne1==1){
                    (c->elmt).somme1=(c->elmt).somme1+strtod(tab[colonne_moy1],NULL);
                    (c->elmt).nb_times=(c->elmt).nb_times+1;
                }if (minimum==1){
                    double nb=strtod(tab[colonne_moy1],NULL);
                    if (nb<(c->elmt).minimum){
                        (c->elmt).minimum=nb;
                    }
                }if (maximum==1){
                    double nb=strtod(tab[colonne_moy1],NULL);
                    if (nb>(c->elmt).maximum){
                        (c->elmt).maximum=nb;
                    }
                }
                if (colonne_moy2>-1){
                    if (strcmp(tab[colonne_moy2],"\n")!=0 && moyenne2==1){
                        (c->elmt).somme2=(c->elmt).somme2+strtod(tab[colonne_moy2],NULL);
                    }
                }
                libererTab2(tab,nb_colonnes);
            }else{
                Chainon* nouv_chainon = creationChainon(creerCase(tab,nb_colonnes,colonne_moy1, colonne_moy2));
                nouv_chainon->suivant=c;
                if (avant!=NULL){
                    avant->suivant=nouv_chainon;
                }else{
                    pliste=nouv_chainon;
                }
            }
        }else{
            Chainon* nouv_chainon = creationChainon(creerCase(tab,nb_colonnes,colonne_moy1, colonne_moy2));
            nouv_chainon->suivant=c;
            if (avant!=NULL){
                avant->suivant=nouv_chainon;
            }else{
                pliste=nouv_chainon;
            }
        }
    }
	return pliste;
}

Chainon* ajout_croissant_date(Chainon* pliste, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy, int moyenne){
    /*  pliste : la liste chainée
        tab : le tabelau contenant les éléments de la ligne à placer dans la liste
        nb_colonnes : le nombre d"élements dans tab
        colonne_tri : le numéro de la colonne à trier (débute à 0)
        colonne_moy : le numéro de la colonne avec laquelle la moyenne (et le minimum et maximum si demandé) sera calculé (débute à 0)
        moyenne : vaut 1 si il y a au moins une moyenne à calculer (avec la colonne n°colonne_moy1 évidemment), 0 sinon

        Retourne la nouvelle liste
    */
	if (pliste==NULL){
		return creationChainon(creerCase(tab,nb_colonnes,colonne_moy,-1));
	}
	Chainon* c = pliste;
	Chainon* avant=NULL;
	while (c!=NULL && strcmp((c->elmt).tab[colonne_tri],tab[colonne_tri])<0){
		if (c->suivant!=NULL){
			if (strcmp((c->suivant->elmt).tab[colonne_tri],tab[colonne_tri])>0){
				avant=c;
			}
		}else{
			avant=c;
		}
		c=c->suivant;
	}
	if (strcmp(tab[colonne_moy],"\n")!=0){
        if (c!=NULL){
            if (strcmp((c->elmt).tab[colonne_tri],tab[colonne_tri])==0 && colonne_moy>-1){
                if (moyenne==1){
                    (c->elmt).somme1=(c->elmt).somme1+strtod(tab[colonne_moy],NULL);
                    (c->elmt).nb_times=(c->elmt).nb_times+1;
                }
                libererTab2(tab,nb_colonnes);
            }else{
                Chainon* nouv_chainon = creationChainon(creerCase(tab,nb_colonnes,colonne_moy, -1));
                nouv_chainon->suivant=c;
                if (avant!=NULL){
                    avant->suivant=nouv_chainon;
                }else{
                    pliste=nouv_chainon;
                }
            }
        }else{
            Chainon* nouv_chainon = creationChainon(creerCase(tab,nb_colonnes,colonne_moy, -1));
            nouv_chainon->suivant=c;
            if (avant!=NULL){
                avant->suivant=nouv_chainon;
            }else{
                pliste=nouv_chainon;
            }
        }
    }
	return pliste;
}

int ecrire_liste_in_file(FILE* fichier_sortie, Chainon* pliste, char type[4], int nb_colonnes){
    int i=0;
    int r;
    char heure[TAILLE_MAX_CASE]="";
    char id[TAILLE_MAX_CASE]="";
    char * couleur[24]={"84AD41","6600AD","05A1AD","EC0700","FFD32E","F4116D","241279","81FF23",
                        "11A234","8AF4FF","075400","000000","FF3D9A","A60082","5E35FF","FF777B",
                        "00FF9C","627600","FF00FC","6D071A","9683EC","9B6337","665A53","924A53"};
    while (pliste!=NULL){
        if (!strcmp(type,"-w")){
            double x1=strtod((pliste->elmt).tab[4],NULL);
            double y1=strtod((pliste->elmt).tab[3],NULL);
            r=fprintf(fichier_sortie, "%lf %lf %lf %lf\n", x1,y1,(pliste->elmt).somme1/(pliste->elmt).nb_times,(pliste->elmt).somme2/(pliste->elmt).nb_times);
        }else if (!strcmp(type,"-t1") || !strcmp(type,"-p1")){
            r=fprintf(fichier_sortie, "%d %s %lf %lf %lf\n", i, (pliste->elmt).tab[0], (pliste->elmt).somme1/(pliste->elmt).nb_times, (pliste->elmt).minimum, (pliste->elmt).maximum);
        }else if (!strcmp(type,"-t2") || !strcmp(type,"-p2")){
            r=fprintf(fichier_sortie, "%s %lf\n",  (pliste->elmt).tab[0], (pliste->elmt).somme1/(pliste->elmt).nb_times);
        }else if (!strcmp(type,"-t3") || !strcmp(type,"-p3")){
            if (strlen(heure)==0){
                strcpy(heure,(pliste->elmt).tab[2]);
                strcpy(id,(pliste->elmt).tab[0]);
            }else{
                if (strcmp(heure,(pliste->elmt).tab[2])){
                    strcpy(heure,(pliste->elmt).tab[2]);
                    strcpy(id,(pliste->elmt).tab[0]);
                    r=fprintf(fichier_sortie, "\n\n");
                }else if (strcmp(id,(pliste->elmt).tab[0])){
                    strcpy(id,(pliste->elmt).tab[0]);
                    r=fprintf(fichier_sortie, "\n\n");
                }
            }
            char* date=(pliste->elmt).tab[1];
            r=fprintf(fichier_sortie, "%s %lf %s\n",date,strtod((pliste->elmt).tab[3],NULL),couleur[atoi(heure)]);
        }else if (!strcmp(type,"-h")){
            r=fprintf(fichier_sortie, "%s %s %s\n",(pliste->elmt).tab[1],(pliste->elmt).tab[0],(pliste->elmt).tab[2]);
        }else if (!strcmp(type,"-m")){
            r=fprintf(fichier_sortie, "%s %s %lf\n\n",(pliste->elmt).tab[3],(pliste->elmt).tab[2],(pliste->elmt).maximum);
        }
        if (r==EOF){
            return 1;
        }
        Chainon* ancien_pliste=pliste;
        pliste=pliste->suivant;
        i++;
        libererCase(ancien_pliste->elmt,nb_colonnes);
        free(ancien_pliste);
    }
    return 0;
}

