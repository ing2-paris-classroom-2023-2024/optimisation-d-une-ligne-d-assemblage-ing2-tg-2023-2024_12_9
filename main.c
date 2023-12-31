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
    int **tabtemp;
    tab.tableauPrecedences = NULL;
    tab.nombreMachines = 0;
    tab.nombreTaches = 0;
    struct Graph g;
    initGraph(&g, MAX);
    Construire_Graph(&g, "../exclusion/exclusions.txt"); // Remplacez par le chemin de votre fichier
    int color[MAX];
    graphColoring(&g, MAX, color); // Utilisez MAX_VERTICES comme estimation du nombre de couleurs

    int choix;
    do {
        choix = menu_de_lancement();
    } while (choix == 0);
    if (choix == 1) {
        precedences(&tab);
        printf("\n");
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
        verifmmC(&tab, color);
        // afficher le tableau de précédences
        for(int i = 0; i < tab.nombreMachines; i++){
            printf("Machine %d : ", i);
            for(int j = 0; j < tab.nombreTaches; j++){
                if (tab.tableauPrecedences[i][j] != 0 ) printf("%d ", tab.tableauPrecedences[i][j]);
            }
            printf("\n");
        }
    }
    if (choix == 2)
    {
        verifmmC(&tab, color);
        for(int i = 0; i < tab.nombreMachines; i++){
            printf("Machine %d : ", i);
            for(int j = 0; j < tab.nombreTaches; j++){
                if (tab.tableauPrecedences[i][j] != 0 ) printf("%d ", tab.tableauPrecedences[i][j]);
            }
            printf("\n");
        }
        initilisationtempscycle(&tab);
        // afficher le tableau de précédences
        for(int i = 0; i < tab.nombreMachines; i++){
            printf("Machine %d : ", i);
            for(int j = 0; j < tab.nombreTaches; j++){
                if (tab.tableauPrecedences[i][j] != 0 ) printf("%d ", tab.tableauPrecedences[i][j]);
            }
            printf("\n");
        }
    }
    if (choix == 3)
    {
        precedences(&tab);
        printf("\n");
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
        verifmmC(&tab, color);
        initilisationtempscycle(&tab);
        // afficher le tableau de précédences
        for(int i = 0; i < tab.nombreMachines; i++){
            printf("Machine %d : ", i);
            for(int j = 0; j < tab.nombreTaches; j++){
                if (tab.tableauPrecedences[i][j] != 0 ) printf("%d ", tab.tableauPrecedences[i][j]);
            }
            printf("\n");
        }
    }
    // libération de la mémoire
    for (int i = 0; i < tab.nombreMachines; ++i)
    {
        free(tab.tableauPrecedences[i]);
    }
    free(tab.tableauPrecedences);
    return 0;
}

