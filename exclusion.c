//
// Created by audri on 24/11/2023.
//

#include "exclusion.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 40  // Estimation du nombre maximum de sommets

// Structure pour représenter un graphe
struct Graph {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
};

// Initialiser le graphe
void initGraph(struct Graph* g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++)
        for (int j = 0; j < numVertices; j++)
            g->adjMatrix[i][j] = 0;
}

// Ajouter une arête au graphe
void addEdge(struct Graph* g, int u, int v) {
    g->adjMatrix[u][v] = 1;
    g->adjMatrix[v][u] = 1;
}

// Vérifier si la couleur peut être attribuée au sommet
int isSafe(int v, struct Graph* g, int color[], int c) {
    for (int i = 0; i < g->numVertices; i++)
        if (g->adjMatrix[v][i] && c == color[i])
            return 0;
    return 1;
}

// Fonction d'aide pour la coloration
int graphColoringUtil(struct Graph* g, int m, int color[], int v) {
    if (v == g->numVertices)
        return 1;

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, g, color, c)) {
            color[v] = c;

            if (graphColoringUtil(g, m, color, v + 1) == 1)
                return 1;

            color[v] = 0;
        }
    }

    return 0;
}

// Fonction pour colorer le graphe
void graphColoring(struct Graph* g, int m, int color[]) {
    for (int i = 0; i < g->numVertices; i++)
        color[i] = 0;

    if (graphColoringUtil(g, m, color, 0) == 0) {
        printf("Solution n'existe pas\n");
        return;
    }
}

// Lire le fichier et construire le graphe
void buildGraphFromFile(struct Graph* g, const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int u, v;
    int maxVertex = 0;
    while (fscanf(file, "%d %d", &u, &v) != EOF) {
        addEdge(g, u, v);
        if (u > maxVertex) maxVertex = u;
        if (v > maxVertex) maxVertex = v;
    }
    g->numVertices = maxVertex + 1;

    fclose(file);
}

// Affichage des stations
void printStations(int color[], int numVertices) {
    int stationNumber = 1;
    int stationFound;

    do {
        stationFound = 0;
        printf("Station %d: ", stationNumber);
        for (int i = 0; i < numVertices; i++) {
            if (color[i] == stationNumber) {
                printf("%d ", i);
                stationFound = 1;
            }
        }
        if (stationFound) {
            printf("\n");
            stationNumber++;
        }
    } while (stationFound);
}

int main() {
    struct Graph g;
    initGraph(&g, MAX_VERTICES);

    buildGraphFromFile(&g, "welsh.txt"); // Remplacez par le chemin de votre fichier

    int color[MAX_VERTICES];
    graphColoring(&g, MAX_VERTICES, color); // Utilisez MAX_VERTICES comme estimation du nombre de couleurs

    printStations(color, g.numVertices);
    return 0;
}
