//
// Created by audri on 24/11/2023.
//


#include "precedence.h"

int compteurNombreMachines(Graphe * graphe){
    int nombreMachines = 0;
    for(int i = 1; i < graphe->ordre+1; i++){
        // printf("Sommet %d : %d\n", graphe->pSommet[i]->numero, graphe->pSommet[i]->distance);
        if (graphe->pSommet[i]->existe == 0){
            // printf("Le sommet %d n'existe pas\n", graphe->pSommet[i]->numero);
        }
        if(graphe->pSommet[i]->distance > nombreMachines){
            nombreMachines = graphe->pSommet[i]->distance;
        }
    }
    printf("Nombre de machines : %d\n", nombreMachines);
    return nombreMachines;
}


Graphe * lireGraphePrecedence(char * nomFichier)
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

// ON PART PLUTÔT SUR UN BFS

Liste * CreerListe(pSommet sommet){
    pMaillon debut = (pMaillon) malloc(sizeof(struct Maillon));
    pMaillon fin = (pMaillon) malloc(sizeof(struct Maillon));
    Liste * Newliste = (Liste*) malloc(sizeof(Liste));
    Newliste->tete = (struct Maillon*) malloc(sizeof(struct Maillon*));
    Newliste->queue = (struct Maillon*) malloc(sizeof(struct Maillon*));
    debut->sommet = sommet;
    fin->sommet = sommet;
    Newliste->tete = debut;
    Newliste->queue = fin;
    Newliste->tete->suivant = NULL;
    Newliste->queue->suivant = NULL;
    Newliste->longueur = 1;
    return Newliste;
}

void EnfilerSommet(Liste * Liste, pSommet sommetAEnfiler){
    pMaillon temp = NULL;
    temp = Liste->tete;
    while (temp->suivant != NULL){
        // printf("temp = %d passe\n", temp->sommet->valeur);
        temp = temp->suivant;

    }
    // printf("temp = %d passe\n", temp->sommet->numero);
    pMaillon NewMaillon = (pMaillon) malloc(sizeof(struct Maillon));
    temp->suivant = NewMaillon;
    NewMaillon->sommet = sommetAEnfiler;
    NewMaillon->suivant = NULL;
    Liste->longueur++;
    // printf("Sommet %d enfile\n", sommetAEnfiler->numero);

}

int prochainPointDeDepart(Graphe * graphe){
    // printf("Entree dans la fonction prochainPointDeDepart\n");
    for(int i = 0; i < graphe->ordre; i++){
        if(graphe->pSommet[i]->existe == 1 && graphe->pSommet[i]->couleur == 'B'){
            return i;
        }
    }
    return -1;
}

void DefilerSommetBFS(Liste * Liste){
    // printf("Sommet %d defile\n", Liste->tete->sommet->numero);
    pMaillon temp = Liste->tete;
    Liste->longueur--;
    Liste->tete = temp->suivant;

    free(temp);
}



void affichageEnregistrementPrecedences(Graphe * graphe, tableauMemoire * tableau){

    int nombreMachines = compteurNombreMachines(graphe);
    tableau->nombreMachines = nombreMachines;

    // On compte le nombre de tâches qui existent

    int nombreTaches = 0;
    for(int i = 1; i < graphe->ordre+1; i++){
        if (graphe->pSommet[i]->existe == 1){
            nombreTaches++;
        }
    }

    tableau->nombreTaches = nombreTaches;




    // Initialisation du tableau, toutes les cases sont à 0
    int tailleTableauPrecedences = graphe->ordre;

    // printf("Ordre du graphe : %d\n", tailleTableauPrecedences);

    for(int i = 0; i < nombreMachines; i++){
        for(int j = 0; j < tailleTableauPrecedences; j++){
            tableau->tableauPrecedences[i][j] = 0;
        }
    }


    // printf("Initialisation terminee\n");
    // printf("Taille du tableau : %d\n", tailleTableauPrecedences);

    // On parcourt le graphe et on remplit le tableau de précédences
    for(int tache = 1; tache < tailleTableauPrecedences+1; tache++) {
        int machine = graphe->pSommet[tache]->distance;
        int placeDansLaMachine = 0;
        if (machine > 0){
            while (tableau->tableauPrecedences[machine-1][placeDansLaMachine] != 0){
                placeDansLaMachine++;
            }
            tableau->tableauPrecedences[machine-1][placeDansLaMachine] = tache;
            //printf("Tache %d assignee a la machine %d\n", tache, machine);
        }
    }


    // On affiche le tableau de précédences
    // printf("Affichage du tableau de precedences\n");
    for(int i = 0; i < nombreMachines; i++){
        printf("Machine %d : ", i);
        for(int j = 0; j < tailleTableauPrecedences; j++){
            if (tableau->tableauPrecedences[i][j] != 0) {
                printf("%d ", tableau->tableauPrecedences[i][j]);
            }
        }
        printf("\n");
    }

}

void parcoursBFS(Graphe* graphe)
{

    int sommet_initial = 1;
    /*
    printf("Entrez le sommet de depart : ");
    scanf("%d",&sommet_initial);
     */


    /* printf("Graphe ");

    if(graphe->orientation)
        printf("oriente ");
    else
        printf("non oriente ");

    printf("d'ordre = %d\n",graphe->ordre);
     */


    // printf("Couleur du sommet 12 : %c \n", graphe->pSommet[8]->couleur);
    // printf("Liste creee\n");
    do{
        // printf("Nouveau point de depart : %d\n", sommet_initial);
        pSommet sommetInitial = graphe->pSommet[sommet_initial];

        sommetInitial->distance = 1; // Ici la variable distance est utilisée pour stocker le numéro de la machine

        Liste * ListeBFS = CreerListe(sommetInitial);

        while (ListeBFS->longueur != 0){

            // printf("Debut analyse\n");
            // printf("Couleur du sommet a analyser : %c\n", ListeBFS->tete->sommet->couleur);
            pSommet sommet = ListeBFS->tete->sommet;

            sommet->couleur = 'N';

            // printf("Sommet analyse : %d \n", sommet->numero);
            pArc arc = sommet->arc;
            while (arc != NULL){


                // Ce qui va permettre de déterminer l'étape à laquelle la tâche va être assignée

                if(graphe->pSommet[arc->sommet]->distance < sommet->distance + 1){
                    graphe->pSommet[arc->sommet]->distance = sommet->distance + 1;
                    // printf("Nouvelle distance du sommet %d : %d\n", arc->sommet, graphe->pSommet[arc->sommet]->distance);
                }

                // printf("%d->%d \n", sommet->numero, arc->sommet);
                // printf("Couleur du sommet : %c\n", graphe->pSommet[arc->sommet]->couleur);
                if(graphe->pSommet[arc->sommet]->couleur == 'N'){
                    // printf("Le sommet est Noir\n");
                }
                else if(graphe->pSommet[arc->sommet]->couleur == 'G'){
                    // printf("Le sommet est Gris\n");
                }
                else if(graphe->pSommet[arc->sommet]->couleur == 'B'){
                    // printf("Le sommet est Blanc\n");
                    EnfilerSommet(ListeBFS, graphe->pSommet[arc->sommet]);
                    graphe->pSommet[arc->sommet]->couleur = 'G';

                }
                else{
                    printf("Erreur de couleur\n");
                    exit(-1);
                }
                arc = arc->arc_suivant;
                // printf("Sortie condition\n");

            }
            // printf("Fin de l'analyse\n");
            DefilerSommetBFS(ListeBFS);
            // printf("Elements de la liste: \n");
            // On affiche les éléments de la liste
            struct Maillon * temp = ListeBFS->tete;

            for(int i = 0; i < ListeBFS->longueur; i++){
                // printf("%d, ", temp->sommet->numero);
                temp = temp->suivant;
            }
            // printf("\n \n");

        }
        // printf("Fin du parcours\n");
        sommet_initial = prochainPointDeDepart(graphe);
    }while(prochainPointDeDepart(graphe) != -1);



}


void precedences(tableauMemoire * tableau){
    Graphe * g;
    g=lireGraphePrecedence("../precedences/precedences.txt");



    parcoursBFS(g);

    // Initialisation du tableau, toutes les cases sont à 0

    int ** tableauPrecedences = (int **) malloc(g->ordre * sizeof(int *));
    int tailleTableauPrecedences = g->ordre;
    // printf("Ordre du graphe : %d\n", tailleTableauPrecedences);
    for(int i = 0; i < tailleTableauPrecedences; i++){
        tableauPrecedences[i] = (int *) malloc(tailleTableauPrecedences * sizeof(int));
        for(int j = 0; j < tailleTableauPrecedences; j++){
            tableauPrecedences[i][j] = 0;
        }
    }
    printf("Affichage des precedences\n");
    tableau->tableauPrecedences = tableauPrecedences;
    affichageEnregistrementPrecedences(g, tableau);
}

