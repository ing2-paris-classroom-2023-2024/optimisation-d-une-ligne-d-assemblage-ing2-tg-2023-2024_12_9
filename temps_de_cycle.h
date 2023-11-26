//
// Created by audri on 24/11/2023.
// Ce fichier s'occupe de derterminer les tâches qui peuvent être faite pendant un temps de cycle donné
// Il prend un fichier de tâches avec leur temps respectif et un temps de cycle

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_TEMPS_DE_CYCLE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_TEMPS_DE_CYCLE_H
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
// structure de tâche
typedef struct tache
{
    int *numero; // tableau de numéro de tâche
    int tailleNum; // taille du tableau
    int temps; // milisecondes
} tache;

// structure de liste de tâche
typedef struct listeTache
{
    tache *tache; // tableau de tâche
    int taille; // taille du tableau
} listeTache;

void fusion(tache tab[], int deb1, int fin1, int fin2);
int verifliste(tache *tab, int taille, int temps);
void fusiontache(tache *t1, tache *t2);
void triInsertion(tache *tab, int taille);
void tempsdecycle(listeTache *liste,int temps);
void afficherliste(listeTache *liste);
void remplirTache(listeTache *liste, char *nomFichier);
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_TEMPS_DE_CYCLE_H
