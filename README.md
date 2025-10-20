# Rapport de TP - Arithmétique sur Grands Entiers

**Nom :** PERRET Noah 

**Groupe :** SEC

**Date :** 15 octobre 2025  

## Compilation et exécution

```bash
# Compilation normale
make

# Exécution des tests unity 

./test_EntierLong

# Exécution du main 

./main_test


# Nettoyage
make clean
```

## Préambule : Représentation des Grands Entiers


Pour représenter des nombres dépassant les limites des types primitifs, nous utilisons la structure `t_EntierLong` :

```cpp
const int MAXCHIFFRES = 18;

struct t_EntierLong {
    bool negatif;               // true si le nombre est négatif
    int chiffres[MAXCHIFFRES];  // Chiffres stockés de droite à gauche
};
```

### Choix de représentation :

**Justification du choix :**
- **Capacité** : Variaibles grâce à la variables ```cpp const int MAXCHIFFRES = 18;``` (limite pratique pour éviter les débordements)
- **Stockage** : Les chiffres sont stockés dans l'ordre inverse (unités à l'index 0)
- **Signe** : Booléen `negatif` pour indiquer le signe
- **Format** : Chaque élément du tableau contient un seul chiffre (0-9)

### Exemple de représentation :

Le nombre `123456` est représenté comme :
```cpp
t_EntierLong n;
n.negatif = false;
n.chiffres = {6, 5, 4, 3, 2, 1, 0, 0, ..., 0};
//            ^unités      ^dizaines de milliers
```
## Présentation de la démarche Unity 

### Stratégie de test effectué

- **Tests de cas normaux** : Validation du comportement attendu
- **Tests de cas limites** : Valeurs particulières (0, nombres maximaux)
- **Tests d'erreur** : Vérification des conditions d'échec

### Fonctions Unity utilisées

```cpp
TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, MAXCHIFFRES);  // Comparaison tableaux
TEST_ASSERT_EQUAL(expected, actual);                         // Comparaison valeurs
TEST_ASSERT_TRUE(condition);                                 // Test booléen
TEST_ASSERT_FALSE(condition);                                // Test booléen inverse
TEST_FAIL_MESSAGE("message");                                // Échec explicite
```

#### Fonctions nécessaires aux tests
```cpp
void setUp(void) {
    exit_called = 0;
    cerr.rdbuf(nullptr); // Désactive les sorties d'erreur pendant les tests
}

void tearDown(void) {
    // Nettoyage après chaque test
}
```

### Avantages de Unity pour ce projet

1. **Simplicité d'utilisation** : Syntaxe claire et intuitive
2. **Portabilité** : Compatible avec tous les environnements C/C++
3. **Granularité** : Tests unitaires isolés et reproductibles
4. **Fonctions spécialisées** : `TEST_ASSERT_EQUAL_INT_ARRAY` parfait pour nos tableaux
5. **Gestion d'erreurs** : Capture possible des `exit()` avec `setjmp/longjmp`
6. **Étendue des tests** : Grand nombre de cas différents vérifiers et testés

Cette approche avec Unity augmente la fiabilité et la robustesse de toutes les fonctionss implémentées.


## Fonctions Utilitaires

### - Fonction `convertInt_Entierlong`

#### Spécification
```cpp
t_EntierLong convertInt_Entierlong(long long intToConvert);
```
**Précondition :** `intToConvert` doit avoir au maximum 18 chiffres
**Postcondition :** Retourne la conversion en `t_EntierLong` de l'entier

#### Description du principe
Conversion par extraction successive des chiffres. Utilise `to_string()` pour obtenir la représentation décimale, puis stocke chaque chiffre dans l'ordre inverse (unités à l'index 0).

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_convertInt_Entierlong_positive(void) {
    // Test: conversion de 12345
    t_EntierLong result = convertInt_Entierlong(12345);
    int expected[] = {5, 4, 3, 2, 1};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, 5);
    TEST_ASSERT_EQUAL(false, result.negatif);
}

void test_convertInt_Entierlong_negative(void) {
    // Test: conversion de -12345 → même chiffres, signe négatif
    // ...
}

void test_convertInt_Entierlong_overflow(void) {
    // Test avec nombre trop grand → doit appeler exit()
    // ...
}
```
</details>

---

### - Fonction `EntierLongIsEqual`

#### Spécification
```cpp
bool EntierLongIsEqual(t_EntierLong a, t_EntierLong b);
```
**Précondition :** Aucune
**Postcondition :** Retourne `true` si a == b, `false` sinon

#### Description du principe
Comparaison stricte en vérifiant d'abord le signe, puis chaque chiffre du tableau. Optimisation : arrêt dès qu'une différence est trouvée.

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_EntierLongIsEqual_true(void) {
    // Test: 123 == 123
    t_EntierLong a = convertInt_Entierlong(123);
    t_EntierLong b = convertInt_Entierlong(123);
    TEST_ASSERT_TRUE(EntierLongIsEqual(a, b));
}

void test_EntierLongIsEqual_false_different_values(void) {
    // Test: 123 != 456
    // ...
}

void test_EntierLongIsEqual_false_different_signs(void) {
    // Test: 123 != -123
    // ...
}
```
</details>

---

### - Fonction `EntierLongAbsComparison`

#### Spécification
```cpp
bool EntierLongAbsComparison(t_EntierLong n1, t_EntierLong n2);
```
**Précondition :** Aucune
**Postcondition :** Retourne `true` si |n1| > |n2|, `false` sinon

#### Description du principe
Comparaison des valeurs absolues en parcourant les chiffres de gauche à droite (poids fort vers poids faible) pour déterminer l'ordre de grandeur.

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_EntierLongAbsComparison_true(void) {
    // Test: |456| > |123|
    t_EntierLong a = convertInt_Entierlong(456);
    t_EntierLong b = convertInt_Entierlong(123);
    TEST_ASSERT_TRUE(EntierLongAbsComparison(a, b));
}

void test_EntierLongAbsComparison_false(void) {
    // Test: |123| < |456|
    // ...
}

void test_EntierLongAbsComparison_negative_numbers(void) {
    // Test: |-456| > |123| (valeurs absolues)
    // ...
}
```
</details>

---

### - Fonction `initializeEntierLong`

#### Spécification
```cpp
void initializeEntierLong(t_EntierLong &n);
```
**Précondition :** Aucune
**Postcondition :** `n` représente la valeur 0 (tous chiffres à 0, signe positif)

#### Description du principe
Initialisation par défaut d'une structure `t_EntierLong`. Met tous les éléments du tableau `chiffres[]` à 0 et le booléen `negatif` à `false`.

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_initializeEntierLong(void) {
    t_EntierLong n;
    initializeEntierLong(n);
    
    int expected[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, n.chiffres, MAXCHIFFRES);
    TEST_ASSERT_EQUAL(false, n.negatif);
}
```
</details>

---

---

## Fonctions des Opérations Arithmétiques

### Fonction `addSameSign`

#### Spécification
```cpp
t_EntierLong addSameSign(t_EntierLong n1, t_EntierLong n2);
```
**Précondition :** `n1.negatif == n2.negatif` (même signe)
**Postcondition :** Retourne la somme arithmétique de n1 + n2

#### Description du principe
Addition classique avec gestion des retenues, chiffre par chiffre de droite à gauche. L'algorithme parcourt le tableau `chiffres[]` depuis l'index 0 (unités) jusqu'à MAXCHIFFRES-1, en propageant les retenues.

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_addSameSign_positive(void) {
    // Test: 123 + 456 = 579
    t_EntierLong a = convertInt_Entierlong(123);
    t_EntierLong b = convertInt_Entierlong(456);
    t_EntierLong result = addSameSign(a, b);
    
    int expected[] = {9, 7, 5, 0, 0, 0, 0, 0, ...};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, MAXCHIFFRES);
    TEST_ASSERT_EQUAL(false, result.negatif);
}

void test_addSameSign_negative(void) {
    // Test: (-123) + (-456) = -579
    // ...
}

void test_addSameSign_carry(void) {
    // Test avec retenues: 999 + 1 = 1000
    // ...
}
```
</details>

**Démarche Unity :** `TEST_ASSERT_EQUAL_INT_ARRAY` pour comparer les tableaux, tests des cas normaux, négatifs et retenues.

---

### - Fonction `subtractionSameSign`

#### Spécification
```cpp
t_EntierLong subtractionSameSign(t_EntierLong n1, t_EntierLong n2);
```
**Précondition :** `n1.negatif == n2.negatif` ET `|n1| >= |n2|`
**Postcondition :** Retourne la différence arithmétique n1 - n2

#### Description du principe
Soustraction classique avec gestion des emprunts. L'algorithme parcourt les chiffres de droite à gauche, en empruntant à la position supérieure quand nécessaire (diff < 0).

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_subtractionSameSign_positive(void) {
    // Test: 456 - 123 = 333
    t_EntierLong a = convertInt_Entierlong(456);
    t_EntierLong b = convertInt_Entierlong(123);
    t_EntierLong result = subtractionSameSign(a, b);
    
    int expected[] = {3, 3, 3, 0, 0, 0, 0, 0, ...};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, MAXCHIFFRES);
    TEST_ASSERT_EQUAL(false, result.negatif);
}

void test_subtractionSameSign_borrow(void) {
    // Test avec emprunts: 1000 - 1 = 999
    // ...
}
```
</details>

**Démarche Unity :** Tests focalisés sur la gestion des emprunts. Les cas d'erreur (n1 < n2) sont testés avec `setjmp/longjmp`.

---

### - Fonction `add`

#### Spécification
```cpp
t_EntierLong add(t_EntierLong n1, t_EntierLong n2);
```
**Précondition :** Aucune
**Postcondition :** Retourne la somme algébrique n1 + n2

#### Description du principe
Addition générale gérant tous les cas de signes. Délègue à `addSameSign` pour même signe, ou convertit en soustraction pour signes différents.

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_add_same_sign_positive(void) {
    // Test: 123 + 456 = 579
    t_EntierLong a = convertInt_Entierlong(123);
    t_EntierLong b = convertInt_Entierlong(456);
    t_EntierLong result = add(a, b);
    
    int expected[] = {9, 7, 5, 0, 0, 0, 0, 0, ...};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, MAXCHIFFRES);
    TEST_ASSERT_EQUAL(false, result.negatif);
}

void test_add_different_signs(void) {
    // Test: 456 + (-123) = 333
    // ...
}
```
</details>

---

### - Fonction `sub`

#### Spécification
```cpp
t_EntierLong sub(t_EntierLong n1, t_EntierLong n2);
```
**Précondition :** Aucune
**Postcondition :** Retourne la différence algébrique n1 - n2

#### Description du principe
Soustraction générale gérant tous les cas de signes. Convertit en addition pour signes différents, ou utilise `subtractionSameSign` avec gestion de l'ordre.

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_sub_positive_result(void) {
    // Test: 456 - 123 = 333
    t_EntierLong a = convertInt_Entierlong(456);
    t_EntierLong b = convertInt_Entierlong(123);
    t_EntierLong result = sub(a, b);
    
    int expected[] = {3, 3, 3, 0, 0, 0, 0, 0, ...};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, MAXCHIFFRES);
    TEST_ASSERT_EQUAL(false, result.negatif);
}

void test_sub_negative_result(void) {
    // Test: 123 - 456 = -333
    // ...
}
```
</details>

---

### - Fonction `multiplication`

#### Spécification
```cpp
t_EntierLong multiplication(t_EntierLong n1, t_EntierLong n2);
```
**Précondition :** Aucune
**Postcondition :** Retourne le produit n1 × n2

#### Description du principe
Multiplication par l'algorithme classique. Pour chaque chiffre de n1 à la position i, multiplie par chaque chiffre de n2 à la position j, et additionne le résultat à la position i+j avec gestion des retenues.

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_multiplication_simple(void) {
    // Test: 123 × 456 = 56088
    t_EntierLong a = convertInt_Entierlong(123);
    t_EntierLong b = convertInt_Entierlong(456);
    t_EntierLong result = multiplication(a, b);
    
    int expected[] = {8, 8, 0, 6, 5, 0, 0, 0, ...};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, MAXCHIFFRES);
    TEST_ASSERT_EQUAL(false, result.negatif);
}

void test_multiplication_by_zero(void) {
    // Test: 123 × 0 = 0
    // ...
}

void test_multiplication_negative(void) {
    // Test: (-123) × 456 = -56088 (gestion des signes)
    // ...
}
```
</details>

**Démarche Unity :** Tests de multiplication simple, par zéro (cas particulier), et avec nombres négatifs pour vérifier la gestion des signes.

---

### - Fonction `divisionEuclidienne`

#### Spécification
```cpp
void divisionEuclidienne(t_EntierLong dividende, t_EntierLong diviseur, 
                        t_EntierLong &quotient, t_EntierLong &reste);
```
**Précondition :** `diviseur ≠ 0`
**Postcondition :** `dividende = quotient × diviseur + reste` avec `0 ≤ |reste| < |diviseur|`

#### Description du principe
Division euclidienne par soustraction répétée optimisée. Construction du quotient chiffre par chiffre en déterminant combien de fois le diviseur peut être soustrait du dividende partiel.

#### Jeux d'essais avec Unity
<details>
<summary>Cliquer pour voir les tests</summary>

```cpp
void test_divisionEuclidienne_simple(void) {
    // Test: 12345 ÷ 123 = quotient: 100, reste: 45
    t_EntierLong dividende = convertInt_Entierlong(12345);
    t_EntierLong diviseur = convertInt_Entierlong(123);
    t_EntierLong quotient, reste;
    
    divisionEuclidienne(dividende, diviseur, quotient, reste);
    
    int expected_quotient[] = {0, 0, 1, 0, 0, 0, 0, 0, ...};
    int expected_reste[] = {5, 4, 0, 0, 0, 0, 0, 0, ...};
    
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_quotient, quotient.chiffres, MAXCHIFFRES);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reste, reste.chiffres, MAXCHIFFRES);
}

void test_divisionEuclidienne_dividende_plus_petit(void) {
    // Test: 123 ÷ 456 = quotient: 0, reste: 123
    // ...
}

void test_divisionEuclidienne_par_zero(void) {
    // Test division par zéro → doit appeler exit()
    // ...
}
```
</details>

**Démarche Unity :** Tests de division normale, cas où dividende < diviseur, et gestion d'erreur pour division par zéro avec capture de `exit()`.

---


