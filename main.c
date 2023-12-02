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
    tableauMemoire tab;
    tab.tableauPrecedences = NULL;
    tab.nombreMachines = 0;
    tab.nombreTaches = 0;
    precedences(&tab);
    printf("Nombre de machines : %d\n", tab.nombreMachines);
    printf("Nombre de tâches : %d\n", tab.nombreTaches);
    // realloc le tableau de précédences au nombre de machines
    tab.tableauPrecedences = realloc(tab.tableauPrecedences, tab.nombreMachines * sizeof(int*));
    // compter le nombre de tâches
    tab.nombreTaches = 0;
    for(int i = 0; i < tab.nombreMachines; i++){
        int compteur = 0;
        while(tab.tableauPrecedences[i][compteur] != 0){
            compteur++;
        }
        if (compteur > tab.nombreTaches)tab.nombreTaches = compteur;
    }
    for ( int i = 0; i < tab.nombreMachines; i++){
        tab.tableauPrecedences[i] = realloc(tab.tableauPrecedences[i], tab.nombreTaches * sizeof(int));
    }
    printf("Nombre de tâches : %d\n", tab.nombreTaches);
    // afficher le tableau de précédences
    for(int i = 0; i < tab.nombreMachines; i++){
        printf("Machine %d : ", i);
        for(int j = 0; j < tab.nombreTaches; j++){
            printf("%d ", tab.tableauPrecedences[i][j]);
        }
        printf("\n");
    }
    initilisationtempscycle(&tab);
    /*
    int choix;
    do {
        choix = menu_de_lancement();
    } while (choix == 0);
    return 0;*/
}