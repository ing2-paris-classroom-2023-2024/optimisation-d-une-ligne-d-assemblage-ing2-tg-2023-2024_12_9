//
// Created by Ethan arfi on 26/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_STRUCTURE_ARFI_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_STRUCTURE_ARFI_H

#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_STRUCTURE_ARFI_H
//
// Created by Ethan ARFI et Julien HOGOMMAT
//

#ifndef TP1
#define TP1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Sommet{
    char *nom;
    int numero;
}t_s;



typedef struct Graphe{
    int ordre;
    t_s *Sommetab;
    int **matrice;
}t_graphe;

t_s initSommet(char *nom, int numero);


void initGraphe(int ordre, t_graphe *graphe);


void recupFichier(t_graphe *graphe);


void affichagedonnees(t_graphe *graphe);


#endif
