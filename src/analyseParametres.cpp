//-----------------------------------
//
//      analyseParametres.cpp
//
//-----------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../inc/variables.hpp"

//-----------------------------------
//
//      aide
//
//-----------------------------------
void aide(char *nomProgramme){
    printf("syntaxe : %s tirage [options]\n", nomProgramme);
    printf("    options : \n");
    printf("        -h : cette aide\n");
    printf("        -f <nom de fichier> : definition du fichier dictionnaire\n");
    printf("        -t <valeur> : fixe le nombre de lettres du tirage\n");
    printf("        -s : affiche les solutions du tirage\n");
    exit(0);
}

//-----------------------------------
//
//      setNbLettresJeu
//
//-----------------------------------
void setNbLettresJeu(int nb){
    if (nb > TAILLE_MAX_TIRAGE){
        printf("ERREUR : la taille du tirage est trop grande max = %d\n", TAILLE_MAX_TIRAGE);
        exit(-1);
    }
    if (nb < TAILLE_MIN_TIRAGE){
        printf("ERREUR : la taille du tirage est trop petite min = %d\n", TAILLE_MIN_TIRAGE);
        exit(-1);
    }
    nbLettresJeu = nb;
}

//-----------------------------------
//
//      lettreRandom
//
//-----------------------------------
void analyseParametres(int argc, char **argv){
    //printf("Analyse des parametres ... debut \n");
    int i = 1;
    char param[50];
    strcpy(tirage,"");
    do {
        //printf("traitement du parametre numero %d\n", i);
        strcpy(param, argv[i]);
        //printf("analyse de %s\n", param);
        if (param[0] != '-'){
            //printf("le tirage de jeu est %s\n", param);
            strcpy(tirage, param);
            setNbLettresJeu(strlen(tirage));
        } else {
            //printf("gestion d'une option %s\n", param);
            switch(param[1]){
                case 'f' : // specifie le nom du fichier de mots
                    strcpy(nomFichierMots, argv[++i]);
                    break;
                case 'h' : // aide
                    aide(argv[0]);
                    break;
                case 's' : // aide
                    afficheSolutions=true;
                    break;
                case 't' : // taille du tirage
                    if (strlen(tirage) != 0){
                        printf("option -t incompatible avec la specification d'un tirage\n");
                        i++;
                    } else {
                        setNbLettresJeu(atoi(argv[++i]));
                        //printf("definition de la taille du tirage a %d\n", nbLettresJeu);
                    }
                    break;
                default :
                    printf("option inconnue %s\n", param);
                    exit(-1);
            }
        }
    } while (++i < argc);
    //printf("Analyse des parametres ... fin \n");
}