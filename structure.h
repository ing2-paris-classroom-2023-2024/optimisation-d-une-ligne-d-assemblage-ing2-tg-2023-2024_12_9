//
// Created by audri on 24/11/2023.
//

#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_STRUCTURE_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>


/* Structure d'un arc*/
struct Arc
{
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int poids; // Pondération de l'arc
    struct Arc* arc_suivant;
};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

struct arcKruskal
{
    int sommet1;
    int sommet2;
    int poids;
};

typedef struct arcKruskal* pArcKruskal;

/* Structure d'un sommet*/
struct Sommet
{
    struct Sommet* predecesseur;
    struct Arc* arc;
    int distance;
    int numero;
    char couleur;
    int kruskal;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int poidstotal;
    int orientation;
    int ordre;
    pSommet* pSommet;
    pArcKruskal * pArcKruskal;
} Graphe;

/* Structure d'un Maillon de la liste, il contient chacun un sommet et un pointeur vers le maillon suivant*/
struct Maillon
{
    struct Sommet* sommet;
    struct Maillon* suivant;

};

typedef struct Maillon* pMaillon;



typedef struct Liste{
    int longueur;
    struct Maillon * tete;
    struct Maillon * queue;
}Liste;

// Méthode de tri à bulles
void triABulles(Graphe * graphe, Graphe * arbre, int taille);

// créer le graphe
Graphe* CreerGraphe(int ordre);

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier);

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2, int poids);

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num);

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe);
#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_TD12_GRP9_STRUCTURE_H
