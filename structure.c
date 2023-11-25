//
// Created by audri on 24/11/2023.
//

#include "structure.h"
#include <stdio.h>
#define SIZE 16
// fonction qui prend en paramètre une chaine de caractère et ouvre le fichier correspondant
FILE* ouvrirFichier(char* nomFichier){
    FILE* fichier = fopen(nomFichier,"r");
    if(fichier == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(-1);
    }
    return fichier;
}
void triABulles(Graphe* graphe, Graphe * arbre, int nombreArcsGraphe){
    int size = graphe->ordre;
    const int taille = nombreArcsGraphe;
    pArcKruskal tab[taille];

    for(int i1 = 0; i1 < taille; i1++){
        tab[i1] = graphe->pArcKruskal[i1];
    }

    // int i, j;
    pArcKruskal tmp;

    //afficher les éléments du tableau
    for (int k = 0; k < taille; ++k) {
        printf("%d ", tab[k]->poids);
    }
    printf("\n");

    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            /* Pour un ordre décroissant utiliser < */
            if (tab[j]->poids > tab[j + 1]->poids) {
                tmp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = tmp;
            }
        }
    }

    for(int l = 0; l < graphe->taille; l++){
        arbre->pArcKruskal[l]->sommet1 = tab[l]->sommet1;
        arbre->pArcKruskal[l]->sommet2 = tab[l]->sommet2;
        arbre->pArcKruskal[l]->poids = tab[l]->poids;
    }

    for (int m = 0; m < taille; ++m) {
        printf("%d ", arbre->pArcKruskal[m]->poids);
    }
    printf("\n");



}

// algorithme pris de "https://waytolearnx.com/2019/08/tri-a-bulle-en-c.html"

Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->poidstotal=0;
    Newgraphe->pSommet = (pSommet*)malloc((ordre)*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->numero=i;
        Newgraphe->pSommet[i]->couleur='B';
        Newgraphe->pSommet[i]->arc=NULL;
        Newgraphe->pSommet[i]->predecesseur=NULL;
        Newgraphe->pSommet[i]->distance=-1;
    }
    return Newgraphe;
}

pSommet* CreerArete(pSommet* sommet,int s1,int s2, int poids)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids=poids;
        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids=poids;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, orientation, ordre, s1, s2, poids;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs,"%d",&ordre);

    graphe=CreerGraphe(ordre); // créer le graphe d'ordre sommets

    graphe->ordre=ordre;
    int temp = 0;

    for (int i=0; i<ordre; ++i)
    {
        fscanf(ifs,"%d",&temp);
        graphe->pSommet[i]->numero=temp;
    }

    fscanf(ifs,"%d",&taille);
    graphe->taille=taille;

    graphe->pArcKruskal = (pArcKruskal*)malloc((taille)*sizeof(pArcKruskal));

    for(int i=0; i<taille; i++)
    {
        graphe->pArcKruskal[i]=(pArcKruskal)malloc(sizeof(struct arcKruskal));
        graphe->pArcKruskal[i]->sommet1=-1;
        graphe->pArcKruskal[i]->sommet2=-1;
        graphe->pArcKruskal[i]->poids=-1;
    }

    graphe->orientation= 0;

    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    {
        fscanf(ifs,"%d%d%d",&s1,&s2,&poids);
        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2, poids);
        graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, poids);
        graphe->pArcKruskal[i]->sommet1 = s1;
        graphe->pArcKruskal[i]->sommet2 = s2;
        graphe->pArcKruskal[i]->poids = poids;
        // printf("s1 : %d, s2 : %d, poids : %d\n",s1,s2,poids);
    }

    return graphe;
}


void afficher_successeurs(pSommet * sommet, int num)
{

    if(sommet[num]->arc==NULL) {
        printf(" sommet %d : pas de successeurs", num);
    }

    else{
        printf("Sommet %d :\n",num);

        pArc arc=sommet[num]->arc;

        while(arc!=NULL)
        {
            printf("%d ",arc->sommet);
            arc=arc->arc_suivant;
        }
    }

}

void graphe_afficher(Graphe* graphe)
{
    printf("Graphe ");

    if(graphe->orientation)
        printf("oriente ");
    else
        printf("non oriente ");

    printf("d'ordre %d\n",graphe->ordre);

    printf("Listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++){
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}