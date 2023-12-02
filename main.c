//
// Created by audri on 19/11/2023.
//
#include "stdio.h"
#include "temps_de_cycle.h"
#include "exclusion.h"
#include "precedence.h"
#include "structure.h"
#include "menudelancement.h"
int main()
{

    int *tab;
    int tailleX = 5;
    int tailleY = 3;


    // Allocation dynamique du tableau
    tab = malloc(tailleY * sizeof(int*));

    tab[0] = 1;
    tab[1]= 2;
    tab[2] = 3;
    tab[3] = 4;
    tab[4] = 5;
/*
    for (int i = 0; i < tailleX; ++i)
    {
        tab[i] = malloc(tailleX * sizeof(int));
    }
    // Initialisation du tableau test
    tab[0][0] = 1;
    tab[0][1] = 2;
    tab[0][2] = 3;
    tab[0][3] = 4;
    tab[0][4] = 5;
    tab[1][0] = 6;
    tab[1][1] = 7;
    tab[1][2] = 8;
    tab[1][3] = 9;
    tab[1][4] = 10;
    tab[2][0] = 11;
    tab[2][1] = 12;
    tab[2][2] = 13;
    tab[2][3] = 15;
    tab[2][4] = 16;
    printf("test\n");*/
    initilisationtempscycle(tab , tailleX);
    int choix;
    do {
        choix = menu_de_lancement();
    } while (choix == 0);
    return 0;
}