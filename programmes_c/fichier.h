#define TAILLE_MAX_LIGNE 200
#define TAILLE_MAX_CASE 50

typedef struct box {
    char** tab;
    int nb_colonnes;
    double somme1;
	double somme2;
    int nb_times;
    double minimum;
    double maximum;
}Case;

typedef struct arbreAVL{
	Case elmt;
	struct arbreAVL* gauche;
	struct arbreAVL* droit;
	int equilibre;
}ArbreAVL;

typedef ArbreAVL* pArbreAVL;

typedef struct arbre{
	Case elmt;
	struct arbre* gauche;
	struct arbre* droit;
}Arbre;

typedef Arbre* pArbre;

typedef struct chainon {
    Case elmt;
    struct chainon* suivant;
}Chainon;

//fichier fonctions.c
Case creerCase(char** tab, int nb_colonnes, int colonne_moy1, int colonne_moy2);
Chainon* entrer_donnees_liste(FILE* fichier_entree, FILE* fichier_sortie, int colonne_tri, int colonne_moy1, int colonne_moy2, int nb_colonnes, int moy1, int moy2, int mini, int maxi, int decroissant, int date, int tri_multiple, int colonnes_tri_mutiple[3]);
Arbre* entrer_donnees_abr(FILE* fichier_entree, FILE* fichier_sortie, int colonne_tri, int colonne_moy1, int colonne_moy2, int nb_colonnes, int moy1, int moy2, int mini, int maxi, int date, int tri_multiple, int colonnes_tri_mutiple[3]);
ArbreAVL* entrer_donnees_avl(FILE* fichier_entree, FILE* fichier_sortie, int colonne_tri, int colonne_moy1, int colonne_moy2, int nb_colonnes, int moy1, int moy2, int mini, int maxi, int date, int tri_multiple, int colonnes_tri_mutiple[3]);
char** LigneVersTab(char* ligne, int nb_colonnes);
void libererTab2(char** tab, int t);
void libererCase(Case c, int nb_colonnes);

//fichier fonctions_liste.c
Chainon* creationChainon(Case a);
Chainon* insertionFin(Chainon* pliste, Chainon* c);
Chainon* triInsertionMaxDecroissant(Chainon* liste);
Chainon* ajout_croissant3(Chainon* pliste, char** tab, int nb_colonnes, int colonne_tri1, int colonne_tri2, int colonne_tri3);
Chainon* ajout_croissant(Chainon* pliste, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy1, int colonne_moy2, int moyenne1, int moyenne2, int minimum, int maximum);
Chainon* ajout_decroissant(Chainon* pliste, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy1, int colonne_moy2, int moyenne1, int moyenne2, int minimum, int maximum);
Chainon* ajout_croissant_date(Chainon* pliste, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy, int moyenne);
int ecrire_liste_in_file(FILE* fichier_sortie, Chainon* pliste, char type[4], int nb_colonnes);

//fichier fonctions_abr.c
pArbre creerArbre(Case r);
pArbre insertionABR_date(pArbre a, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy, int moyenne);
pArbre insertionABR(pArbre a, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy1, int colonne_moy2, int moyenne1, int moyenne2, int minimum, int maximum);
pArbre insertionABR3(pArbre a, char** tab, int nb_colonnes, int colonne_tri1, int colonne_tri2, int colonne_tri3);
pArbre insertionABR_avec_max(pArbre a, Case c);
void triABR(pArbre arbre, pArbre* nouv_arbre,int nb_colonnes);
int ecrire_abr_in_file_croissant(FILE* fichier_sortie, Arbre* arbre, char type[4], int* i, int nb_colonnes);
int ecrire_abr_in_file_decroissant(FILE* fichier_sortie, Arbre* arbre, char type[4], int nb_colonnes);
int ecrire_abr_in_file_p3t3(FILE* fichier_sortie, Arbre* arbre, char type[4], char heure[], char id[], int nb_colonnes);

//fichier fonctions_avl.c
pArbreAVL creerArbreAVL(Case r);
int max2(int a, int b);
int min2(int a, int b);
int min3(int a, int b, int c);
int max3(int a, int b, int c);
pArbreAVL rotationGauche(pArbreAVL a);
pArbreAVL rotationDroite(pArbreAVL a);
pArbreAVL doubleRotationGauche(pArbreAVL a);
pArbreAVL doubleRotationDroite(pArbreAVL a);
pArbreAVL equilibrerAVL(pArbreAVL a);
pArbreAVL insertionAVL(pArbreAVL a,int* h, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy1, int colonne_moy2, int moyenne1, int moyenne2, int minimum, int maximum);
pArbreAVL insertionAVL_date(pArbreAVL a, int* h, char** tab, int nb_colonnes, int colonne_tri, int colonne_moy, int moyenne);
pArbreAVL insertionAVL3(pArbreAVL a, int* h, char** tab, int nb_colonnes, int colonne_tri1, int colonne_tri2, int colonne_tri3);
pArbreAVL insertionAVL_avec_max(pArbreAVL a, int* h, Case c);
void triAVL(pArbreAVL arbre, pArbreAVL* nouv_arbre,int nb_colonnes);
int ecrire_avl_in_file_croissant(FILE* fichier_sortie, ArbreAVL* arbre, char type[4], int* i, int nb_colonnes);
int ecrire_avl_in_file_decroissant(FILE* fichier_sortie, ArbreAVL* arbre, char type[4], int nb_colonnes);
int ecrire_avl_in_file_p3t3(FILE* fichier_sortie, ArbreAVL* arbre, char type[4], char heure[], char id[], int nb_colonnes);

