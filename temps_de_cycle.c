//
// Created by audri on 24/11/2023.
//

#include "temps_de_cycle.h"

// structure de tâche
typedef struct tache
{
    int numero;
    int temps;
} tache;

// tri fusion
void fusion(tache tab[], int deb1, int fin1, int fin2)
{
    tache *table1;
    int deb2 = fin1 + 1;
    int compt1 = deb1;
    int compt2 = deb2;
    int i;

    table1 = malloc((fin1 - deb1 + 1) * sizeof(tache));

    for (i = deb1; i <= fin1; i++)
        table1[i - deb1] = tab[i];

    for (i = deb1; i <= fin2; i++)
    {
        if (compt1 == deb2)
            break;

        else if (compt2 == (fin2 + 1))
        {
            tab[i] = table1[compt1 - deb1];
            compt1++;
        }

        else if (table1[compt1 - deb1].temps < tab[compt2].temps)
        {
            tab[i] = table1[compt1 - deb1];
            compt1++;
        }

        else
        {
            tab[i] = tab[compt2];
            compt2++;
        }
    }
    free(table1);
}

tache tempsdecycle(tache *tab, int temps)
{
    // tri le tableau tab de taille inconnue
    int taille = sizeof(&tab);
    int deb = 0;
    int fin = taille - 1;
    int milieu = (fin + deb) / 2;
    fusion(tab, deb, milieu, fin);
    int compteur = taille;
    while ()
    {
        if (tab[0].temps + tab[compteur].temps> temps)
        {

        }
    }
}