#include "../include/lit_ecrit.h"
#include "../include/entierlong.h"
#include "../include/utilitaires.h"
#include "../include/main_test.h"

#include <iostream>



int main(void) {
    //test_EntierLongIsEqual();
    //test_convertInt_Entierlong();
    t_EntierLong entierLong;

    for (unsigned int i = 0; i < MAXCHIFFRES; i++)//Initialisation du tableau
    {
        // mise à 0 de chaque entier
        entierLong.chiffres[i] = 0;    
    }
    entierLong.negatif = false;
    entierLong.chiffres[0] = 1;
    afficheEntierLong(entierLong);
    

    




    //afficheEntierLong(entier1);
    return 0;
}

void test_convertInt_Entierlong(void){
    //variables :
    int entier1 = 32;
    t_EntierLong entierLong;
    entierLong = convertInt_Entierlong(entier1);
    cout << " convertit : ";
    afficheEntierLong(entierLong);
}

void test_EntierLongIsEqual(void){
    //variables :
    t_EntierLong entier1,entier2;
    entier1 = {0,{1,0}};
    entier1 = {0,{1,0}};
    if (EntierLongIsEqual(entier1,entier2)) // test de l'égalité
    {
        cout << "les 2 entier long sont égaux ";
    }
}

