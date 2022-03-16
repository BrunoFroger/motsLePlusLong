//-----------------------------------
//
//      compareMots.cpp
//
//-----------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cctype>

#include "../inc/variables.hpp"


char *suppressionAccents(char *ligne_char){

    //printf("\n suppression des accents de %s\n", ligne_char);
	int mchar, tchar;
    int nbConversion = 0;
    int index = 0;
    char tmp[200];
    int i = 0;
    //printf("longeur de la chaine a traiter : %ld\n", strlen(ligne_char));
	while (ligne_char[i] != '\0')
	{
		//Conversion du caractere en int
		mchar = (int)ligne_char[i];
        //printf("i=%d : (%c),%d  =>  ", i , ligne_char[i], mchar);
        
        switch(mchar){
            case -61:
                // traitement d'un carcatere accentué
                i++;
        		tchar = (int)ligne_char[i];
                //printf("\n\ti=%d : [%c],%d =>  ", i, ligne_char[i], tchar);
                switch (tchar){
                    case -92:
                    case -94:
                    case -96:
                    case -124:
                    case -126:
                    case -128:
                        tmp[index++] = 'a';
                        //printf("on transforme %d en 'a'\n", tchar);
                        nbConversion++;
                        break;
                    case -85:
                    case -86:
                    case -87:
                    case -88:
                    case -117:
                    case -118:
                    case -119:
                    case -120:
                        tmp[index++] = 'e';
                        //printf("on transforme %d en 'e'\n", tchar);
                        nbConversion++;
                        break;
                    case -68: 
                    case -69: 
                    case -100:
                    case -101:
                    case -103:
                    case -71:
                        tmp[index++] = 'u';
                        //printf("on transforme %d en 'u'\n", tchar);
                        nbConversion++;
                        break;
                    case -82: 
                    case -81: 
                    case -113: 
                    case -114: 
                        tmp[index++] = 'i';
                        //printf("on transforme %d en 'i'\n", tchar);
                        nbConversion++;
                        break;
                    case -76: 
                    case -74: 
                    case -108: 
                    case -106:  
                        tmp[index++] = 'o';
                        //printf("on transforme %d en 'o'\n", tchar);
                        nbConversion++;
                        break;
                    case -79: 
                    case -111: 
                        tmp[index++] = 'n';
                        //printf("on transforme %d en 'n'\n", tchar);
                        nbConversion++;
                        break;
                    case -89 : // ç;
                        tmp[index++] = 'c';
                        //printf("on transforme %d en 'c'\n", tchar);
                        nbConversion++;
                        break;
                    default :
                        //printf("on jette %d\n", tchar);
                        break;
                }
                break;
            default:
                // caractes non accentués
                //printf("on garde %d\n", mchar);
                tmp[index++] = mchar;
                break;
        }
        tmp[index]= '\0';
        i++;
    }
    strcpy(ligne_char, tmp);

    //printf("\n%d caracteres accentues modifies\n", nbConversion);
    //printf("nouvelle chaine : %s\n", ligne_char);
    return ligne_char;
}


bool compareMots(char *ligne, char *tirage){
    char lettreTirage, lettreLigne;
    int tailleLigne, tailleTirage;
    char lettresRestantesTirage[nbLettresJeu];
    char lettresRestantesLigne[nbLettresJeu];
    int nbLettresOk = 0;
    int nbIterations = 0;

    // enleve RC si present
    if (ligne[strlen(ligne) - 1] == '\n') ligne[strlen(ligne) - 1] = '\0';

    strcpy(lettresRestantesLigne, ligne);
    strcpy(ligne, suppressionAccents(lettresRestantesLigne));
    tailleLigne = strlen(ligne);
    tailleTirage = strlen(tirage);
    //printf("-----------------------------------------\n");
    // test si taille de ligne est correcte
    if ((tailleLigne > nbLettresJeu) || (tailleLigne < NB_LETTRES_MINI)){
        //printf(" [taille de %s incorrecte (%d)] \n", ligne, tailleLigne);
        return false;
    }

    // passage en minuscules du tirage et de la ligne
    for (int i = 0 ; i <= tailleTirage ; i++) {
        lettresRestantesTirage[i] = tolower(tirage[i]);
    }
    //printf("compare : ligne %s(%d), tirage %s(%d)\n", ligne, tailleLigne, tirage, tailleTirage);
    //printf(" [ligne apres suppression des accents <%s>] ", ligne);
    for (int i = 0 ; i <= tailleLigne ; i++) {
        lettresRestantesLigne[i] = tolower(lettresRestantesLigne[i]);
    }
    //printf(" [ligne apres suppression des majuscules <%s>] ", lettresRestantesLigne);

    //printf(" [comparaison de <%s> et <%s>]", lettresRestantesLigne, lettresRestantesTirage);

    //printf("\n");
    // boucle sur les caracteres
    nbLettresOk = 0;
    for (int i = 0 ; i < tailleLigne ; i++){
        for (int j = 0 ; j < tailleTirage ; j++){
            lettreLigne = lettresRestantesLigne[i];
            lettreTirage = lettresRestantesTirage[j];
            //printf("\tcomparaison de %c et %c => ", lettreLigne, lettreTirage);
            if (lettreLigne == lettreTirage){
                lettresRestantesLigne[i] = '#';
                lettresRestantesTirage[j] = '*';
                nbLettresOk++;
                //printf("ok\n");
            } else {
                //printf("nok\n");
            }
        }
    }

    if ( (nbLettresOk >= NB_LETTRES_MINI) && (nbLettresOk == tailleLigne)){
        //printf(" [%s est dans %s] \n", ligne, tirage);
        return true;
    } else {
        //printf(" [%s n'est dans %s] \n", ligne, tirage);
        return false;
    }

    return false;
}