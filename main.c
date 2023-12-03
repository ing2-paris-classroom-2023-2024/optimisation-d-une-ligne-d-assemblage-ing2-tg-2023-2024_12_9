//
// Created by audri on 19/11/2023.
//
#include "stdio.h"
#include "temps_de_cycle.h"
#include "exclusion.h"
#include "precedence.h"
#include "structure.h"
#include "menudelancement.h"


// tri par Insersion pour le temps de cycle

void triInsertionint(int *tab, int taille)
{
    int i, j;
    int temp;
    for (i = 1; i < taille; i++)
    {
        temp = tab[i];
        j = i - 1;
        while (j >= 0 && tab[j] < temp)
        {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = temp;
    }
}
void comparaison(int **tab, tableauMemoire tableauMemoire1 , int nX, int nY)
{
    // verifie que toutes les valeurs de la même ligne de tableauMemoire1 soit dans la même ligne de tab
    int verif = 0 ;
    int compteur = 0;
    int temps[tableauMemoire1.nombreTaches];

            for (int k = 0; k < tableauMemoire1.nombreMachines; ++k)
            {
                for (int l = 0; l < tableauMemoire1.nombreTaches; ++l)
                {
                    for (int i = 0; i < nY; ++i)
                    {
                        for (int j = 0; j < nY; ++j)
                        {
                            if (tab[i][j] == tableauMemoire1.tableauPrecedences[k][l])
                            {
                                for (int m = 0; m < sizeof(temps) -1; ++m)
                                {
                                    if (temps[m] == temps[m+1])
                                    {verif = 1;}
                                    else {verif = 0;}
                                }
                                compteur++;
                                if (verif == 0)
                                {
                                    temps[compteur] = i;
                                }
                            }
                }
            }

        }
    }
}

int main()
{
    tableauMemoire tab;
    tableauC tabC;
    int **tabtemp;
    tab.tableauPrecedences = NULL;
    tab.nombreMachines = 0;
    tab.nombreTaches = 0;
    struct Graph g;
    initGraph(&g, MAX);
    Construire_Graph(&g, "../exclusion/exclusions.txt"); // Remplacez par le chemin de votre fichier
    int color[MAX];
    graphColoring(&g, MAX, color); // Utilisez MAX_VERTICES comme estimation du nombre de couleurs
    affichage_stations(color, g.nb_sommets, &tabC.tableauC, &tabC.nX, &tabC.nY);
    // afficher le tabC
    printf("Nombre de machines : %d\n", tabC.nX);
    printf("Nombre de tâches : %d\n", tabC.nY);
    for(int i = 0; i < tabC.nX; i++){
        triInsertionint(tabC.tableauC[i], tabC.nY);
    }
    for (int i = 0; i < tabC.nX; ++i)
    {
        printf("Machine %d : ", i);
        for (int j = 0; j < tabC.nY; ++j)
        {
            printf("%d ", tabC.tableauC[i][j]);
        }
        printf("\n");
    }

    int choix;
    do {
        choix = menu_de_lancement();
    } while (choix == 0);
    if (choix == 1) {

        //exclusion(&tab);
        // afficher le tableau de précédences
        for(int i = 0; i < tab.nombreMachines; i++){
            printf("Machine %d : ", i);
            for(int j = 0; j < tab.nombreTaches; j++){
                if (tab.tableauPrecedences[i][j] != 0) printf("%d ", tab.tableauPrecedences[i][j]);
            }
            printf("\n");
        }
    }
    if (choix == 2) {

        //temps_de_cycle(&tab);
        // afficher le tableau de précédences
        for(int i = 0; i < tab.nombreMachines; i++){
            printf("Machine %d : ", i);
            for(int j = 0; j < tab.nombreTaches; j++){
                if (tab.tableauPrecedences[i][j] != 0) printf("%d ", tab.tableauPrecedences[i][j]);
            }
            printf("\n");
        }
    }
    if (choix == 3)
    {

        precedences(&tab);
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
        initilisationtempscycle(&tab);
        // afficher le tableau de précédences
        for(int i = 0; i < tab.nombreMachines; i++){
            printf("Machine %d : ", i);
            for(int j = 0; j < tab.nombreTaches; j++){
                if (tab.tableauPrecedences[i][j] != 0) printf("%d ", tab.tableauPrecedences[i][j]);
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

