#include "utilitaires.h"
#include "cmath"
#include <iostream>

t_EntierLong convertInt_Entierlong(int intToConvert){
    //Variables :
    t_EntierLong intConverted;
    string intToString = to_string(abs(intToConvert)); // Convertit en string
    unsigned int lenght = intToString.size(); // calcule la longeur
    unsigned int y = 0;
    
    if (lenght > MAXCHIFFRES) {
    cerr << "Erreur : le nombre dépasse le nombre de chiffres max autorisé (" << MAXCHIFFRES << ")." << endl;
    exit(EXIT_FAILURE);
    }
    
    if (intToConvert < 0)
    {
        intConverted.negatif = true; //Définit le signe
    }else{
        intConverted.negatif = false;
    }

    for (unsigned int i = 0; i < MAXCHIFFRES; i++)//Initialisation du tableau
    {
        // mise à 0 de chaque entier
        intConverted.chiffres[i] = 0;    
    }

    for (int i = lenght; i > 0 ; i--)
    {
        // Reconvertit caractère par caractère dans le tableau de int :
        intConverted.chiffres[i-1] = intToString[y] - '0';
        y++;
    }

    return intConverted;
}


bool EntierLongIsEqual(t_EntierLong a, t_EntierLong b){
    if (a.negatif != b.negatif){
        return false; // vérification du signe
    }
    for (unsigned int i = 0; i < MAXCHIFFRES; i++){
        if (a.chiffres[i] != b.chiffres[i]){
            return false;  // vérification des chiffres un par un
        }      
    }
    return true;
}


