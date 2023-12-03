// Created by audri on 24/11/2023.
// Ce programme s'occupe de determiner toutes les tâches incompatible entre elles
// Il prend en entrée un fichier texte contenant les tâches et leurs incompatibilités et une liste
// Il renvoie en sortie un tableau de tâches incompatibles où chaque colonne coorespond à une machine différente
// et chaque ligne aux ensembles de tâches qui peuvent être effectuées par la machine correspondante

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_EXCLUSION_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_EXCLUSION_H

#include "structure.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 40  // Estimation du nombre maximum de sommets
// Structure pour représenter un graphe
struct Graph {
    int Matrice[MAX][MAX];
    int nb_sommets;
};
void initGraph(struct Graph* g, int nb_sommet);
void Construire_Graph(struct Graph* g, const char* filename);
void graphColoring(struct Graph* g, int m, int couleurs[]);
void affichage_stations(int couleur[], int nb_sommets);
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_EXCLUSION_H
