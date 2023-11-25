//
// Created by audri on 24/11/2023.
// Ce programme s'occupe de determiner toutes les tâches précédentes entre elles
// Il prend en entrée un fichier texte contenant les tâches et leurs précédences et une liste
// Il renvoie en sortie un tableau de tâches précédentes où chaque colonne coorespond à une machine différente
// et chaque ligne aux ensembles de tâches qui peuvent être effectuées par la machine correspondante
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_PRECEDENCE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_PRECEDENCE_H

#include "structure.h"

Graphe * lireGraphePrecedence(FILE* nomFichier);
void printLongestPath(Graphe * g, int depart, int arrivee);
void boucleDFSdijkstra(pSommet sommet_actuel, Graphe * g);
void ParcoursDijkstra(int depart, int arrivee, Graphe * graphe);
int precedences();



#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_PRECEDENCE_H
