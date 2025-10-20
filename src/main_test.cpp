#include "../include/lit_ecrit.h"
#include "../include/entierlong.h"
#include "../include/utilitaires.h"
#include "../include/main_test.h"
#include "../include/operations.h"
#include <iostream>

//Déclaration des constantes
using namespace std;
#define NOMBREFIBONACHI  2000// Nomnbre de terme de la suite de Fibonacci à calculer
#define U0 0 // Premier terme de la suite de Fibonacci
#define U1 1 // Deuxième terme de la suite de Fibonacci

int main(void) {
    // cout << "Tests unitaires :" << endl;
    // test_EntierLongIsEqual();
    // test_convertInt_Entierlong();
    // test_EntierLongAbsComparison();
    // test_addSameSign();
    // test_subtractionSameSign();
    // test_MultiplicationEntierLong();
    // test_divisionEuclidienne();

    t_EntierLong tabFibonnachi[NOMBREFIBONACHI];
    #ifndef TEST_UNITY
    calculFibonnachi(convertInt_Entierlong(U0), convertInt_Entierlong(U1), tabFibonnachi);
    #endif

    //afficheEntierLong(entier1);
    return 0;
}

/*
/*
 * @brief Calcule les termes de la suite de Fibonacci et les stocke dans un tableau.
 * 
 * @param u0 Premier terme de la suite.
 * @param u1 Deuxième terme de la suite.
 * @param tabFibonnachi Tableau où seront stockés les termes calculés.
 */
#ifndef TEST_UNITY
void  calculFibonnachi(t_EntierLong u0,t_EntierLong  u1, t_EntierLong * tabFibonnachi){
    // initialisation des deux premiers termes
    tabFibonnachi[0] = u0;
    tabFibonnachi[1] = u1;
    // affiche les deux premiers termes
    // afficheEntierLong(tabFibonnachi[0]);
    // afficheEntierLong(tabFibonnachi[1]);

    for (int i = 2; i <= NOMBREFIBONACHI; i++){
        // calcul et stockage du terme i
        initializeEntierLong(tabFibonnachi[i]);
        tabFibonnachi[i] = addSameSign(tabFibonnachi[i-1], tabFibonnachi[i-2]); // Calcul des termes de la suite de Fibonacci 
        // affiche le terme calculé
        if (i > NOMBREFIBONACHI-3){
            cout << "F(" << i << ") :";
            afficheEntierLong(tabFibonnachi[i]);
            cout << endl;
        }
        if (i >= NOMBREFIBONACHI && (EntierLongIsEqual(subtractionSameSign(tabFibonnachi[i],tabFibonnachi[i-1]),tabFibonnachi[i-2]))){
            cout << "U2000 - U1999 = U1998" << endl;
        }
    }
}
#endif



void test_convertInt_Entierlong(void){
    //variables :
    long long entier1 = 12345;
    t_EntierLong entierLong;
    entierLong = convertInt_Entierlong(entier1);
    cout << " convertit : ";
    afficheEntierLong(entierLong);
}

void test_EntierLongIsEqual(void){
    //variables :
    t_EntierLong entier1,entier2;
    entier1 = {0,1};
    entier2 = {0,{0,0,1}};
    if (EntierLongIsEqual(entier1,entier2)) // test de l'égalité
    {
        cout << "les 2 entier long sont égaux " << endl;
    }else{
        cout << "les 2 entier long sont différents ";
    }
}

void test_EntierLongAbsComparison(void){
    //variables :
    t_EntierLong entier1,entier2;
    entier1 = {0,{0,0,0,9}};
    entier2 = {0,{0,0,1}};
    if (EntierLongAbsComparison(entier1,entier2)) // test de l'égalité
    {
        cout << "n1 est plus petit ou égal a n2" << endl; 
    }else{
        cout << "n1 est plus grand que n2 " << endl;  
    }
}


void test_addSameSign(void){
    //variables :
    t_EntierLong entier1,entier2;
    entier1 = {0,{9,9}};
    entier2 = {0,{9,9}};
    t_EntierLong resultat = addSameSign(entier1,entier2);
    cout << "Le résultat de l'addition est : ";
    afficheEntierLong(resultat);
    
}

void test_subtractionSameSign(void){
    //variables :
    t_EntierLong entier1,entier2;
    entier1 = {0,{0,0,1}};
    entier2 = {0,{0,8}};
    t_EntierLong resultat = subtractionSameSign(entier1,entier2);
    cout << "Le résultat de la soustraction est : ";
    afficheEntierLong(resultat);
    
}

void test_MultiplicationEntierLong(void){
    //variables :
    t_EntierLong entier1,entier2;
    entier1 = {1,{0}};
    entier2 = {0,{0}};
    t_EntierLong resultat = multiplication(entier1,entier2);
    cout << "Le résultat de la multiplication est : ";
    afficheEntierLong(resultat);
}


void test_divisionEuclidienne(void){
    //variables :
    t_EntierLong entier1,entier2,quotient,reste;
    entier1 = {0,{0,0,0,0,1}}; 
    entier2 = {0,{8}};     
    divisionEuclidienne(entier1,entier2,quotient,reste);
    cout << "Le résultat de la division euclidienne est : " << endl;
    cout << "Quotient : ";
    afficheEntierLong(quotient);
    cout << "Reste : ";
    afficheEntierLong(reste);
}


