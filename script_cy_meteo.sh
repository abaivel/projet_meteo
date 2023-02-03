#!/bin/bash
debut=$(date +%s)
if [ $# -eq 1 ] && [ $1 == "--help" ]; then
	cat documentation_help
elif [ $# -lt 2 ]; then
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
	date_invalide=0
	for arg in $*; do
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
			date_an=$(echo $date_min | cut -d '-' -f1)
			date_mois=$(echo $date_min | cut -d '-' -f2)
			date_jour=$(echo $date_min | cut -d '-' -f3)
			if [ $date_jour -eq 0 ] || [ $date_mois -eq 0 ] || [ $date_mois -eq 0 ];then
				date_invalide=1
			elif [ $date_mois -eq 2 ]; then
				if [ $(( $date_an % 4 )) -eq 0 ] && [ $(( $date_an % 100 )) -ne 0 ]; then
					if [ $date_jour -gt 29 ];then
						date_invalide=1
					fi
				elif [ $(( $date_an % 400 )) -eq 0 ];then
					if [ $date_jour -gt 29 ];then
						date_invalide=1
					fi
				elif [ $date_jour -gt 28 ];then
					date_invalide=1
				fi
			elif [ $date_mois -eq 1 ] || [ $date_mois -eq 3 ] || [ $date_mois -eq 5 ] || [ $date_mois -eq 7 ] || [ $date_mois -eq 8 ] || [ $date_mois -eq 10 ] || [ $date_mois -eq 12 ] ;then
				if [ $date_jour -gt 31 ];then
					date_invalide=1
				fi
			elif [ $date_mois -eq 4 ] || [ $date_mois -eq 6 ] || [ $date_mois -eq 9 ] || [ $date_mois -eq 11 ] ;then
				if [ $date_jour -gt 30 ];then
					date_invalide=1
				fi
			fi
		elif [ $date_present -eq 2 ]; then
			date_present=3
			date_max=$arg
			date_an=$(echo $date_max | cut -d '-' -f1)
			date_mois=$(echo $date_max | cut -d '-' -f2)
			date_jour=$(echo $date_max | cut -d '-' -f3)
			if [ $date_jour -eq 0 ] || [ $date_mois -eq 0 ] || [ $date_mois -eq 0 ];then
				date_invalide=1
			elif [ $date_mois -eq 2 ]; then
				if [ $(( $date_an % 4 )) -eq 0 ] && [ $(( $date_an % 100 )) -ne 0 ]; then
					if [ $date_jour -gt 29 ];then
						date_invalide=1
					fi
				elif [ $(( $date_an % 400 )) -eq 0 ];then
					if [ $date_jour -gt 29 ];then
						date_invalide=1
					fi
				elif [ $date_jour -gt 28 ];then
					date_invalide=1
				fi
			elif [ $date_mois -eq 1 ] || [ $date_mois -eq 3 ] || [ $date_mois -eq 5 ] || [ $date_mois -eq 7 ] || [ $date_mois -eq 8 ] || [ $date_mois -eq 10 ] || [ $date_mois -eq 12 ] ;then
				if [ $date_jour -gt 31 ];then
					date_invalide=1
				fi
			elif [ $date_mois -eq 4 ] || [ $date_mois -eq 6 ] || [ $date_mois -eq 9 ] || [ $date_mois -eq 11 ] ;then
				if [ $date_jour -gt 30 ];then
					date_invalide=1
				fi
			fi
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
	if (( $date_present == 1 ));then
		erreur=1
		echo "Argument -d utilisé mais pas de dates renseignées"
	fi
	if (( $date_present == 2 ));then
		erreur=1
		echo "Argument -d utilisé mais qu'une seule date renseignée"
	fi
	if (( $date_invalide == 1 ));then
		erreur=1
		echo "Date invalide"
	fi
	echo "Vérification des paramètres terminée"
	if (( $erreur == 0 )); then
		if [ $(ls | grep -x $nom_executable_c | wc -c) -eq 0 ]; then
			make -s
			make clean -s
		fi
		if [ $(ls | grep -x $nom_executable_c | wc -c) -gt 0 ]; then #compilation réussie
			echo "avant"
			contenu_fichier=`tail -n +2 $nom_fichier`
			date="2012-11-25"
			echo "avant"
			echo $contenu_fichier | tr ',:' ';' | tr ' ' '\n' > fichier_modifie.csv
			echo "apres"
			nom_fichier="fichier_modifie.csv"
			if (( $lieu_present == 1 )) && (( $date_present == 3 )); then
				if [ $lieu = "-F" ]; then
					awk -v date_min="${date_min}T23" -v date_max="${date_max}T23" 'BEGIN{FS=";"}; {if($13 >= 40 && $13 <= 55 && $14 >= -10 && $14 <= 10 && $2 >= date_min && $2 <= date_max) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-G" ]; then
					awk -v date_min="${date_min}T23" -v date_max="${date_max}T23" 'BEGIN{FS=";"}; {if($13 >= 2 && $13 <= 6 && $14 >= -55 && $14 <= -51 && $2 >= date_min && $2 <= date_max) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-S" ]; then
					awk -v date_min="${date_min}T23" -v date_max="${date_max}T23" 'BEGIN{FS=";"}; {if($13 >= 46 && $13 <= 48 && $14 >= -57 && $14 <= -56 && $2 >= date_min && $2 <= date_max) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-A" ]; then
					awk -v date_min="${date_min}T23" -v date_max="${date_max}T23" 'BEGIN{FS=";"}; {if($13 >= 11 && $13 <= 19 && $14 >= -64 && $14 <= -60 && $2 >= date_min && $2 <= date_max) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-O" ]; then
					awk -v date_min="${date_min}T23" -v date_max="${date_max}T23" 'BEGIN{FS=";"}; {if($13 >= -50 && $13 <= 0 && $14 >= 30 && $14 <= 80 && $2 >= date_min && $2 <= date_max) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-Q" ]; then
					awk -v date_min="${date_min}T23" -v date_max="${date_max}T23" 'BEGIN{FS=";"}; {if($13 >= -90 && $13 <= -60 && $2 >= date_min && $2 <= date_max) print $0;}' $nom_fichier > data_filtre1.csv
				fi
				nom_fichier="data_filtre1.csv"
			elif (( $lieu_present == 1 )); then
				if [ $lieu = "-F" ]; then
					awk 'BEGIN{FS=";"}; {if($13 >= 40 && $13 <= 55 && $14 >= -10 && $14 <= 10) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-G" ]; then
					awk 'BEGIN{FS=";"}; {if($13 >= 2 && $13 <= 6 && $14 >= -55 && $14 <= -51) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-S" ]; then
					awk 'BEGIN{FS=";"}; {if($13 >= 46 && $13 <= 48 && $14 >= -57 && $14 <= -56) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-A" ]; then
					awk 'BEGIN{FS=";"}; {if($13 >= 11 && $13 <= 19 && $14 >= -64 && $14 <= -60) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-O" ]; then
					awk 'BEGIN{FS=";"}; {if($13 >= -50 && $13 <= 0 && $14 >= 30 && $14 <= 80) print $0;}' $nom_fichier > data_filtre1.csv
				elif [ $lieu = "-Q" ]; then
					awk 'BEGIN{FS=";"}; {if($13 >= -90 && $13 <= -60) print $0;}' $nom_fichier > data_filtre1.csv
				fi
				nom_fichier="data_filtre1.csv"
			elif (( $date_present == 3 )); then
				awk -v date_min="${date_min}T23" -v date_max="${date_max}T23" 'BEGIN{FS=";"}; {if($2 >= date_min && $2 <= date_max) print $0;}' $nom_fichier > data_filtre1.csv
				nom_fichier="data_filtre1.csv"
			fi
			echo "Vérification date et lieu terminée"
			for t in $types; do
				num_colonne="1"
				arguments_en_plus=$type_tri
				colonne_de_tri=1
				if [ $t = "-t1" ]; then
					num_colonne="1,15"
				elif [ $t = "-t2" ]; then
					num_colonne="2,15"
					colonne_de_tri=2
				elif [ $t = "-t3" ]; then
					cat $nom_fichier | awk 'BEGIN{FS=";"; OFS=";"}; {gsub(/T/,";",$2); print $0;}' > nouv_fichier.csv
					nom_fichier="nouv_fichier.csv"
					num_colonne="1,2,3,16"
				elif [ $t = "-p1" ]; then
					num_colonne="1,10"
				elif [ $t = "-p2" ]; then
					num_colonne="2,10"
					colonne_de_tri=2
				elif [ $t = "-p3" ]; then
					awk 'BEGIN{FS=";"; OFS=";"}; {gsub(/T/, ";",$2); print $0;}' $nom_fichier > nouv_fichier.csv
					nom_fichier="nouv_fichier.csv"
					num_colonne="1,2,3,11"
				elif [ $t = "-w" ]; then
					num_colonne="1,7,8,13,14"
				elif [ $t = "-h" ]; then
					num_colonne="13,14,18"
					colonne_de_tri=14
					arguments_en_plus=$arguments_en_plus" -r"
				elif [ $t = "-m" ]; then
					num_colonne="1,9,13,14"
					colonne_de_tri=6
					arguments_en_plus=$arguments_en_plus" -r"
				fi
				type=$(echo $t | tr -d "-")
				nom_fichier_res="resultat_$type.csv"
				nom_fichier_trie="fichier_trie_$type.csv"
				cut -d ';' -f$num_colonne $nom_fichier > $nom_fichier_res
				echo "filtrage fini"
				./$nom_executable_c -f $nom_fichier_res -o $nom_fichier_trie $arguments_en_plus
				r=0
				echo "r=$r"
				if (( $r == 1 )); then
					echo "Options incorrectes"
				elif [ $r -eq 2 ]; then
					echo "Probleme à l'ouverture du fichier $nom_fichier_res"
				elif [ $r -eq 3 ]; then
					echo "Probleme à l'ouverture ou à l'écriture du fichier $nom_fichier_trie"
				elif [ $r -eq 4 ];then
					echo "Probleme indéfini à l'execution de l'executable $nom_executable_c"
				elif [ $r -eq 0 ]; then
					echo "tri fini"
					if [ $t = "-t1" ] || [ $t = "-p1" ]; then
						echo "set terminal png size 1500,800 enhanced background rgb 'white'" > gnuplot_script
						echo "set style line 1 lt 1 lw 1.5 pt 3 linecolor rgb '#00000000'" >> gnuplot_script
						echo "set output 'curve_$type.png'" >> gnuplot_script
						echo "plot '$nom_fichier_trie' using 1:4:5 with filledcurve fc \"#FF00FF\", '' using 1:3 smooth mcspline lw 2" >> gnuplot_script
						gnuplot gnuplot_script > fichier_error_gnuplot
						echo "Création du graphique fini"
					elif [ $t = "-t2" ] || [ $t = "-p2" ]; then
						echo "set terminal png size 1500,800 enhanced background rgb 'white'" > gnuplot_script
						echo "set xdata time" >> gnuplot_script
						echo "set timefmt \"%Y-%m-%dT%H\"" >> gnuplot_script
						echo "set format x \"%Y-%m-%d\"" >> gnuplot_script
						echo "set key top left autotitle columnheader" >> gnuplot_script
						echo "set style line 1 lt 1 lw 1.5 pt 3 linecolor rgb '#00000000'" >> gnuplot_script
						echo "set output 'curve_$type.png'" >> gnuplot_script
						echo "plot '$nom_fichier_trie' using 1:2 smooth mcspline lw 2" >> gnuplot_script
						gnuplot gnuplot_script > fichier_error_gnuplot
						echo "Création du graphique fini"
					elif [ $t = "-t3" ] || [ $t = "-p3" ]; then
						echo "set terminal png size 1500,800 enhanced background rgb 'white'" > gnuplot_script
						echo "set xdata time" >> gnuplot_script
						echo "set timefmt \"%Y-%m-%d\"" >> gnuplot_script
						echo "set format x \"%Y-%m-%d\"" >> gnuplot_script
						echo "set key top left autotitle columnheader" >> gnuplot_script
						echo "set output 'curve_$type.png'" >> gnuplot_script
						commande="plot '$nom_fichier_trie' using 1:2:3 index 0 notitle with line lw 2"
						nb_lignes_vides=$(grep -c "^$" $nom_fichier_trie)
						nb_courbes_moins_un=$(( $nb_lignes_vides / 2 ))
						for (( i=1 ; i<$nb_courbes_moins_un ; i++ )); do
							commande="$commande, '' using 1:2:3 index $i notitle with line lw 2"
						done
						echo $commande >> gnuplot_script
						gnuplot gnuplot_script > fichier_error_gnuplot
						echo "Création du graphique fini"
					elif [ $t = "-w" ]; then
						echo "set terminal png size 1500,800 enhanced background rgb 'white'" > gnuplot_script
						echo "set xrange[-180:180]" >> gnuplot_script
						echo "set yrange[-90:90]" >> gnuplot_script
						echo "set output 'curve_$type.png'" >> gnuplot_script
						echo "plot '$nom_fichier_trie' with vectors filled" >> gnuplot_script
						gnuplot gnuplot_script > fichier_error_gnuplot
						echo "Création du graphique fini"
					elif [ $t = "-h" ]; then
						echo "set pm3d map interpolate 0,0" > gnuplot_script
						echo "set dgrid3d" >> gnuplot_script
						echo "set terminal png size 1500,800 enhanced background rgb 'white'" >> gnuplot_script
						echo "set xrange[-180:180]" >> gnuplot_script
						echo "set yrange[-90:90]" >> gnuplot_script
						echo "set output 'curve_$type.png'" >> gnuplot_script
						echo "splot \"$nom_fichier_trie\"" >> gnuplot_script
						gnuplot gnuplot_script > fichier_error_gnuplot
						echo "Création du graphique fini"
					elif [ $t = "-m" ]; then
						echo "set pm3d map interpolate 0,0" > gnuplot_script
						echo "set dgrid3d" >> gnuplot_script
						echo "set terminal png size 1500,800 enhanced background rgb 'white'" >> gnuplot_script
						echo "set xrange[-180:180]" >> gnuplot_script
						echo "set yrange[-90:90]" >> gnuplot_script
						echo "set output 'curve_$type.png'" >> gnuplot_script
						echo "splot \"$nom_fichier_trie\"" >> gnuplot_script
						gnuplot gnuplot_script > fichier_error_gnuplot
						echo "Création du graphique fini"
					fi
				fi
				$(rm -f $nom_fichier_res)
				$(rm -f $nom_fichier_trie)
			done
		fi
		echo "0"
	fi
			
fi

rm -f data_filtre1.csv
rm -f donnees_rangees.txt
rm -f fichier_modifie.csv
rm -f gnuplot_script
rm -f fichier_error_gnuplot
fin=$(date +%s)
duree=$(( $fin - $debut ))
echo $duree
