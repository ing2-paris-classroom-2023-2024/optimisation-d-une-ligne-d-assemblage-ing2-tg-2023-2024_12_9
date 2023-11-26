//
// Created by audri on 24/11/2023.
//

#include "menudelancement.h"

// Fonction blindée qui permet de lancer soit :
// - contrainte d'exclusion et de précédence
// - contrainte d'exclusion et temps de cycle
// - contrainte de précédence et temps de cycle et contrainte d'exclusion
// - quitter le programme
int menu_de_lancement()
{
    int choix = 0;
    printf("Bienvenue dans le menu de lancement du programme\n");
    printf("Veuillez choisir une option :\n");
    printf("1 - Contrainte d'exclusion et de precedence\n");
    printf("2 - Contrainte d'exclusion et temps de cycle\n");
    printf("3 - Contrainte de precedence et temps de cycle et contrainte d'exclusion\n");
    printf("4 - Quitter le programme\n");
    scanf("%d", &choix);
    switch (choix)
    {
        case 1:
            printf("Vous avez choisi la contrainte d'exclusion et de précédence\n");
            return 1;
            break;
        case 2:
            printf("Vous avez choisi la contrainte d'exclusion et temps de cycle\n");
            return 2;
            break;
        case 3:
            printf("Vous avez choisi la contrainte de précédence et temps de cycle et contrainte d'exclusion\n");
            return 3;
            break;
        case 4:
            printf("Vous avez choisi de quitter le programme\n");
            return 4;
            break;
        default:
            return 0;
            break;
    }
}
//bujifajbipsabuip