
#include "exclusion.h"

void triInsertionint(int *tab, int taille)
{
    int i, j;
    int temp;
    for (i = 1; i < taille; i++)
    {
        temp = tab[i];
        j = i - 1;
        while (j >= 0 && tab[j] < temp)
        {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = temp;
    }
}

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
    g->nb_sommets = sommet_max + 1;
    fclose(file);
}

// Fonction qui ajoute une ligne à un tableau passé en paramètre
void ajouterl(int ***tab, int *tailleY,int tailleX, int ***tab2 , int *tailleY2, int tailleX2)
{
    int tailletemp = *tailleY + *tailleY2;
    int **temp = realloc(*tab, sizeof(int*) * tailletemp);
    if (temp == NULL)
    {
        // Gestion de l'échec de la réallocation
        printf("Erreur de réallocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    *tab = temp;

    // Copie des nouvelles lignes
    for (int i = 0; i < *tailleY2; ++i)
    {
        (*tab)[*tailleY + i] = calloc(tailleX, sizeof(int));

        if ((*tab)[*tailleY + i] == NULL)
        {
            // Gestion de l'échec de la réallocation
            printf("Erreur de réallocation de mémoire\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < tailleX; ++j)
        {
            (*tab)[*tailleY + i][j] = (*tab2)[i][j];
        }
    }

    *tailleY += *tailleY2;
}
void remplirmem(tableauMemoire *tab, char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }

    // Compter le nombre de lignes
    int taille = 0;
    int numero;
    float temps;

    while (fscanf(fichier, "%d %f", &numero, &temps) == 2)
    {
        taille++;
    }

    fseek(fichier, 0, SEEK_SET);

    // Allocation dynamique pour le tableau de tâches
    int **tabtemps = malloc(sizeof(int*));
    tabtemps[0] = malloc(taille * sizeof(int*));
    tab->nombreTaches = taille;
    tab->nombreMachines = 1;
    // Lire les données avec fscanf
    for (int i = 0; i < taille; ++i)
    {
        if (fscanf(fichier, "%d %f", &numero, &temps) == 2)
        {
             tabtemps[0][i] = numero;
        }
        else
        {
            // Gestion d'une erreur de lecture
            printf("Erreur lors de la lecture des données du fichier\n");
            // Vous pouvez choisir de quitter la fonction ou de gérer autrement l'erreur.
            exit(EXIT_FAILURE);
        }
    }
    tab->tableauPrecedences = tabtemps;
    fclose(fichier);
}
int verifmmC(tableauMemoire *tab, int couleur[])
{
    int test = 1;
    int index = 0, taille = 0;
    int **tab2 = malloc(sizeof(int*));
    if (tab->tableauPrecedences == NULL)
    {
        remplirmem(tab, "../operation/operations.txt");
    }
    int tabtemps[tab->nombreTaches];
    for (int k = 0; k < tab->nombreMachines; k++)
    {
        index = 0;
        for (int i = 0; i < tab->nombreTaches; i++)
        {
            tabtemps[i] = -1;
        }

        for (int i = 0; i < tab->nombreTaches; i++)
        {
            for (int j = 0; j <tab->nombreTaches; ++j)
            {
                //printf(" %d", tab->tableauPrecedences[2][j]);
                if ((couleur[tab->tableauPrecedences[k][i]] == tabtemps[j]) && (tab->tableauPrecedences[k][i] != 0))
                {
                    test = 0;
                }
            }
            if (test && (tab->tableauPrecedences[k][i] != 0))
            {
                tabtemps[index] = couleur[tab->tableauPrecedences[k][i]];
                index++;
            }
            test = 1;
        }
        int **tabtemps2 = calloc(index, sizeof(int*));
        for (int i = 0; i < index; i++)
        {
            tabtemps2[i] = calloc(tab->nombreTaches, sizeof(int));
        }
        index = 0;
        while (tabtemps[index] != -1)
        {
            for (int i = 0; i < tab->nombreTaches; i++)
            {
                if (tabtemps[index] == couleur[tab->tableauPrecedences[k][i]])
                {
                    tabtemps2[index][i] = tab->tableauPrecedences[k][i];
                }
            }
            index++;
        }
        ajouterl(&tab2, &taille, tab->nombreTaches, &tabtemps2, &index, tab->nombreTaches);
        // free du tableau de temps 2
        for (int i = 0; i < index; i++)
        {
            free(tabtemps2[i]);
        }
        free(tabtemps2);
    }
    for (int i = 0; i < taille; i++)
    {
        triInsertionint(tab2[i], tab->nombreTaches);
    }
    // free du tableau précédence
    for (int i = 0; i < tab->nombreMachines; i++)
    {
        free(tab->tableauPrecedences[i]);
    }
    free(tab->tableauPrecedences);
    tab->tableauPrecedences = tab2;
    tab->nombreMachines = taille;
    tab->nombreTaches = 0;
    for(int i = 0; i < tab->nombreMachines; i++){
        int compteur = 0;
        while(tab->tableauPrecedences[i][compteur] != 0){
            compteur++;
        }
        if (compteur > tab->nombreTaches)tab->nombreTaches = compteur+1;
    }
    return 0;
}

// Affichage des stations
void affichage_stations(int couleur[], int nb_sommets) {
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
        if (station_existente) {
            printf("\n");
            numero_station++;
        }
        compteur++;
    } while (station_existente);

}


