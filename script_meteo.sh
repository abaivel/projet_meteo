#!/bin/bash
if [ $# -lt 2 ]; then
	echo "Pas assez d'arguments"
else
	nom_executable_c="tri_meteo"
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
		#echo $arg
		if [ $fichier_present -eq 1 ]; then
			nom_fichier=$arg
			if [ -f $arg ]; then
				fichier_present=2
			fi
	 	elif [ $arg == "-f" ]; then
	 		fichier_present=1
	 	elif [ $arg == "-t1" ] || [ $arg == "-t2" ] || [ $arg == "-t3" ] || [ $arg == "-p1" ] || [ $arg == "-p2" ] || [ $arg == "-p3" ] || [ $arg == "-w" ] || [ $arg == "-h" ] || [ $arg == "-m" ]; then
	 		type_present=$type_present+1
	 		types=$types$arg" "
	 	elif [ $arg == "-F" ] || [ $arg == "-G" ] || [ $arg == "-S" ] || [ $arg == "-A" ] || [ $arg == "-O" ] || [ $arg == "-Q" ]; then
			lieu=$arg
			lieu_present=$lieu_present+1
		elif [ $arg == "--tab" ] || [ $arg == "--abr" ] || [ $arg == "--avl" ]; then
			type_tri_present=$type_tri_present+1
			type_tri=$arg
		elif [ $arg == "-d" ]; then
			if [ $date_present -ne 0 ]; then
				erreur=1
			else
				date_present=1
			fi
		elif [ $date_present -eq 1 ]; then
			date_present=2
			date_min=$arg
		elif [ $date_present -eq 2 ]; then
			date_present=3
			date_max=$arg
		else
			echo "Parametre non existant"
			erreur=1
		fi
			
	 	
	done
	echo $date_min
	echo $date_max
	if (( $fichier_present == 0 )); then
		erreur=1
		echo "Fichier non renseigne"
	elif (( $fichier_present == 1 )); then
		erreur=1
		echo "$nom_fichier n'est pas un fichier"
	fi
	if (( $type_present == 0 )); then
		erreur=1
		echo "Pas de type de donnees renseigne"
	fi
	if (( $lieu_present == 2 )); then
		erreur=1
		echo "Trop de lieux renseignes - 1 maximum"
	fi
	if (( $type_tri_present == 2 )); then
		erreur=1
		echo "Trop de types de tri renseignes - 1 maximum"
	fi
	if (( date_present == 1 ));then
		erreur=1
		echo "Argument -d utilisé mais pas de dates renseignées"
	fi
	if (( date_present == 2 ));then
		erreur=1
		echo "Argument -d utilisé mais qu'une seule date renseignée"
	fi
	if (( $erreur == 0 )); then
		#if [ $(ls | grep -x $nom_executable_c | wc -c) = 0 ]; then
		#	echo $(make)
		#fi
		#parametres corrects
		if (( $lieu_present == 1 )) && (( $date_present == 3 )); then
			echo $(echo "" > data_filtre1.csv)
			#echo $(head -n 1 meteo_filtered_data_v1.csv >> data_filtre1.csv)
			contenu_fichier=`tail -n +2 $nom_fichier`
			for ligne in $contenu_fichier; do
				coord=$(echo ligne | cut -d ';' -f10)
				coord1=$(echo coord | cut -d ',' -f1)
				coord2=$(echo coord | cut -d ',' -f2)
				date=$(echo ligne | cut -d ';' -f2 | cut -d 'T' -f1)
				if [ $lieu = "-F" ] && (( $(echo "$coord1 >= 40" |bc -l) )) && (( $(echo "$coord1 <= 55" |bc -l) )) && (( $(echo "$coord2 >= -10" |bc -l) )) && (( $(echo "$coord2 <= 10" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $(echo $ligne >> data_filtre1.csv)
					fi
				elif [ $lieu = "-G" ] && (( $(echo "$coord1 >= 2" |bc -l) )) && (( $(echo "$coord1 <= 6" |bc -l) )) && (( $(echo "$coord2 >= -55" |bc -l) )) && (( $(echo "$coord2 <= -51" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $(echo $ligne >> data_filtre1.csv)
					fi
				elif [ $lieu = "-S" ] && (( $(echo "$coord1 >= 46" |bc -l) )) && (( $(echo "$coord1 <= 48" |bc -l) )) && (( $(echo "$coord2 >= -57" |bc -l) )) && (( $(echo "$coord2 <= -56" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $(echo $ligne >> data_filtre1.csv)
					fi
				elif [ $lieu = "-A" ] && (( $(echo "$coord1 >= 11" |bc -l) )) && (( $(echo "$coord1 <= 19" |bc -l) )) && (( $(echo "$coord2 >= -64" |bc -l) )) && (( $(echo "$coord2 <= -60" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $(echo $ligne >> data_filtre1.csv)
					fi
				elif [ $lieu = "-O" ] && (( $(echo "$coord1 >= -50" |bc -l) )) && (( $(echo "$coord1 <= 0" |bc -l) )) && (( $(echo "$coord2 >= 30" |bc -l) )) && (( $(echo "$coord2 <= 80" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $(echo $ligne >> data_filtre1.csv)
					fi
				elif [ $lieu = "-Q" ] && (( $(echo "$coord1 >= -90" |bc -l) )) && (( $(echo "$coord1 <= -60" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $(echo $ligne >> data_filtre1.csv)
					fi
				fi
			done
			nom_fichier="data_filtre1.csv"
		elif (( $lieu_present == 1 )); then
			echo $(echo "" > data_filtre1.csv)
			#echo $(head -n 1 meteo_filtered_data_v1.csv >> data_filtre1.csv)
			contenu_fichier=`tail -n +2 $nom_fichier`
			for ligne in $contenu_fichier; do
				coord=$(echo $ligne | cut -d ';' -f10)
				coord1=$(echo $coord | cut -d ',' -f1)
				coord2=$(echo $coord | cut -d ',' -f2)
				echo $coord
				if [ $lieu = "-F" ] && (( $(echo "$coord1 >= 40" |bc -l) )) && (( $(echo "$coord1 <= 55" |bc -l) )) && (( $(echo "$coord2 >= -10" |bc -l) )) && (( $(echo "$coord2 <= 10" |bc -l) )); then
					echo $(echo $ligne >> data_filtre1.csv)
				elif [ $lieu = "-G" ] && (( $(echo "$coord1 >= 2" |bc -l) )) && (( $(echo "$coord1 <= 6" |bc -l) )) && (( $(echo "$coord2 >= -55" |bc -l) )) && (( $(echo "$coord2 <= -51" |bc -l) )); then
					echo $(echo $ligne >> data_filtre1.csv)
				elif [ $lieu = "-S" ] && (( $(echo "$coord1 >= 46" |bc -l) )) && (( $(echo "$coord1 <= 48" |bc -l) )) && (( $(echo "$coord2 >= -57" |bc -l) )) && (( $(echo "$coord2 <= -56" |bc -l) )); then
					echo $(echo $ligne >> data_filtre1.csv)
				elif [ $lieu = "-A" ] && (( $(echo "$coord1 >= 11" |bc -l) )) && (( $(echo "$coord1 <= 19" |bc -l) )) && (( $(echo "$coord2 >= -64" |bc -l) )) && (( $(echo "$coord2 <= -60" |bc -l) )); then
					echo $(echo $ligne >> data_filtre1.csv)
				elif [ $lieu = "-O" ] && (( $(echo "$coord1 >= -50" |bc -l) )) && (( $(echo "$coord1 <= 0" |bc -l) )) && (( $(echo "$coord2 >= 30" |bc -l) )) && (( $(echo "$coord2 <= 80" |bc -l) )); then
					echo $(echo $ligne >> data_filtre1.csv)
				elif [ $lieu = "-Q" ] && (( $(echo "$coord1 >= -90" |bc -l) )) && (( $(echo "$coord1 <= -60" |bc -l) )); then
					echo $(echo $ligne >> data_filtre1.csv)
				fi
			done
			nom_fichier="data_filtre1.csv"
		elif (( $date_present == 3 )); then
			echo $(echo "" > data_filtre1.csv)
			#echo $(head -n 1 meteo_filtered_data_v1.csv >> data_filtre1.csv)
			contenu_fichier=`tail -n +2 $nom_fichier`
			for ligne in $contenu_fichier; do
				date=$(echo $ligne | cut -d ';' -f2 | cut -d 'T' -f1)
				if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
					echo $(echo $ligne >> data_filtre1.csv)
				fi
			done
			nom_fichier="data_filtre1.csv"
		fi
		for t in $types; do
			echo $t
			num_colonne="1"
			arguments_en_plus=$type_tri
			colonne_de_tri=1
			if [ $t = "-t1" ]; then
				num_colonne="1,11,12,13"
			elif [ $t = "-t2" ]; then
				num_colonne="2,10,11,12,13"
				colonne_de_tri=2
			elif [ $t = "-t3" ]; then
				num_colonne="1,2,11,12,13"
			elif [ $t = "-p1" ]; then
				num_colonne="1,7,8"
			elif [ $t = "-p2" ]; then
				num_colonne="2,7,8"
				colonne_de_tri=2
			elif [ $t = "-p3" ]; then
				num_colonne="1,2,7,8"
			elif [ $t = "-w" ]; then
				num_colonne="1,4,5,10"
			elif [ $t = "-h" ]; then
				num_colonne="10,14"
				colonne_de_tri=14
				arguments_en_plus=$arguments_en_plus" -r"
			elif [ $t = "-m" ]; then
				num_colonne="6,10"
				colonne_de_tri=6
				arguments_en_plus=$arguments_en_plus" -r"
			fi
			echo $num_colonne
			echo $(cut -d ';' -f$num_colonne $nom_fichier > resultat.csv)
			#retour=$(./$nom_executable_c -f resultat.csv -o fichier_trie.csv$arguments_en_plus)
			
			#appel au programme en C
		done
	fi
			
fi


















