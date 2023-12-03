
#include "exclusion.h"

// Initialiser le graphe
void initGraph(struct Graph* g, int nb_sommet) {
    g->nb_sommets = nb_sommet;
    for (int i = 0; i < nb_sommet; i++)
        for (int j = 0; j < nb_sommet; j++)
            g->Matrice[i][j] = 0;
}

// Ajouter une arête au graphe
void ajouter_arrete(struct Graph* g, int u, int v) {
    g->Matrice[u][v] = 1;
    g->Matrice[v][u] = 1;
}

// Vérifier si la couleur peut être attribuée au sommet
int Verification(int v, struct Graph* g, int couleur[], int c) {
    for (int i = 0; i < g->nb_sommets; i++)
        if (g->Matrice[v][i] && c == couleur[i])
            return 0;
    return 1;
}

// Fonction d'aide pour la coloration
int graph_Coloration(struct Graph* g, int m, int couleurs[], int v) {
    if (v == g->nb_sommets)
        return 1;

    for (int c = 1; c <= m; c++) {
        if (Verification(v, g, couleurs, c)) {
            couleurs[v] = c;

            if (graph_Coloration(g, m, couleurs, v + 1) == 1)
                return 1;

            couleurs[v] = 0;
        }
    }

    return 0;
}

// Fonction pour colorer le graphe
void graphColoring(struct Graph* g, int m, int couleurs[]) {
    for (int i = 0; i < g->nb_sommets; i++)
        couleurs[i] = 0;

    if (graph_Coloration(g, m, couleurs, 0) == 0) {
        printf("Solution n'existe pas\n");
        return;
    }
}

// Lire le fichier et construire le graphe
void Construire_Graph(struct Graph* g, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int u, v;
    int sommet_max = 0;
    while (fscanf(file, "%d %d", &u, &v) != EOF) {
        ajouter_arrete(g, u, v);
        if (u > sommet_max) sommet_max = u;
        if (v > sommet_max) sommet_max = v;
    }


    // Partie faite par Mateo (verification de l'existance des sommets)
    int tableauExiste[sommet_max];
    for (int i = 0; i < sommet_max; i++) {
        tableauExiste[i] = 0;
    }
    for (int i = 0; i < sommet_max; i++) {
        for (int j = 0; j < sommet_max; j++) {
            if (g->Matrice[i][j] == 1) {
                tableauExiste[i] = 1;
                tableauExiste[j] = 1;
            }
        }
    }
    int compteur = 0;
    for (int i = 0; i < sommet_max; i++) {
        if (tableauExiste[i] == 1) {
            compteur++;
        }
    }
    // Fin de la partie faite par Mateo
    g->nb_sommets = sommet_max;



    fclose(file);
}

// Affichage des stations
void affichage_stations(int couleur[], int nb_sommets , int ***tab , int *nX , int *nY) {
    int numero_station = 1;
    int compteur = 0;
    int station_existente;
    do {
        station_existente = 0;
        printf("Station %d: ", numero_station);
        for (int i = 0; i < nb_sommets; i++) {
            if (couleur[i] == numero_station) {
                printf("%d ", i);
                station_existente = 1;
            }
        }
        printf("station existante : %d\n", station_existente);
        if (station_existente) {
            printf("\n");
            numero_station++;
        }
        compteur++;
    } while (station_existente);
    numero_station = 1;
    *tab = calloc(compteur, sizeof(int*));
    for (int i = 0; i < compteur; i++) {
        (*tab)[i] = calloc(nb_sommets, sizeof(int));
    }
    do {
        station_existente = 0;
        for (int i = 0; i < nb_sommets; i++) {
            if (couleur[i] == numero_station) {
                station_existente = 1;
                (*tab)[numero_station - 1][i] = i;
            }
        }
        if (station_existente){
            numero_station++;
        }
    } while (station_existente);
    // affichage couleur
    for (int i = 0; i < compteur; i++) {
        for (int j = 0; j < nb_sommets; j++) {
            printf("%d ", (*tab)[i][j]);
        }
        printf("\n");
    }
    *nX = compteur;
    *nY = nb_sommets;
}


