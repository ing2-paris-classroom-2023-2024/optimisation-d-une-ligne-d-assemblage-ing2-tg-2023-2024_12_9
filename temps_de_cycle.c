//
// Created by audri on 24/11/2023.
//

#include "temps_de_cycle.h"



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
    t.tailleNum = sizeof(t1->numero)/4 + sizeof(t2->numero)/4;
    t.numero = malloc(t.tailleNum*sizeof(int));
    if (t.tailleNum == 1)
    {
        t.numero[0] = t1->numero[0];
    }
    else
    {
        for (int i = 0; i < sizeof(t1->numero)/4; ++i)
        {
            t.numero[i] = t1->numero[i];
        }
    }
    if (t.tailleNum == 1)
    {
        t.numero[sizeof(t1->numero)/4] = t2->numero[0];
    }
    else
    {
        for (int i = 0; i < sizeof(t2->numero)/4; ++i)
        {
            t.numero[sizeof(t1->numero)/4 + i] = t2->numero[i];
        }
    }
    printf("%d",sizeof(t.numero)/4);
    t.temps = t1->temps + t2->temps;
    free(t1->numero);
    free(t2->numero);
    free(t2);
    *t1 = t;
}


void tempsdecycle(tache *tab, int taille, int temps)
{
    int compteur = taille;
    printf("test\n");
    while (verifliste(tab, taille, temps))
    {
        printf("test1\n");
        triInsertion(tab, taille);
        if (tab[0].temps + tab[compteur].temps < temps)
        {
            printf("test2\n");
            fusiontache(&tab[0], &tab[taille]);
            printf("test3\n");
            taille--;
            compteur--;
            // addaptation de la taille de la liste
            for (int i = 1; i < taille; i++)
            {
                tab[i] = tab[i + 1];
            }
            printf("test4\n");
            realloc(tab, sizeof(tache) * taille);
        }
        else
        {
            compteur--;
        }

    }
}