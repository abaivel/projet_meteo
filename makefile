all: tri_meteo

main.o: programmes_c/main.c programmes_c/fichier.h
	gcc -c $< -o $@

fonctions.o: programmes_c/fonctions.c programmes_c/fichier.h
	gcc -c $< -o $@

fonctions_liste.o: programmes_c/fonctions_liste.c programmes_c/fichier.h
	gcc -c $< -o $@

fonctions_abr.o: programmes_c/fonctions_abr.c programmes_c/fichier.h
	gcc -c $< -o $@

fonctions_avl.o: programmes_c/fonctions_avl.c programmes_c/fichier.h
	gcc -c $< -o $@

tri_meteo: main.o fonctions.o fonctions_liste.o fonctions_abr.o fonctions_avl.o
	gcc $^ -o $@ -lm

clean:
	rm -f *.o
