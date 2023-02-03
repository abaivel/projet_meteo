# projet_meteo
Bienvenue dans CY METEO, une application qui va traiter un fichier de données météorologiques dans le but d’afficher des graphiques ! <br/>
Les données traitées seront multiples et au choix de l’utilisateur : précipitations, températures, humidité, vitesse et orientation des vents, etc... Il pourra également choisir le lieu et la période des données à analyser. <br/>
L'application est un script shell à exécuter avec le format suivant : ./script_cy_meteo [OPTIONS] ou bash script_cy_meteo [OPTIONS] <br/>
Les différentes options sont :
  * L'option pour indiquer le fichier de données : (Option obligatoire) <br/>
      -f <nom_fichier> : permet d'indiquer au script dans quel fichier prendre les données météorologiques, nom_fichier correspond au nom du fichier, dont les données doivent être séparées par un point-virgule ';' <br/>
  * Les options pour choisir le type de données : (Il est obligatoire d'avoir au moins une de ces options) <br/>
      -t1 : Les données sont triées dans l'ordre croissant par ID de station et pour chaque station, la moyenne, le minimum et le maximum des températures sont calculés. Le graphique crée un graphique de type barres d’erreur avec en abscisse l’identifiant de la station, et en ordonnée le minimum, maximum et la moyenne. <br/>
      -t2 : Les données sont triées dans l'ordre chronologique et pour chaque date/heure, la moyenne des températures est calculée. Le graphique crée est un graphique de type ligne simple (courbe) avec en abscisse le jour et l’heure des mesures, et en ordonnée la moyenne. <br/>
      -t3 : Les données sont triées d'abord par heure, puis par ID de station, puis par date. Le graphique crée est un graphique de type multi-lignes avec en abscisse les jours, et en ordonnée les valeurs de températures mesurées. Ce diagramme contiendra 1 ligne par station et par heure avec les courbes correspondant à la même heure dans la même couleur. <br/>
      -p1 : Les données sont triées dans l'ordre croissant par ID de station et pour chaque station, la moyenne, le minimum et le maximum des pressions sont calculés. Le graphique crée un graphique de type barres d’erreur avec en abscisse l’identifiant de la station, et en ordonnée le minimum, maximum et la moyenne. <br/>
      -p2 : Les données sont triées dans l'ordre chronologique et pour chaque date/heure, la moyenne des pressions est calculée. Le graphique crée est un graphique de type ligne simple (courbe) avec en abscisse le jour et l’heure des mesures, et en ordonnée la moyenne. <br/>
      -p3 : Les données sont triées d'abord par heure, puis par ID de station, puis par date. Le graphique crée est un graphique de type multi-lignes avec en abscisse les jours, et en ordonnée les valeurs de pression mesurées. Ce diagramme contiendra 1 ligne par station et par heure avec les courbes correspondant à la même heure dans la même couleur. <br/>
      -w : Les données sont triées dans l'ordre croissant par ID de station et pour chaque station, l’orientation moyenne et la vitesse moyenne des
vents sont calculées. Le graphique crée est un graphique de type vecteurs (correspondant au vent) avec l’abscisse correspondant à la longitude et l’ordonnée correspondant à la latitude. <br/>
      -h : Les données sont triées dans l'ordre décroissant par l'altitude de chaque station. Le graphique crée est un graphique de type carte interpolée et colorée montrant l'altitude avec l’abscisse correspondant à la longitude et l’ordonnée correspondant à la latitude. <br/>
      -m : Les données sont triées dans l'ordre décroissant par l'humidité maximale de chaque station. Le graphique crée est un graphique de type carte interpolée et colorée montrant l'humidité maximale avec l’abscisse correspondant à la longitude et l’ordonnée correspondant à la latitude. <br/>
  * Les options pour filtrer les données par lieu : (Ces options sont exclusives, une seule peut être utilisée) <br/>
      -F : Seulement les données de la France métropolitaine seront traités <br/>
      -G : Seulement les données de la Guyane française seront traités <br/>
      -S : Seulement les données de Saint-Pierre-et-Miquelon seront traités <br/>
      -A : Seulement les données des Antilles seront traités <br/>
      -O : Seulement les données de l'Océan Indien seront traités <br/>
      -Q : Seulement les données de l'Antarctique seront traités <br/>
   * L'option pour filtrer les données par date : <br/>
      -d <min> <max> : les données traitées sont dans l’intervalle de dates [<min>..<max>] incluses. Le format des dates est une chaine de type YYYY-MM-DD (année-mois-jour). <br/>
   * Les options pour trier les données : (Ces options sont exclusives, une seule peut être utilisée) <br/>
      --avl : Option par défaut, les données seront triées par un avl, c'est-à-dire un arbre binaire de recherche équilibré. C'est le tri le plus rapide. <br/>
      --abr : Les données seront triées par un abr, c'est-à-dire un arbre binaire de recherche. <br/>
      --tab : Les données seront triées par une liste chainée. C'est le tri le plus lent (grandement déconseillé avec l'option t2 et p2 san filtrage, à moins de vouloir rester plus de 12 minutes à attendre) <br/>
   Il existe aussi l'option --help pour afficher le manuel (à utiliser seule, sans autre option) <br/>

Les graphiques crés sont trouvables dans le répertoire, ils ne seront pas affichés par le script. Le script n'affiche rien durant son exécution, à part un message pour vous informer que tel graphique a été crées. Un graphique est crée par type de données choisis et som nom sera dans le format "curve_type.png" avec type remplacé par le type de données (t1,w,h,...) <br/>

Pour trier les données, le script shell appelle un programme en C. Le script peut compiler le programme lui-même mais si vous souhaitez compiler le programme C, utilisez juste la commande make lorsque vous êtes dans le répertoire de base (pas dans "programmes_c"). <br/>

    

