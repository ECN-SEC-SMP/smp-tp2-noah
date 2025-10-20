#include "utilitaires.h"
#include "cmath"
#include <iostream>

/**
 * @brief Convertit un entier en t_EntierLong
 *
 * @param intToConvert L'entier à convertir
 * @return t_EntierLong La structure contenant les chiffres et le signe
 * 
 */
t_EntierLong convertInt_Entierlong(long long intToConvert){
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


/**
 * @brief Compare deux valeurs t_EntierLong
 **
 * @param a Premier t_EntierLong à comparer.
 * @param b Deuxième t_EntierLong à comparer.
 * 
 * @return true Si les deux structures sont identiques (même signe et mêmes chiffres).
 */
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



bool EntierLongAbsComparison(t_EntierLong n1, t_EntierLong n2){
    
    unsigned int i1 = 1, i2 = 1;
    while (n1.chiffres[MAXCHIFFRES-i1] < 1 && i1 < MAXCHIFFRES)
    {
        i1++;  // recherche du premier chiffre non nul
    }
    while (n2.chiffres[MAXCHIFFRES-i2] < 1 && i2 < MAXCHIFFRES)
    {
        i2++; // recherche du premier chiffre non nul
    }

    if (i1 > i2) // Vérification si N1 a moins de chiffres que N2 (inversé car on commence par la fin du tableau)
    {
        return true;
    }
    else if ((i1 == i2) && (n1.chiffres[MAXCHIFFRES-i1] <= n2.chiffres[MAXCHIFFRES-i2]))// si même nombre de chiffres, on compare le chiffre le plus significatif
    {
        return true;
    }else { // n1 a plus de chiffres que n2
        return false;       
    }
}

void initializeEntierLong(t_EntierLong &n) {
    for (unsigned int i = 0; i < MAXCHIFFRES; i++) {
        n.chiffres[i] = 0;
    }
}


