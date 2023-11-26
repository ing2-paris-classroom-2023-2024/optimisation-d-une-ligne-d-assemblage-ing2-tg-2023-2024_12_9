#include "structure.arfi.h"

t_s initSommet(char *nom, int numero) {
    t_s S;
    S.nom= malloc(sizeof(char)* strlen(nom)+1);
    strcpy(S.nom, nom);
    S.numero= numero;

    return S;
}

void initGraphe(int ordre, t_graphe *graphe) {

    graphe->ordre = ordre;

    graphe->matrice = malloc(ordre * sizeof(int*)); //colonnes

    for (int i = 0; i < ordre; i++) {
        graphe->matrice[i] = malloc(ordre * sizeof(int)); //lignes
    }

    graphe->Sommetab = malloc(ordre * sizeof(t_s));
}

void recupFichier(t_graphe *graphe) {

    char nom[100];
    int numero = 0;

    FILE *fc = fopen("../fichierTP1.txt", "r");
    if (fc != NULL) {

        fscanf(fc, "%d", &graphe->ordre);
        initGraphe(graphe->ordre, graphe);

        for (int j = 0; j < graphe->ordre; j++) {
            fscanf(fc, "%d %d %d %d %d %d %d", &(graphe->matrice[0][j]), &(graphe->matrice[1][j]),
                   &(graphe->matrice[2][j]), &(graphe->matrice[3][j]), &(graphe->matrice[4][j]),
                   &(graphe->matrice[5][j]), &(graphe->matrice[6][j]));
        }


        for (int i = 0; i < graphe->ordre; i++) {
            fgets(nom, 100, fc);
            graphe->Sommetab[i] = initSommet(nom, numero);

        }


        fclose(fc);
    }
}


void affichagedonnees(t_graphe *graphe) {
    printf("%d", graphe->ordre);

    for (int x = 0; x < graphe->ordre; x++) {
        printf("\n");

        for (int y = 0; y < graphe->ordre; y++) {
            printf("%d", graphe->matrice[y][x]);
        }
    }

    printf("\n\nVOICI LES JEUX D'INFLUENCE DES PERSONNES :");


    for (int i = 0; i < graphe->ordre; i++) {

        printf("%s", graphe->Sommetab[i].nom);
    }
}


int main() {

    t_graphe graphe;

    recupFichier(&graphe);

    affichagedonnees(&graphe);


    return 0;
}