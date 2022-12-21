#!/bin/bash
if [ $# -lt 2 ]; then
	echo "Pas assez d'arguments"
else
	fichier_present=0
	nom_fichier=""
	type_present=0
	lieu_present=0
	type_tri_present=0
	type_tri=""
	lieu=""
	date_present=0
	date_min=""
	date_max=""
	erreur=0
	types=""
	for arg in $*; do
		echo $arg
		if [ $fichier_present -eq 1 ]; then
			nom_fichier=$arg
			if [ -f $arg ]; then
				fichier_present=2
			fi
	 	elif [ $arg = "-f" ]; then
	 		fichier_present=1
	 	elif [ $arg == "-t2" ] || [ $arg == -p? ] || [ $arg = "-w" ] || [ $arg = "-h" ] || [ $arg = "-m" ]; then
	 		type_present=$type_present+1
	 		types=$types$arg" "
	 	elif [ $arg = "-F" ] || [ $arg = "-G" ] || [ $arg = "-S" ] || [ $arg = "-A" ] || [ $arg = "-O" ] || [ $arg = "-Q" ]; then
			lieu=$arg
			lieu_present=$lieu_present+1
		elif [ $arg = "--tab" ] || [ $arg = "--abr" ] || [ $arg = "--avl" ]; then
			type_tri_present=$type_tri_present+1
			type_tri=$arg
		elif [ $arg = "-d" ]; then
			if [ $date_present -ne 0 ]; then
				erreur=1
			else
				date_present=1
			fi
		elif [ $date_present -eq 1 ]; then
			date_present=2
		else
			echo "Parametre non existant"
			erreur=1
		fi
			
	 	
	done
	echo $types
	if [ $fichier_present -eq 0 ]; then
		erreur=1
		echo "Fichier non renseigne"
	elif [ $fichier_present -eq 1 ]; then
		erreur=1
		echo "$nom_fichier n'est pas un fichier"
	fi
	if [ $type_present -eq 0 ]; then
		erreur=1
		echo "Pas de type de donnees renseigne"
	fi
	if [ $lieu_present -ge 2 ]; then
		erreur=1
		echo "Trop de lieux renseignes - 1 maximum"
	fi
	if [ $type_tri_present -ge 2 ]; then
		erreur=1
		echo "Trop de types de tri renseignes - 1 maximum"
	fi
	if [ $erreur -eq 0 ]; then
		#parametres corrects
		for t in $types; do
			echo $t
			num_colonne="1"
			croissant=1
			if [ $t = "-t1" ]; then
				num_colonne="1,11,12,13"
			elif [ $t = "-t2" ]; then
				num_colonne="2,11,12,13"
			elif [ $t = "-t3" ]; then
				num_colonne="1,2,11,12,13"
			elif [ $t = "-p1" ]; then
				num_colonne="1,7,8"
			elif [ $t = "-p2" ]; then
				num_colonne="2,7,8"
			elif [ $t = "-p3" ]; then
				num_colonne="1,2,7,8"
			elif [ $t = "-w" ]; then
				num_colonne="1,4,5"
			elif [ $t = "-h" ]; then
				num_colonne="14"
				croissant=0
			elif [ $t = "-m" ]; then
				num_colonne="6"
				croissant=0
			fi
			echo $num_colonne
			echo $(cut -d ';' -f$num_colonne $nom_fichier) >> resultat.csv
		done
	fi
			
fi


















