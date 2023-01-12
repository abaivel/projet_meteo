typedef struct case {
    char** tab;
    double somme;
    int nb_times;
    double minimum;
    double maximum;
}Case;

typedef struct arbreAVL{
	Case elmt;
	struct arbre* gauche;
	struct arbre* droit;
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


