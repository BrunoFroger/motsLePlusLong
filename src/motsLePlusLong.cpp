//-----------------------------------
//
//      motsLePlusLong.cpp
//
//-----------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>

#include "../inc/variables.hpp"
#include "../inc/compareMots.hpp"
#include "../inc/analyseParametres.hpp"
#include "../inc/tirage.hpp"

#define MAX_SOLUTIONS       1000

int main(int argc, char **argv){

    char ligne[100];
    FILE *fichierMots;
    char listeMots[TAILLE_MAX_TIRAGE][MAX_SOLUTIONS][50];
    int nbMots[TAILLE_MAX_TIRAGE];

    printf("+----------------------------------------+\n");
    printf("|                                        |\n");
    printf("|           Mot le plus long             |\n");
    printf("|                                        |\n");
    printf("|          (c) B.Froger 2022             |\n");
    printf("|                                        |\n");
    printf("+----------------------------------------+\n");

    // init listeMots
    //printf("reset listeMots[%d][%d]\n", NB_LETTRES_TIRAGE, MAX_SOLUTIONS);
    for (int i = 0 ; i < TAILLE_MAX_TIRAGE ; i++){
        //printf("reset listeMots[%d]\n", i);
        nbMots[i] = 0;
        for(int j = 0 ; j < MAX_SOLUTIONS ; j++){
            //printf("\treset listeMots[%d][%d]\n", i, j);
            strcpy(listeMots[i][j], "");
        }
    }
    //return 0;
    //strcpy(nomFichierMots, "datas/liste_mots.txt");
    strcpy(nomFichierMots, "datas/ods6.txt");
    /*
    if (argc > 1 ){
        printf("Erreur de syntaxe : trop de parametres\n");
        return -1;
    }*/

    //generation du tirage ou recuperation du tirage en parametre
    if (argc > 1){
        analyseParametres(argc, argv);
    }

    if (strlen(tirage) == 0){
        genereTirage();
    }

    // test si fichier de mots valide
    fichierMots = fopen(nomFichierMots, "r");
    if (fichierMots == NULL){
        printf("ERREUR : imopssible d'ouvrir le fichier de mots %s\n", nomFichierMots);
        return -1;
    }

    printf("Tirage de %d lettres\n", nbLettresJeu);
    printf("Solution de %d lettres minimum\n", NB_LETTRES_MINI);
    printf("tirage = %s\n", tirage);
    afficheTirage(tirage);
    // recherche du nombre de mots pour chaque longeur (" à nbLettreJeu")

    int nbSolutions = 0;
    int numLigneFichier=0;
    while (!feof(fichierMots)){
        strcpy(ligne, "");
        fgets(ligne, 100, fichierMots);
        numLigneFichier++;
        if (strlen(ligne) != 0){
            if (compareMots(ligne, tirage)){
                //printf ("tirage %s : solution %s\n", tirage, ligne);
                nbSolutions++;
                int tailleMot = strlen(ligne);
                int idxTblMots = nbMots[tailleMot];
                strcpy(listeMots[tailleMot][idxTblMots], ligne);
                nbMots[tailleMot]++;
                if (strcmp(ligne, "zythums") == 0){
                    printf("sur ligne %d du fichier insertion de %s avec taille mot %d\n", numLigneFichier, ligne, tailleMot);
                }
            }
        }
    } 
    int total = 0;
    printf("+------------------------------+\n");
    printf("|     nombre de solutions      |\n");
    printf("+--------------+---------------+\n");
    printf("|  nb lettres  |  nb solutions |\n");
    printf("+--------------+---------------+\n");
    for (int i = 3 ; i <= nbLettresJeu ; i++){
        printf("|      %2d      |       %3d     |\n", i, nbMots[i]);
        total += nbMots[i];
    }
    printf("+--------------+---------------+\n");
    printf("|     Total    |      %4d     |\n", total);
    printf("+--------------+---------------+\n");

    if (afficheSolutions){
        // liste des solutions par nombres de mots
        for (int i = 0 ; i <= nbLettresJeu; i++){
            int nbResultats = nbMots[i];
            if (nbResultats > 0){
                printf("Mots de %d lettres (%d) : ", i, nbResultats);
                for (int j = 0 ; j < nbResultats ; j++){
                    printf("%s, ", listeMots[i][j]);
                }
                printf("\n");
            }
        }
    }
    char saisie[20];
    int idxSaisie=0;
    bool propalValide=false;
    bool finDePartie=true;

    char car;
    while (! finDePartie){
        printf("Votre proposition : ");
        car = fgetc(stdin);
        while (car != '\n'){
            saisie[idxSaisie++] = car;
            saisie[idxSaisie] = '\0';
            car = fgetc(stdin);
        }
        if (strlen(saisie) > 0){
            // teste proposition
            int nbSol = nbMots[strlen(saisie)];
            if (nbSol != 0){
                for (int i = 0 ; i < nbSol ; i++){
                    if (strcmp(listeMots[strlen(saisie)][i], saisie) == 0){
                        propalValide=true;
                    }
                }
                if (propalValide){
                    printf("Votre proposition (%s) est valide => BRAVO\n", saisie);
                } else {
                    printf("Votre proposition (%s) n'est pas valide => DOMMAGE\n", saisie);
                }
                propalValide=false;
            }
        }
    }
    printf("Fin du programme\n");
}
