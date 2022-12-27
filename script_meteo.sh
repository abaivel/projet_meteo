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
	 	elif [[ $arg == "-t"? ]] || [[ $arg == "-p"? ]] || [ $arg == "-w" ] || [ $arg == "-h" ] || [ $arg == "-m" ]; then	
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
	echo "Vérification des paramètres terminée"
	if (( $erreur == 0 )); then
		#if [ $(ls | grep -x $nom_executable_c | wc -c) = 0 ]; then
		#	echo $(make)
		#fi
		#parametres corrects
		if (( $lieu_present == 1 )) && (( $date_present == 3 )); then
			echo "" > data_filtre1.csv
			#echo $(head -n 1 meteo_filtered_data_v1.csv >> data_filtre1.csv)
			contenu_fichier=`tail -n +2 $nom_fichier`
			for ligne in $contenu_fichier; do
				coord=$(echo ligne | cut -d ';' -f10)
				coord1=$(echo coord | cut -d ',' -f1)
				coord2=$(echo coord | cut -d ',' -f2)
				date=$(echo ligne | cut -d ';' -f2 | cut -d 'T' -f1)
				if [ $lieu = "-F" ] && (( $(echo "$coord1 >= 40" |bc -l) )) && (( $(echo "$coord1 <= 55" |bc -l) )) && (( $(echo "$coord2 >= -10" |bc -l) )) && (( $(echo "$coord2 <= 10" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $ligne >> data_filtre1.csv
					fi
				elif [ $lieu = "-G" ] && (( $(echo "$coord1 >= 2" |bc -l) )) && (( $(echo "$coord1 <= 6" |bc -l) )) && (( $(echo "$coord2 >= -55" |bc -l) )) && (( $(echo "$coord2 <= -51" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $ligne >> data_filtre1.csv
					fi
				elif [ $lieu = "-S" ] && (( $(echo "$coord1 >= 46" |bc -l) )) && (( $(echo "$coord1 <= 48" |bc -l) )) && (( $(echo "$coord2 >= -57" |bc -l) )) && (( $(echo "$coord2 <= -56" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $ligne >> data_filtre1.csv
					fi
				elif [ $lieu = "-A" ] && (( $(echo "$coord1 >= 11" |bc -l) )) && (( $(echo "$coord1 <= 19" |bc -l) )) && (( $(echo "$coord2 >= -64" |bc -l) )) && (( $(echo "$coord2 <= -60" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $ligne >> data_filtre1.csv
					fi
				elif [ $lieu = "-O" ] && (( $(echo "$coord1 >= -50" |bc -l) )) && (( $(echo "$coord1 <= 0" |bc -l) )) && (( $(echo "$coord2 >= 30" |bc -l) )) && (( $(echo "$coord2 <= 80" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $ligne >> data_filtre1.csv
					fi
				elif [ $lieu = "-Q" ] && (( $(echo "$coord1 >= -90" |bc -l) )) && (( $(echo "$coord1 <= -60" |bc -l) )); then
					if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
						echo $ligne >> data_filtre1.csv
					fi
				fi
			done
			nom_fichier="data_filtre1.csv"
		elif (( $lieu_present == 1 )); then
			echo "" > data_filtre1.csv
			#echo $(head -n 1 meteo_filtered_data_v1.csv >> data_filtre1.csv)
			contenu_fichier=`tail -n +2 $nom_fichier`
			for ligne in $contenu_fichier; do
				coord=$(echo $ligne | cut -d ';' -f10)
				coord1=$(echo $coord | cut -d ',' -f1)
				coord2=$(echo $coord | cut -d ',' -f2)
				if [ $lieu = "-F" ] && (( $(echo "$coord1 >= 40" |bc -l) )) && (( $(echo "$coord1 <= 55" |bc -l) )) && (( $(echo "$coord2 >= -10" |bc -l) )) && (( $(echo "$coord2 <= 10" |bc -l) )); then
					echo $ligne >> data_filtre1.csv
				elif [ $lieu = "-G" ] && (( $(echo "$coord1 >= 2" |bc -l) )) && (( $(echo "$coord1 <= 6" |bc -l) )) && (( $(echo "$coord2 >= -55" |bc -l) )) && (( $(echo "$coord2 <= -51" |bc -l) )); then
					echo $ligne >> data_filtre1.csv
				elif [ $lieu = "-S" ] && (( $(echo "$coord1 >= 46" |bc -l) )) && (( $(echo "$coord1 <= 48" |bc -l) )) && (( $(echo "$coord2 >= -57" |bc -l) )) && (( $(echo "$coord2 <= -56" |bc -l) )); then
					echo $ligne >> data_filtre1.csv
				elif [ $lieu = "-A" ] && (( $(echo "$coord1 >= 11" |bc -l) )) && (( $(echo "$coord1 <= 19" |bc -l) )) && (( $(echo "$coord2 >= -64" |bc -l) )) && (( $(echo "$coord2 <= -60" |bc -l) )); then
					echo $ligne >> data_filtre1.csv
				elif [ $lieu = "-O" ] && (( $(echo "$coord1 >= -50" |bc -l) )) && (( $(echo "$coord1 <= 0" |bc -l) )) && (( $(echo "$coord2 >= 30" |bc -l) )) && (( $(echo "$coord2 <= 80" |bc -l) )); then
					echo $ligne >> data_filtre1.csv
				elif [ $lieu = "-Q" ] && (( $(echo "$coord1 >= -90" |bc -l) )) && (( $(echo "$coord1 <= -60" |bc -l) )); then
					echo $ligne >> data_filtre1.csv
				fi
			done
			nom_fichier="data_filtre1.csv"
		elif (( $date_present == 3 )); then
			echo "" > data_filtre1.csv
			#echo $(head -n 1 meteo_filtered_data_v1.csv >> data_filtre1.csv)
			contenu_fichier=`tail -n +2 $nom_fichier`
			for ligne in $contenu_fichier; do
				date=$(echo $ligne | cut -d ';' -f2 | cut -d 'T' -f1)
				if [ $(date -d $date +"%Y%m%d") -ge $(date -d $date_min +"%Y%m%d") ] && [ $(date -d $date +"%Y%m%d") -le $(date -d $date_max +"%Y%m%d") ]; then
					echo $ligne >> data_filtre1.csv
				fi
			done
			nom_fichier="data_filtre1.csv"
		fi
		echo "Vérification date et lieu terminée"
		for t in $types; do
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
			#echo $num_colonne
			cut -d ';' -f$num_colonne $nom_fichier | tail -n +2 > resultat.csv
			echo "filtrage fini"
			#retour=$(./$nom_executable_c -f resultat.csv -o fichier_trie.csv$arguments_en_plus)
			sort -k${colonne_de_tri}n resultat.csv >> fichier_trie.csv
			echo "tri fini"
			#appel au programme en C
			if [ $t = "-t1" ] || [ $t = "-p1" ]; then
				donnees_triees=`cat fichier_trie.csv`
				#echo $donnees_triees
				num_station=""
				somme=0
				nb_total=0
				min=""
				max=""
				i=0
				for ligne in $donnees_triees; do
					if [ -z "$num_station" ]; then
						num_station=$(echo $ligne | cut -d ';' -f1)
					elif [ $num_station != $(echo $ligne | cut -d ';' -f1) ]; then
						moyenne=$(echo "${somme} / ${nb_total}" | bc -l)
						echo $num_station $moyenne $min $max >> donnees_rangees.txt
						num_station=$(echo $ligne | cut -d ';' -f1)
						somme=0
						nb_total=0
						min=""
						max=""
					fi
					nb_total=$(( $nb_total + 1 ))
					valeur=$(echo $ligne | cut -d ';' -f2)
					if [ -z "$valeur" ]; then
						valeur=0
					fi
					somme=$(echo "${somme} + ${valeur}" | bc)
					if [ -n "$min" ]; then
						if (( $(echo "${valeur} < ${min}" | bc -l) )); then
							min=$valeur
						fi
						if (( $(echo "${valeur}> ${max}" | bc -l) )); then
							max=$valeur
						fi
					else
						min=$valeur
						max=$valeur
					fi
					echo 
					i=$(( $i + 1 ))
					echo "i=$i"
				done
				moyenne=$(echo "${somme} / ${nb_total}" | bc -l)
				echo $num_station $moyenne $min $max >> donnees_rangees.txt
				echo "ecriture des fichiers pour gnuplot fini"
				#echo $(plot 'donnees_rangees.txt' with yerrorlines >> gnuplot_script)
				echo "set terminal png size 800,500 enhanced background rgb 'white'" > gnuplot_script
				echo "set style line 1 lt 1 lw 1.5 pt 3 linecolor rgb '#2b63ff'" >> gnuplot_script
				echo "set output 'curve.png'" >> gnuplot_script
				echo "plot 'donnees_rangees.txt' with yerrorlines" >> gnuplot_script
				gnuplot gnuplot_script
				echo "Création du graphique fini"
			fi
		done
	fi
			
fi
rm -f donnees_rangees.txt
rm -f fichier_trie.csv
rm -f resultat.csv
rm -f gnuplot_script
