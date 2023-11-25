//
// Created by audri on 24/11/2023.
//


#include "precedence.h"

Graphe * lireGraphePrecedence(FILE * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille = 0, orientation, ordre, s1, s2, poids;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    // Parcours du fichier un première fois pour déterminer le nombre de sommets et d'arcs

    int sommetMaximum = 0;

    // CE SCRIPT PART DU PRINCIPE QUE LES SOMMETS SONT NUMEROTES DE 1 A N
    while (fscanf(ifs,"%d %d",&s1,&s2) != EOF)
    {
        if (s1 > sommetMaximum) {
            sommetMaximum = s1;
        }
        if (s2 > sommetMaximum) {
            sommetMaximum = s2;
        }
        taille++;
    }

    // On remet le curseur au début du fichier
    fseek(ifs, 0, SEEK_SET);

    ordre = sommetMaximum;
    graphe=CreerGraphe(ordre); // créer le graphe d'ordre sommets

    graphe->ordre=ordre;

    for (int i=0; i<ordre; ++i)
    {
        fscanf(ifs,"%d %d",&s1, &s2);
        CreerArete(graphe->pSommet, s1, s2, 1);
    }

    return graphe;
}

void printLongestPath(Graphe * g, int depart, int arrivee)
{
    if(depart==arrivee)
    {
        printf("%d",depart);
    }
    else if(g->pSommet[arrivee]->predecesseur==NULL)
    {
        printf("Il n'existe pas de chemin entre %d et %d",depart,arrivee);
    }
    else
    {
        printLongestPath(g,depart,g->pSommet[arrivee]->predecesseur->numero);
        printf("->%d",arrivee);
    }
}

void boucleDFSdijkstra(pSommet sommet_actuel, Graphe * g){
    pArc tempArc = sommet_actuel->arc;
    pArc arcMinimum = NULL;
    int longueurArcMinimum = 0;
    printf("sommet actuel : %d\n",sommet_actuel->numero);
    if(tempArc !=NULL) {
        longueurArcMinimum = -1;
        while (tempArc != NULL) {
            printf("Arc de %d vers %d, poids = %d\n",sommet_actuel->numero,tempArc->sommet,tempArc->poids);
            // si la distance du sommet actuel + le poids de l'arc est inférieur à la distance du sommet de destination
            if (sommet_actuel->distance + tempArc->poids > g->pSommet[tempArc->sommet]->distance)
            {
                g->pSommet[tempArc->sommet]->distance = sommet_actuel->distance + tempArc->poids;
                g->pSommet[tempArc->sommet]->predecesseur = sommet_actuel;
                g->pSommet[tempArc->sommet]->couleur = 'G';
            }

            // pour trouver l'arc de poids minimum et continuer le programme
            if (tempArc->poids > longueurArcMinimum && g->pSommet[tempArc->sommet]->couleur != 'N')
            {
                longueurArcMinimum = tempArc->poids;
                arcMinimum = tempArc;
                printf("L'arc de %d vers %d est plus long\n",sommet_actuel->numero,arcMinimum->sommet);

            }
            tempArc = tempArc->arc_suivant;
        }
        if (longueurArcMinimum != -1) {
            printf("L'arc %d a l'arc le plus long : %d\n",arcMinimum->sommet,longueurArcMinimum);
            sommet_actuel->couleur = 'N';
            printf("Fin de la visite de %d\n", sommet_actuel->numero);
            sommet_actuel = g->pSommet[arcMinimum->sommet];
            boucleDFSdijkstra(sommet_actuel,g);
        }
        else{
            tempArc = NULL;
            printf("Ce sommet n'a pas d'arc\n");
        }
    }
    sommet_actuel->couleur = 'N';
}

void ParcoursDijkstra(int depart, int arrivee, Graphe * graphe){
    pSommet sommet_actuel=graphe->pSommet[depart];
    sommet_actuel->distance=0; // car c'est le premier sommet (le départ)
    boucleDFSdijkstra(sommet_actuel,graphe);
    printLongestPath(graphe,depart,arrivee);
}

int precedences(){
    Graphe * g;
    int depart, arrivee;
    g=lireGraphePrecedence("../precedences/precedences.txt");
    printf("Entrez le sommet de départ : ");
    scanf("%d",&depart);
    printf("Entrez le sommet d'arrivée : ");
    scanf("%d",&arrivee);
    ParcoursDijkstra(depart,arrivee,g);
    return 0;
}

