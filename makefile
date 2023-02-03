all: tri_meteo

main.o: programmes_c/main.c programmes_c/fichier.h
	gcc -c $< -o $@

functions.o: programmes_c/functions.c programmes_c/fichier.h
	gcc -c $< -o $@

functions_liste.o: programmes_c/functions_liste.c programmes_c/fichier.h
	gcc -c $< -o $@

functions_abr.o: programmes_c/functions_abr.c programmes_c/fichier.h
	gcc -c $< -o $@

functions_avl.o: programmes_c/functions_avl.c programmes_c/fichier.h
	gcc -c $< -o $@

tri_meteo: main.o functions.o functions_liste.o functions_abr.o functions_avl.o
	gcc $^ -o $@ -lm

clean:
	rm -f *.o
