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




int main()
{
    listeTache liste;
    remplirTache(&liste, "../operation/operations.txt");
    afficherTache(&liste);
    printf("\n");
    tempsdecycle(&liste, 10);
    afficherTache(&liste);
    int choix;
    /*
    do {
        choix = menu_de_lancement();
    } while (choix == 0);*/
    return 0;
}