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
		if [ $fichier_present -eq 1 ]; then
			nom_fichier=$arg
			if [ -f $arg ]; then
				fichier_present=2
			fi
	 	elif [ $arg = "-f" ]; then
	 		fichier_present=1
	 	elif [ $arg = "-t?" ] || [ $arg = "-p?" ] || [ $arg = "-w" ] || [ $arg = "-h" ] || [ $arg = "-m" ]; then
	 		type_present=$type_present+1
	 		types=$types+$arg+" "
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
	if [ $fichier_present -eq 0 ]; then
		erreur=1
		echo "Fichier non renseigne"
	elif [ &fichier_present -eq 1 ]; then
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
			colonne_type=0
			if [ $arg = "-t?" ]; then
			elif [ $arg = "-p?" ]; then
			elif [ $arg = "-w" ]; then 
			elif [ $arg = "-h" ]; then 
			elif [ $arg = "-m" ]
fi


















