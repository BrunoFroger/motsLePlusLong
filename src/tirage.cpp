//-----------------------------------
//
//      tirage.cpp
//
//-----------------------------------
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "../inc/variables.hpp"

char listeVoyelles[6] = { 'A', 'E', 'I', 'O', 'U', 'Y' };
char listeConsonnes[20] = { 'B', 'C', 'D', 'F', 'G', 'H',
                           'J', 'K', 'L', 'M', 'N', 'P', 
                           'Q', 'R', 'S', 'T', 'V', 'W', 
                           'X', 'Z' };
char lettres[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 
    'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' 
};
int nbLettres[] = {
    9, 2, 2, 3, 15, 2, 2, 2, 8, 1, 1, 5, 3, 6, 6, 
    2, 1, 6, 6, 6, 6, 2, 1, 1, 1, 1 
};

char JeuDeLettres[100];
int nbVoyelles = 0;
int nbConsonnes = 0;

//-----------------------------------
//
//      construitJeuDeLettres
//
//-----------------------------------
void construitJeuDeLettres(void){
    int index = 0;
    int nb;
    for (int i =0 ; i < 26 ; i++){
        //printf("generation de %d %c\n", nbLettres[i], lettres[i]);
        for (int j = 0 ; j < nbLettres[i] ; j++){
            JeuDeLettres[index++] = lettres[i];
        }
    }
}

//-----------------------------------
//
//      lettreRandom
//
//-----------------------------------
char lettreRandom(){
    int numLettre;
    bool isVoyelle=false;
    numLettre = rand() % 100;
    for (int i = 0 ; i < 6 ; i++){
        if (JeuDeLettres[numLettre] == listeVoyelles[i]){
            isVoyelle=true;
        }
    }
    if (isVoyelle) nbVoyelles++; else nbConsonnes++;
    return JeuDeLettres[numLettre];
}

//-----------------------------------
//
//      genereTirage
//
//-----------------------------------
void genereTirage(void){
    construitJeuDeLettres();
    //return;
    srand(time(NULL));
    bool tirageValide = false;
    while (!tirageValide){
        nbVoyelles=0;
        nbConsonnes=0;
        for (int i = 0 ; i < nbLettresJeu ; i++){
            char lettre = lettreRandom();
            tirage[i] = lettre;
        }
        //printf("%d voyelles et %d consonnes dans ce tirage\n", nbVoyelles, nbConsonnes);
        if (nbVoyelles > nbLettresJeu / 4) {
            if (nbVoyelles < nbLettresJeu / 2){
                tirageValide = true;
            }
        }
    }
}

//-----------------------------------
//
//      afficheTirage
//
//-----------------------------------
void afficheTirage(char *tirage){
    char tmp[50] = "";
    int idxTmp = 0;
    int tailleZEoneAffichage;
    int nbBlancs, tailleTirage;
    tailleTirage = strlen(tirage) * 2;
    tailleZEoneAffichage = tailleTirage + 10;
    nbBlancs = 6;

    //printf("0123456789012345678901234567890123456789\n");
    if (strlen(tirage) != 0){
        // affichage premiere ligne de '-'
        for (int i = 0 ; i < tailleZEoneAffichage + 2 ; i++){
            if ((i != 0) && (i < tailleZEoneAffichage + 1)){
                printf("-");
            } else {
                printf("+");
            }
        }
        printf("\n");
        printf("|%*s%-*s%*s|\n", nbBlancs, " ", tailleTirage, "Tirage", nbBlancs - 2, " ");
        printf("|%*s|\n", tailleZEoneAffichage, " ");
        printf("|%*s", nbBlancs, " ");
        for (int i = 0 ; i < strlen(tirage) ; i++){
            tmp[idxTmp++] = tirage[i];
            tmp[idxTmp++] = ' ';
        }
        tmp[idxTmp] = '\0';
        printf("%s", tmp);
        printf("%*s|\n", nbBlancs - 2, " ");
        printf("|%*s|\n", tailleZEoneAffichage, " ");
        // affichage dernière ligne de '-'
        for (int i = 0 ; i < tailleZEoneAffichage + 2 ; i++){
            if ((i != 0) && (i < tailleZEoneAffichage + 1)){
                printf("-");
            } else {
                printf("+");
            }
        }
    }
    printf("\n");
}