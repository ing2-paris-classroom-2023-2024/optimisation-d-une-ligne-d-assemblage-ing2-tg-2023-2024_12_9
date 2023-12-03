
#include <stdio.h>
#include <stdlib.h>

#define MAX 40  // Estimation du nombre maximum de sommets

// Structure pour représenter un graphe
struct Graph {
    int Matrice[MAX][MAX];
    int nb_sommets;
};

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
    g->nb_sommets = sommet_max + 1;

    fclose(file);
}

// Affichage des stations
void affichage_stations(int couleur[], int nb_sommets) {
    int numero_station = 1;
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
        if (station_existente) {
            printf("\n");
            numero_station++;
        }
    } while (station_existente);
}

int main() {
    struct Graph g;
    initGraph(&g, MAX);

    Construire_Graph(&g, "welsh.txt"); // Remplacez par le chemin de votre fichier

    int color[MAX];
    graphColoring(&g, MAX, color); // Utilisez MAX_VERTICES comme estimation du nombre de couleurs

    affichage_stations(color, g.nb_sommets);
    return 0;
}
