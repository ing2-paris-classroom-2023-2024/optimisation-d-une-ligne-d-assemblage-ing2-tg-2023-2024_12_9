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
    int caractere;

    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere == '\n') {
            taille++;
        }
    }
    fseek(fichier, 0, SEEK_SET);
    // Allocation dynamique pour le tableau de tâche
    liste->tache = malloc(taille * sizeof(tache));
    liste->taille = taille;
    printf("Taille : %d\n", taille);
    char ligne[100];
    int i = 0;
    while (fgets(ligne, 100, fichier) != NULL)
    {
        char *token = strtok(ligne, " ");
        liste->tache[i].numero = malloc(sizeof(int));
        liste->tache[i].tailleNum = 1;
        liste->tache[i].numero[0] = (int) atoi(token);
        token = strtok(NULL, " ");
        liste->tache[i].temps = atof(token) * 1000;
        i++;
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
    tache t;
    t.tailleNum = t1->tailleNum + t2->tailleNum;
    t.numero = calloc(t.tailleNum, sizeof(int));

    if (t.tailleNum == 1)
    {
        t.numero[0] = t1->numero[0];
    }
    else
    {
        for (int i = 0; i < t1->tailleNum; ++i)
        {
            t.numero[i] = t1->numero[i];
        }
    }

    if (t2->tailleNum == 1)
    {
        t.numero[t1->tailleNum] = t2->numero[0];
    }
    else
    {
        for (int i = 0; i < t2->tailleNum; ++i)
        {
            t.numero[t1->tailleNum + i] = t2->numero[i];
        }
    }
    t.temps = t1->temps + t2->temps;
    free(t1->numero);
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
    while (verifliste(liste->tache, liste->taille, tempsConv))
    {
        if ((liste->tache[0].temps + liste->tache[compteur].temps) <= tempsConv)
        {
            fusiontache(&liste->tache[0], &liste->tache[compteur]);

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
