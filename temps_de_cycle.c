//
// Created by audri on 24/11/2023.
//

#include "temps_de_cycle.h"

void afficherTache(listeTache *liste)
{
    for (int i = 0; i < liste->taille; i++)
    {
        printf("Machine : %d Tache : ",i);
        for (int j = 0; j < liste->tache[i].tailleNum; j++)
        {
            printf("%d", liste->tache[i].numero[j]);
            if (j != liste->tache[i].tailleNum - 1)
            {
                printf(" -> ");
            }
        }
        printf(" Temps : %d\n", liste->tache[i].temps);
        printf("\n");
    }
}

// tri fusion pour le temps de cycle
void fusion(tache *tab, int deb, int milieu, int fin)
{
    int i1 = deb;
    int i2 = milieu + 1;
    int i;
    tache *tab2;

    // Allocation dynamique pour le tableau temporaire
    tab2 = malloc((fin - deb + 1) * sizeof(tache));

    for (i = 0; i <= fin - deb; i++)
    {
        if (i1 <= milieu && (i2 > fin || tab[i1].temps < tab[i2].temps))
        {
            tab2[i] = tab[i1];
            i1++;
        }
        else
        {
            tab2[i] = tab[i2];
            i2++;
        }
    }
    // Copie les éléments triés de tab2 à tab
    for (i = 0; i <= fin - deb; i++)
    {
        tab[deb + i] = tab2[i];
    }

    // Libération de la mémoire allouée pour tab2
    free(tab2);
}

// tri par Insersion pour le temps de cycle
void triInsertion(tache *tab, int taille)
{
    int i, j;
    tache temp;
    for (i = 1; i < taille; i++)
    {
        temp = tab[i];
        j = i - 1;
        while (j >= 0 && tab[j].temps > temp.temps)
        {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = temp;
    }
}

int verifliste(tache *tab, int taille, int temps)
{
    int i;
    if (taille == 1)
    {
        return 0;
    }
    else
    {
        if (tab[0].temps + tab[1].temps > temps)
        {
            return 0;
        }
        return 1;
    }
    return 1;
}

void fusiontache(tache *t1, tache *t2)
{
    tache t;
    t.tailleNum = t1->tailleNum + t2->tailleNum;
    t.numero = malloc(t.tailleNum*sizeof(int));
    if (t.tailleNum == 1)
    {
        t.numero[0] = t1->numero[0];
    }
    else
    {
        for (int i = 0; i < t1->tailleNum; ++i)
        {
            t.numero[i] = t1->numero[i];
        }
    }
    if (t.tailleNum == 1)
    {
        t.numero[t1->tailleNum] = t2->numero[0];
    }
    else
    {
        for (int i = 0; i < t1->tailleNum; ++i)
        {
            t.numero[t1->tailleNum + i] = t2->numero[i];
        }
    }
    t.temps = t1->temps + t2->temps;
    free(t1->numero);
    free(t2->numero);
    free(t2);
    *t1 = t;
}


void tempsdecycle(listeTache *liste, int temps)
{
    int compteur = liste->taille;
    printf("test\n");
    while (verifliste(liste->tache, liste->taille, temps))
    {
        printf("test1\n");
        triInsertion(liste->tache, liste->taille);
        if (liste->tache[0].temps + liste->tache[compteur].temps < temps)
        {
            printf("test2\n");
            fusiontache(&liste->tache[0], &liste->tache[liste->taille - 1]);
            printf("test3\n");
            liste->taille--;
            compteur--;
            // addaptation de la taille de la liste
            if (liste->taille != compteur)
            {
                for (int i = compteur; i < liste->taille - 1; i++)
                {
                    liste->tache[i] = liste->tache[i + 1];
                }
            }
            printf("test4\n");
            afficherTache(liste);
            realloc(liste->tache, sizeof(tache) * liste->taille);
        }
        else
        {
            compteur--;
        }

    }
    printf("test5\n");
}