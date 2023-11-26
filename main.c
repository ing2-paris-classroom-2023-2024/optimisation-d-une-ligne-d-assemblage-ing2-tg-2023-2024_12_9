//
// Created by audri on 19/11/2023.
//
#include "stdio.h"
#include "temps_de_cycle.h"
#include "exclusion.h"
#include "precedence.h"
#include "structure.h"
#include "menudelancement.h"
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

int main()
{
    listeTache liste;
    liste.taille = 3;
    liste.tache = malloc(sizeof(tache) * liste.taille);
    for (liste.taille = 0; liste.taille < 3; liste.taille++)
    {
        liste.tache[liste.taille].numero = malloc(sizeof(int));
        liste.tache[liste.taille].tailleNum = 1;
    }
    liste.tache[0].numero[0] = 1;
    liste.tache[0].temps = 3;
    liste.tache[1].numero[0] = 2;
    liste.tache[1].temps = 2;
    liste.tache[2].numero[0] = 3;
    liste.tache[2].temps = 1;
    afficherTache(&liste);
    tempsdecycle(liste.tache, 3, 10);
    afficherTache(&liste);
    int choix;
    /*
    do {
        choix = menu_de_lancement();
    } while (choix == 0);*/
    return 0;
}