//
// Created by audri on 24/11/2023.
//

#include "temps_de_cycle.h"

// fonction qui remplie la liste de tâche à partir d'un fichier
void remplirTache(listeTache *liste, char *nomFichier)
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
    liste->tache = calloc(taille, sizeof(tache));
    liste->taille = taille;
    printf("Taille : %d\n", taille);

    // Lire les données avec fscanf
    for (int i = 0; i < taille; ++i)
    {
        if (fscanf(fichier, "%d %f", &numero, &temps) == 2)
        {
            liste->tache[i].numero = calloc(1, sizeof(int));
            liste->tache[i].tailleNum = 1;
            liste->tache[i].numero[0] = numero;
            liste->tache[i].temps = temps * 1000;
        }
        else
        {
            // Gestion d'une erreur de lecture
            printf("Erreur lors de la lecture des données du fichier\n");
            // Vous pouvez choisir de quitter la fonction ou de gérer autrement l'erreur.
            exit(EXIT_FAILURE);
        }
    }

    fclose(fichier);
}

int remplir_temps_de_cycle(char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        exit(EXIT_FAILURE);
    }
    int a;
    char l[100];
    fseek(fichier, 0, SEEK_SET);
    fgets(l, 100, fichier);
    fclose(fichier);
    a = atoi(l);
    return a;
}

// fonction qui affiche la liste de tâche
void afficherTache(listeTache *liste)
{

    for (int i = 0; i < liste->taille; i++)
    {
        printf("Machine : %d Tache : ",i);
        for (int j = 0; j < liste->tache[i].tailleNum; j++)
        {
            printf("%d", liste->tache[i].numero[j]);
            if (j != liste->tache[i].tailleNum - 1)
            {
                printf(" -> ");
            }
        }
        printf(" Temps : %d\n", liste->tache[i].temps);
    }
}

// tri fusion pour le temps de cycle
void fusion(tache *tab, int deb, int milieu, int fin)
{
    int i1 = deb;
    int i2 = milieu + 1;
    int i;
    tache *tab2;

    // Allocation dynamique pour le tableau temporaire
    tab2 = malloc((fin - deb + 1) * sizeof(tache));

    for (i = 0; i <= fin - deb; i++)
    {
        if (i1 <= milieu && (i2 > fin || tab[i1].temps < tab[i2].temps))
        {
            tab2[i] = tab[i1];
            i1++;
        }
        else
        {
            tab2[i] = tab[i2];
            i2++;
        }
    }
    // Copie les éléments triés de tab2 à tab
    for (i = 0; i <= fin - deb; i++)
    {
        tab[deb + i] = tab2[i];
    }

    // Libération de la mémoire allouée pour tab2
    free(tab2);
}

// tri par Insersion pour le temps de cycle
void triInsertion(tache *tab, int taille)
{
    int i, j;
    tache temp;
    for (i = 1; i < taille; i++)
    {
        temp = tab[i];
        j = i - 1;
        while (j >= 0 && tab[j].temps > temp.temps)
        {
            tab[j + 1] = tab[j];
            j--;
        }
        tab[j + 1] = temp;
    }
}

int verifliste(tache *tab, int taille, int temps)
{
    int i;
    if (taille == 1)
    {
        return 0;
    }
    else
    {
        if (tab[0].temps + tab[1].temps > temps)
        {
            return 0;
        }
        return 1;
    }
    return 1;
}

void fusiontache(tache *t1, tache *t2)
{
    printf("test1\n");
    tache t;
    t.tailleNum = t1->tailleNum + t2->tailleNum;
    t.numero = calloc(t.tailleNum, sizeof(int));
    printf("test2\n");
    /*
    if (t.tailleNum == 1)
    {
        printf("test2.5\n");
        t.numero[0] = t1->numero[0];
        printf("test2.5\n");
    }
    else
    {*/
        printf("test2.6\n");
        for (int i = 0; i < t1->tailleNum; ++i)
        {
            t.numero[i] = t1->numero[i];
        }
    //}
    printf("test3\n");
        /*
    if (t2->tailleNum == 1)
    {
        t.numero[t1->tailleNum] = t2->numero[0];
    }
    else
    {*/
        for (int i = 0; i < t2->tailleNum; ++i)
        {
            t.numero[t1->tailleNum + i] = t2->numero[i];
        }
    //}
    printf("test4\n");
    t.temps = t1->temps + t2->temps;
    printf("test5\n");
    //free(t1->numero);
    printf("test6\n");
    // Ne pas libérer t2->numero ici, car t1->numero pointe déjà vers le même tableau.
    // free(t2->numero);
    // free(t2);

    *t1 = t;
}



void tempsdecycle(listeTache *liste, int temps)
{
    int compteur = liste->taille - 1;
    int tempsConv = temps * 1000;
    printf("\n");
    printf("Temps : %d\n", temps);
    triInsertion(liste->tache, liste->taille);
    printf("test\n");
    while (verifliste(liste->tache, liste->taille, tempsConv))
    {
        printf("test\n");
        if ((liste->tache[0].temps + liste->tache[compteur].temps) <= tempsConv)
        {
            printf("test\n");
            fusiontache(&liste->tache[0], &liste->tache[compteur]);
            printf("test\n");
            // Copie des éléments suivants dans le tableau
            if (compteur != liste->taille - 1)
            {
                for (int i = compteur; i < liste->taille; i++)
                {
                    liste->tache[i] = liste->tache[i + 1];
                }
            }
            liste->taille--;
            compteur = liste->taille - 1;
            // Réallocation avec vérification
            tache *temp = realloc(liste->tache, sizeof(tache) * liste->taille);
            if (temp == NULL)
            {
                // Gestion de l'échec de la réallocation
                // (optionnel, dépend de la logique de votre application)
                // Vous pourriez choisir de quitter la fonction ou de gérer autrement l'erreur.
                printf("Erreur de reallocation de memoire\n");
                exit(EXIT_FAILURE);
            }
            liste->tache = temp;
            triInsertion(liste->tache, liste->taille);
        }
        else
        {
            compteur--;
        }
    }
}

void contrainte(listeTache *l1, int *tab, listeTache *l2)
{
    int taille = 0;
    int compteur = 0;
    while (tab[taille] != 0)
    {
        taille++;
    }

    printf("test\n");
    l2->tache = malloc(taille * sizeof(tache));
    l2->taille = taille;
    printf("test\n");

    for (int i = 0; i < l1->taille; ++i)
    {
        for (int j = 0; j < taille; ++j)
        {
            if (l1->tache[i].numero[0] == tab[j])
            {
                // Allocation de mémoire pour la nouvelle tâche dans l2
                l2->tache[compteur].numero = malloc(l1->tache[i].tailleNum * sizeof(int));
                l2->tache[compteur].tailleNum = l1->tache[i].tailleNum;
                // Copie des données de la tâche de l1 à l2
                l2->tache[compteur].numero[0] = l1->tache[i].numero[0];
                l2->tache[compteur].temps = l1->tache[i].temps;
                compteur++;
            }
        }
    }
}



// fonction qui ajoute une ligne à un tableau entrer en paramètre

// Fonction qui ajoute une ligne à un tableau passé en paramètre
void ajouterLigne(int ***tab, int *taille,int tailletab, listeTache *l)
{
    int tailletemp = *taille + l->taille;
    printf("tailletemp : %d\n", tailletemp);
        int **temp = realloc(*tab, sizeof(int*) * tailletemp);
        if (temp == NULL)
        {
            // Gestion de l'échec de la réallocation
            printf("Erreur de réallocation de mémoire\n");
            exit(EXIT_FAILURE);
        }

        *tab = temp;

    // Copie des nouvelles lignes
    for (int i = 0; i < l->taille; ++i)
    {
        (*tab)[*taille + i] = malloc(sizeof(int) * tailletab);

        if ((*tab)[*taille + i] == NULL)
        {
            // Gestion de l'échec de la réallocation
            printf("Erreur de réallocation de mémoire\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < l->tache[i].tailleNum; ++j)
        {
            (*tab)[*taille + i][j] = l->tache[i].numero[j];
        }
    }

    *taille += l->taille;
}
void libererTache(listeTache *liste)
{
    // Libération de la mémoire pour chaque tâche
    for (int i = 0; i < liste->taille; ++i)
    {
        free(liste->tache[i].numero);
    }

    // Libération de la mémoire pour le tableau de tâches
    free(liste->tache);

    // Réinitialisation de la structure listeTache
    liste->tache = NULL;
    liste->taille = 0;
}

void initilisationtempscycle(tableauMemoire *tab)

{
    int **tab2 = malloc(sizeof(int*));
    int taille2 = 0;
    listeTache liste = {NULL, 0};
    listeTache liste2 = {NULL, 0};
    printf("test\n");
    remplirTache(&liste, "../operation/operations.txt");
    printf("test\n");
   //afficherTache(&liste);
    for (int i = 0; i < tab->nombreMachines; ++i)
    {
            contrainte(&liste , tab->tableauPrecedences[i] , &liste2);
            printf("test\n");
            printf("\n");
            //afficherTache(&liste2);
            //printf("Temps de cycle : %d\n", remplir_temps_de_cycle("../temps/temps_cycle.txt"));
            printf("test6\n");
            tempsdecycle(&liste2, remplir_temps_de_cycle("../temps/temps_cycle.txt"));
            printf("test7\n");
            afficherTache(&liste2);
            ajouterLigne(&tab2, &taille2,tab->nombreTaches, &liste2);
            printf("taille2 : %d\n", liste2.taille);
            liste2 = (listeTache) {NULL, 0};
    }

    for (int i = 0; i < taille2; ++i)
    {
        for ( int j = 0; j < tab->nombreTaches; ++j)
        {
            if (tab2[i][j] > 1000)
            {
                tab2[i][j] = 0;
            }
        }
    }
    tab->tableauPrecedences = tab2;
    tab->nombreMachines = taille2;
    tab->nombreTaches = 0;
    for(int i = 0; i < tab->nombreMachines; i++){
        int compteur = 0;
        while(tab->tableauPrecedences[i][compteur] != 0){
            compteur++;
        }
        if (compteur > tab->nombreTaches)tab->nombreTaches = compteur;
    }
    afficherTache(&liste);
    printf("test\n");
    afficherTache(&liste2);
    // libération de la mémoire
    printf("taille : %d\n", liste.taille);
    printf("taille : %d\n", liste2.taille);
    libererTache(&liste);
    for (int i = 0; i < liste.taille; ++i)
    {
        if (liste.tache[i].numero != NULL && liste.tache[i].tailleNum != 0)
        {
            printf("test\n");
            free(liste.tache[i].numero);
            liste.tache[i].numero = NULL;
        }
    }
    free(liste.tache);
    liste.tache = NULL;
    free(liste2.tache);
}