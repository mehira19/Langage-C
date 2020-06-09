/*
 *
 *
 *
 */


#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define L 12 /* nombre de lignes du damier */
#define C 18 /* nombre de colonnes du damier */

void sleep(int s) /* fonction permettant d'attendre s secondes */
{
	time_t start_time = 0;
	time_t current_time = 0;

	start_time = time(NULL);

	while(current_time-start_time+1 <= s)
		current_time = time(NULL);
}

void initialisation_damier(int damier[L][C])
{
	/* Initialise chaque cellule du damier "damier" (vivante ou morte) de maniere aleatoire */
	int val;

	for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++)
        {
            val = rand() % 100;
            if (val < 50) // Cellule vivante
            {
                damier[i][j] = 1;
            } else { // Cellule morte
                damier[i][j] = 0;
            }
        }
	}

}

void affiche_damier(int damier[L][C])
{
	/* Affiche le damier "damier" */
	for (int i = 0; i < L; i++)
    {
        for (int k = 0; k < (2 * C + 1); k++) printf("-");
        printf("\n");
        for (int j = 0; j < C; j++)
        {
            printf("|");
            if (damier[i][j] == 1)
            {
                printf("o");
            } else {
                printf("-");
            }
        }
        printf("|\n");
    }
    for (int k = 0; k < (2 * C); k++) printf("-");
    printf("\n");
}

int nombre_voisins(int damier[L][C], int i0, int j0)
{
	/* Renvoie le nombre de voisins vivants de la cellule (i0,j0) du damier "damier" */
	int nb = 0;

    /* Nombre total de voisins (mort et vivant)
    if ((i0 == 0 && j0 == 0) || (i0 == 0 && j0 == C-1) || (i0 == L-1 && j0 == 0) || (i0 == L-1 && j0 == C-1)) nb = 3;
    else if (i0 == 0 || i0 == L-1 || j0 == 0 || j0 == C-1) nb = 5;
    else nb = 8;
    */

    for (int i = i0-1; i < i0+2; i++)
    {
        for (int j = j0-1; j < j0+2; j++)
        {
            if ((i != i0 || j != j0) && i >= 0 && i < L && j >= 0 && j < C && damier[i][j] == 1) nb++;
        }
    }

	return nb;
}

void generation_suivante(int damier[L][C], int new_damier[L][C])
{
	/* Remplit le damier "new_damier" representant la generation suivante du damier "damier" */
	int nb_voisins;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++)
        {
            nb_voisins = nombre_voisins(damier, i, j);
            new_damier[i][j] = damier[i][j];
            if (damier[i][j] == 1 && (nb_voisins == 2 || nb_voisins == 3)) new_damier[i][j] = 1;
            else if (damier[i][j] == 1 && (nb_voisins < 2 || nb_voisins > 3)) new_damier[i][j] = 0;
            else if (damier[i][j] == 0 && nb_voisins == 3) new_damier[i][j] = 1;

        }
    }
}

void copie_damier(int damier_cible[L][C], int damier_source[L][C])
{
	/* Copie l'ensemble des cellules du damier "damier_source" vers le damier "damier_cible" */
	for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++) damier_cible[i][j] = damier_source[i][j];

    }
}


int main ()
{
	int i = 0;
	int nbCycles = 0;

	int damier[L][C];
	int new_damier[L][C];


	/*
	 * A completer : rentrer le nombre de cycles au clavier
	 *
	 */
	 scanf("%i", &nbCycles);

	/*
	 * A completer : initialisation du generateur de nombres
	 * aleatoires
	 */
	 srand(time(NULL));

	/*
	 * A completer : initialisation du damier
	 */
	 initialisation_damier(damier);

	while (i < nbCycles)
	{
		system("cls"); /* efface l'ecran de la console sur Windows */

		/* A completer : on affiche le damier */
		affiche_damier(damier);
		/* A completer : on calcule la generation suivante */
		generation_suivante(damier, new_damier);
		/* A completer : on copie l'ensemble des cellules du nouveau damier vers l'ancien damier */
		copie_damier(damier, new_damier);
		/* A completer : attendre 1 seconde */
        sleep(1);
		i++;
	}

	return 0;
}
