typedef struct arbreAVL{
	int elmt;
	struct arbre* gauche;
	struct arbre* droit;
	int equilibre;
}ArbreAVL;

typedef ArbreAVL* pArbreAVL;

typedef struct arbre{
	int elmt;
	struct arbre* gauche;
	struct arbre* droit;
}Arbre;

typedef Arbre* pArbre;

typedef struct chainon {
    int elmt;
    struct chainon* suivant;
}Chainon;
