#include <stdio.h>

// Structure pour représenter une tâche avec son temps
typedef struct {
    int temps;
    int machine;
} Tache;

void triFusionTaches(int i, int j, Tache tab[], Tache tmp[]) {
    if (j <= i) {
        return;
    }

    int m = (i + j) / 2;

    triFusionTaches(i, m, tab, tmp);
    triFusionTaches(m + 1, j, tab, tmp);

    int pg = i;
    int pd = m + 1;
    int c;

    for (c = i; c <= j; c++) {
        if (pg == m + 1) {
            tmp[c] = tab[pd];
            pd++;
        } else if (pd == j + 1) {
            tmp[c] = tab[pg];
            pg++;
        } else if (tab[pg].temps < tab[pd].temps) {
            tmp[c] = tab[pg];
            pg++;
        } else {
            tmp[c] = tab[pd];
            pd++;
        }
    }

    for (c = i; c <= j; c++) {
        tab[c] = tmp[c];
    }
}

void associerTachesAMachine(Tache tab[], int nbr, int tempsCycle) {
    int i = 0;
    int j = nbr - 1;

    while (i < j) {
        int somme = tab[i].temps + tab[j].temps;

        if (somme < tempsCycle) {
            printf("Taches %d et %d sont associees. Nouveau temps de cycle : %d\n", tab[i].temps, tab[j].temps, somme);

            // Associer les tâches à une machine (ici, on stocke la machine dans la structure de la tâche)
            tab[i].machine = i + 1;
            tab[j].machine = i + 1;

            i++;
            j--;
        } else {
            printf("Sinon on recommence pour le premier et l’avant-dernier.\n");
            j--; // Recommencer avec le premier et l'avant-dernier
        }
    }

    // Dernière tâche si elle n'a pas été traitée
    if (i == j) {
        printf("Tache %d est associee seule. Temps de cycle : %d\n", tab[i].temps, tab[i].temps);
        tab[i].machine = i + 1;
    }
}

int calculerNombreMachines(Tache tab[], int nbr) {
    int nombreMachines = 0;

    for (int i = 0; i < nbr; i++) {
        if (tab[i].machine > nombreMachines) {
            nombreMachines = tab[i].machine;
        }
    }

    return nombreMachines;
}

int main() {
    int nbr, i;
    Tache tab[100], tmp[100];
    int tempsCycle;

    printf("Entrez le nombre d'elements dans le tableau: ");
    scanf("%d", &nbr);

    printf("Entrez %d temps de taches : ", nbr);
    for (i = 0; i < nbr; i++) {
        scanf("%d", &tab[i].temps);
        tab[i].machine = 0;
    }

    printf("Entrez le temps de cycle : ");
    scanf("%d", &tempsCycle);

    triFusionTaches(0, nbr - 1, tab, tmp);
    associerTachesAMachine(tab, nbr, tempsCycle);

    printf("\nTableau trie et associe a une machine : \n");
    for (i = 0; i < nbr; i++) {
        printf("Tache %d - Machine %d\n", tab[i].temps, tab[i].machine);
    }

    int nombreMachines = calculerNombreMachines(tab, nbr);
    printf("\nNombre de machines necessaires : %d\n", nombreMachines);

    return 0;
}
