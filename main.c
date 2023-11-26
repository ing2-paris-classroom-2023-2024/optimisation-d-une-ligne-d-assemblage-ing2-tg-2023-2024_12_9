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
    printf("Temps de cycle : %d\n", remplir_temps_de_cycle("../temps/temps_cycle.txt"));
    tempsdecycle(&liste, remplir_temps_de_cycle("../temps/temps_cycle.txt"));
    afficherTache(&liste);
    int choix;
    /*
    do {
        choix = menu_de_lancement();
    } while (choix == 0);*/
    return 0;
}