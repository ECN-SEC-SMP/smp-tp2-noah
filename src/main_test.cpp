#include "../include/lit_ecrit.h"
#include "../include/entierlong.h"
#include "../include/utilitaires.h"
#include "../include/main_test.h"
#include "../include/operations.h"
#include <iostream>



int main(void) {
    cout << "Tests unitaires :" << endl;
    test_EntierLongIsEqual();
    test_convertInt_Entierlong();
    test_EntierLongAbsComparison();
    test_addSameSign();
    test_subtractionSameSign();
    test_MultiplicationEntierLong();
    test_divisionEuclidienne();


    //afficheEntierLong(entier1);
    return 0;
}

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

// void test_add(void){
//     //variables :
//     t_EntierLong entier1,entier2;
//     entier1 = {0,{10}};
//     entier2 = {0,{1}};
//     t_EntierLong resultat = multiplicationEntierLong(entier1,entier2);
//     cout << "Le résultat de la multiplication est : ";
//     afficheEntierLong(resultat);
// }


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

