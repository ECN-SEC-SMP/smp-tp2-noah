#include "operations.h"
#include "utilitaires.h"
#include "lit_ecrit.h"
#include "cmath"
#include <iostream>

/**
 * @brief Additionne deux t_EntierLong de même signe
 * 
 * @param n1 Premier opérande
 * @param n2 Deuxième opérande (même signe que n1)
 * 
 * @return t_EntierLong Résultat de l'addition n1 + n2
 */
t_EntierLong addSameSign(t_EntierLong n1, t_EntierLong n2){
    if (n1.negatif != n2.negatif) {
    cerr << "Erreur : Les 2 chiffrs n'ont pas le même signe" << std::endl;
    exit(EXIT_FAILURE);
    }

    t_EntierLong n3;
    initializeEntierLong(n3);
    n3.negatif = n1.negatif ? 1 : 0;
    
   // initialisation du résultat

    u_int8_t carry = 0 ;
    for (unsigned int i = 0; i < MAXCHIFFRES; i++) {
        unsigned int somme = n1.chiffres[i] + n2.chiffres[i] + carry;
        n3.chiffres[i] = somme % 10;
        carry = somme / 10;
    }
    
    return n3;
}

/**
 * @brief Soustrait deux t_EntierLong de même signe (n1 >= n2)
 * 
 * @param n1 Premier opérande 
 * @param n2 Deuxième opérande (même signe que n1)
 * 
 * @return t_EntierLong Résultat de la soustraction n1 - n2
 */
t_EntierLong subtractionSameSign(t_EntierLong n1, t_EntierLong n2){
    if (n1.negatif != n2.negatif) {
        cerr << "Erreur : Les 2 chiffrs n'ont pas le même signe" << endl;
        exit(EXIT_FAILURE);
    }
    if (!(EntierLongAbsComparison(n2,n1))) {
        cerr << "Erreur : n1 doit être plus grand ou égal à n2" << endl;
        exit(EXIT_FAILURE);
    }

    t_EntierLong n3;
    initializeEntierLong(n3);
    n3.negatif = n1.negatif ? 1 : 0;
    
   // initialisation du résultat

    u_int8_t borrow = 0;
    for (int i = 0; i < MAXCHIFFRES; i++) {
        int diff = n1.chiffres[i] - n2.chiffres[i] - borrow;

        if (diff < 0) {
            borrow = 1;
            diff += 10;
        } else {
            borrow = 0;
        }
        
        n3.chiffres[i] = diff % 10;
    }
    return n3;
}

/**
 * @brief Additionne deux t_EntierLong de signes quelconques 
 * 
 * @param n1 Premier opérande de type t_EntierLong
 * @param n2 Deuxième opérande de type t_EntierLong
 * 
 * @return t_EntierLong Le résultat de l'addition n1 + n2
 */
t_EntierLong add(t_EntierLong n1, t_EntierLong n2) {
    t_EntierLong n3;
    initializeEntierLong(n3);


    // Si les deux ont le même signe → addition directe
    if (n1.negatif == n2.negatif) {
        n3 = addSameSign(n1, n2);
    } 
    else {   
        // si n1 positif et n2 négatif : n1 - |n2|
        if (!n1.negatif && n2.negatif) {
            n2.negatif = 0;

            if ((EntierLongAbsComparison(n1, n2))) {
                n3 = subtractionSameSign(n1, n2);
                n3.negatif = 0;
            } else {
                n3 = subtractionSameSign(n2, n1);
                n3.negatif = 1;
            }
        }
        // Si n1 négatif et n2 positif : n2 - |n1|
        else if (n1.negatif && !n2.negatif) {
            n1.negatif = 0;

            if ((EntierLongAbsComparison(n2, n1))) {
                n3 = subtractionSameSign(n2, n1);
                n3.negatif = 0;
            } else {
                n3 = subtractionSameSign(n1, n2);
                n3.negatif = 1;
            }
        }
    }

    return n3;
}

/*IA à partir de l'addition*/
/**
 * @brief Soustrait deux t_EntierLong de signes quelconques
 *
 * @param n1 Premier opérande de type t_EntierLong (minuende)
 * @param n2 Deuxième opérande de type t_EntierLong (soustrahende)
 *
 * @return t_EntierLong Le résultat de la soustraction n1 - n2
 */
t_EntierLong sub(t_EntierLong n1, t_EntierLong n2) {
    t_EntierLong n3;
    initializeEntierLong(n3);
    
    // Si les deux ont des signes différents → addition des valeurs absolues
    if (n1.negatif != n2.negatif) {
        // Cas 1 : n1 positif, n2 négatif → n1 + |n2| (résultat positif)
        if (!n1.negatif && n2.negatif) {
            n2.negatif = 0;
            n3 = addSameSign(n1, n2);
            n3.negatif = 0;
        }
        // Cas 2 : n1 négatif, n2 positif → -(|n1| + n2) (résultat négatif)
        else if (n1.negatif && !n2.negatif) {
            n1.negatif = 0;
            n3 = addSameSign(n1, n2);
            n3.negatif = 1;
        }
    }
    else { // Même signe → soustraction des valeurs absolues
        // Cas 1 : les deux positifs → n1 - n2
        if (!n1.negatif && !n2.negatif) {
            if (EntierLongAbsComparison(n1, n2)) {
                n3 = subtractionSameSign(n1, n2);
                n3.negatif = 0;
            } else {
                n3 = subtractionSameSign(n2, n1);
                n3.negatif = 1;
            }
        }
        // Cas 2 : les deux négatifs → -(|n1| - |n2|) = |n2| - |n1|
        else if (n1.negatif && n2.negatif) {
            n1.negatif = 0;
            n2.negatif = 0;
            if (EntierLongAbsComparison(n1, n2)) {
                n3 = subtractionSameSign(n1, n2);
                n3.negatif = 1;
            } else {
                n3 = subtractionSameSign(n2, n1);
                n3.negatif = 0;
            }
        }
    }
    
    return n3;
}

/**
 * @brief Effectue la multiplication de deux t_EntierLong en utilisant la méthode : "à la main"
 * 
 * @param n1 Premier opérande de type t_EntierLong (multiplicande)
 * @param n2 Deuxième opérande de type t_EntierLong (multiplicateur)
 * 
 * @return t_EntierLong Le résultat de la multiplication n1 × n2
 * 
 */
t_EntierLong multiplication(t_EntierLong n1, t_EntierLong n2) {
    t_EntierLong n3;
    initializeEntierLong(n3);
    
    // Gestion du signe inchangée
    n3.negatif = (n1.negatif && !n2.negatif || !n1.negatif && n2.negatif) ?  1 : 0;
    
    for (int i = 0; i < MAXCHIFFRES; i++) {
        int carry = 0;
        
        // On effectue la multiplication comme on le ferait à la main, 
        for (int j = 0; j < MAXCHIFFRES ; j++) { 
            unsigned int pos1 = i + j; 

            if (pos1 >= MAXCHIFFRES) continue; 

            // calcul du produit simple + carry 
            unsigned int produit = n1.chiffres[i] * n2.chiffres[j] + n3.chiffres[pos1] + carry;
            n3.chiffres[pos1] = produit % 10;
            carry = produit / 10;   
        }
        
        //Propager la retenue finale 
        int k = i; 
        while (carry > 0 && k >= 0) {
             int temp = n3.chiffres[k] + carry;
             n3.chiffres[k] = temp % 10;
             carry = temp / 10;
             k--;
        }
        
    }

    return n3;
}

/**
 * @brief Effectue la multiplication de deux t_EntierLong par additions répétées
 * 
 * @param n1 Premier opérande de type t_EntierLong (multiplicande)
 * @param n2 Deuxième opérande de type t_EntierLong (multiplicateur - nombre de fois à additionner n1)
 * 
 * @return t_EntierLong Le résultat de la multiplication n1 × n2
 * 
 * @warning Cette méthode peut être lente pour de grandes valeurs de n2 car elle effectue
 *          des additions successives
 */
/*t_EntierLong multiplication(t_EntierLong n1, t_EntierLong n2) {
    t_EntierLong n3;
    initializeEntierLong(n3);
    
    // Gestion du signe inchangée
    if (n1.negatif && !n2.negatif || !n1.negatif && n2.negatif){
        n3.negatif = 1; 
    } else {
        n3.negatif = 0;
    }

    // n1 et n2 valeur absolues
    n1.negatif = 0;
    n2.negatif = 0;

    t_EntierLong counter;
    counter.negatif = 0;
    initializeEntierLong(counter);
    
    while (!EntierLongIsEqual(counter,n2)) {  // tant que compteur n'est pas égal à n2
        n3 = addSameSign(n3, n1);  
        afficheEntierLong(n3);
        counter = addSameSign(counter, t_EntierLong{0,{1}}); // +1
    }
        

    return n3;
}*/


/**
 * @brief Effectue la division euclidienne de deux t_EntierLong
 * 
 * @param dividende Le nombre à diviser
 * @param diviseur Le nombre par lequel diviser (ne doit pas être zéro)
 * @param quotient Référence vers le résultat de la division (modifié par la fonction)
 * @param reste Référence vers le reste de la division (modifié par la fonction)
 * 
 * @warning Cette méthode peut être lente pour de grandes valeurs de dividende car elle effectue
 *          des soustractions successives
 */
void divisionEuclidienne(t_EntierLong dividende, t_EntierLong diviseur, t_EntierLong &quotient, t_EntierLong &reste) {
    // Vérification que le diviseur n'est pas zéro
    t_EntierLong zero;
    zero.negatif = 0;
    initializeEntierLong(zero);
    if (EntierLongIsEqual(diviseur, zero)) {
        cerr << "Erreur : Division par zéro impossible" << endl;
        exit(EXIT_FAILURE);
    }
    
    // Initialisation des résultats
    initializeEntierLong(quotient);
    initializeEntierLong(reste);
    
    // Gestion du signe du quotient
    quotient.negatif = (dividende.negatif != diviseur.negatif) ? 1 : 0;
    reste.negatif = dividende.negatif; // Le reste a le même signe que le dividende
    
    //Valeurs absolues
    dividende.negatif = 0; diviseur.negatif = 0;
    
    // Copie du dividende dans le reste
    for (unsigned int i = 0; i < MAXCHIFFRES; i++) {
        reste.chiffres[i] = dividende.chiffres[i];
    }
    
    // Division par soustractions successives
    while (EntierLongAbsComparison(diviseur,reste)) {
        reste = subtractionSameSign(reste, diviseur);
        quotient = addSameSign(quotient, t_EntierLong{0,{1}}); // +1);
    }
}

