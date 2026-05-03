# Jeu de la vie C++
Le jeu de la vie en C++

# Mais dis donc ! Tu l'as déjà fait ! Y a quoi de neuf ??
En terme de règles, rien. C'est exactement le même jeu. Cependant il y a de grosses différences avec celui fait en Python.

 - Le jeu est fait en C++ avec SFML
 Comme C++ est un langage compilé (natif), c'est beaucoup plus rapide que la version Python
 
 - Le jeu peut avoir une grande taille
 En effet c'était une limitation de la version Python. Ici, on peut le faire TRÈS grand, ça tournera très vite !
 
 - Le jeu est moins facilement personnalisable
 Ma faute. En effet, sur la version Python, il y avait une ligne de commande avec laquelle on pouvait définir la taille de la grille. Ici il n'y a pas ça.
 Cependant vous pouvez la personnaliser. Pour cela, ouvrez le fichier main.c, et au début il y a des define WIDTH, HEIGHT et CELL_SIZE.
 Vous pouvez changer leur valeur, la fenêtre s'adaptera (attention à bien avoir TOUTES les cases visibles, si vous voulez beaucoup BEAUCOUP de cellules, réduisez la taille des cellules.
 
 - Le jeu ne démarre pas en random
 Ça c'est un avantage. Vous pouvez cliquer sur les cases en début de partie afin de regarder des patterns précis, ce qu'il n'y a pas dans la version Python.
 
# Ok super, mais comment je m'en sert ? Ça démarre pas !
Normal. Voici la (maigre) notice d'utilisation :

Clic gauche de la souris sur une case : la rend vivante (noire)
Clic droit de la souris sur une case : la rend morte (blanche)

Touche C du clavier : tout effacer (mettre toute les cases mortes)
Touche Espace du clavier : démarrer le jeu
Touche R du clavier : stoppe le jeu et efface tout
Touche Échap : Quitter (aussi faisable avec la petite croix)

# Ok mais comment je le fait tourner ? Ou comment je le compile ?
Il vous faudra SFML et un compilateur c++. 
Sous Linux, vous pouvez faire : `g++ main.cpp -lsfml-graphics -lsfml-system -lsfml-window`

# Bon jeu !
