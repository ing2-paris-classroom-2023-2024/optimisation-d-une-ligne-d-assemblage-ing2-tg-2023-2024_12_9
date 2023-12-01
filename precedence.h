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



Graphe * lireGraphePrecedence(char * nomFichier);
Liste * CreerListe(pSommet sommet);
void EnfilerSommet(Liste * Liste, pSommet sommetAEnfiler);
int prochainPointDeDepart(Graphe * graphe);
void DefilerSommetBFS(Liste * Liste);
void parcoursBFS(Graphe* graphe);
void precedences(tableauMemoire * tableau);



#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_PRECEDENCE_H
