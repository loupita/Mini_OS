# Mini_OS

Le système d’exploitation est codé en C sous forme d’une fonction qui vérifie continuellement l’occupation de la mémoire. Lorsqu’elle est occupée à 97%, l’OS décharge la page la plus ancienne vers le swap. Lorsqu’il y a beaucoup plus espace l’OS recharge la page la plus veille du Swap. Cette fonction sera lancée sous forme de thread. 
