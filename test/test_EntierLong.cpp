#include "../include/lit_ecrit.h"
#include "../include/entierlong.h"
#include "../include/utilitaires.h"
#include "../include/main_test.h"
#include "../include/operations.h"
#include "unity.h"
#include <iostream>


using namespace std;

/*l'IA m'a aidé pour rajouté un grand nombre de test*/
static jmp_buf test_exit_jmp;
static int exit_called = 0;

// Override de la fonction exit pour les tests
void exit(int status) {
    exit_called = status;
    longjmp(test_exit_jmp, 1);
}

void setUp(void) {
    exit_called = 0;
    cerr.rdbuf(nullptr); //désactive les sorties d'erreur pendant les tests
}

void tearDown(void) {
    // Cleanup
}

void test_convertInt_Entierlong(void) {
    // Test avec un nombre trop grand
    long huge_number = 2000000000000000000; // Plus grand que MAXCHIFFRES
    
    if (setjmp(test_exit_jmp) == 0) {
        // Code qui devrait provoquer exit()
        convertInt_Entierlong(huge_number);
        TEST_FAIL_MESSAGE("Expected exit() to be called");
    } else {
        // exit() a été appelé
        TEST_ASSERT_EQUAL(EXIT_FAILURE, exit_called);
    }
    // Reset du flag
    exit_called = 0;
    // Test de conversion
    long input1 = 12345;
    long input2 = -12345;
    int expected[5] = {5,4,3,2,1};
    t_EntierLong result = convertInt_Entierlong(input1);

    TEST_ASSERT_EQUAL(0, result.negatif);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result.chiffres, 5);

    t_EntierLong result_neg = convertInt_Entierlong(input2);
    TEST_ASSERT_EQUAL(1, result_neg.negatif);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result_neg.chiffres, 5);
}


void test_EntierLongIsEqual(void) {
    // Test d'égalité
    t_EntierLong a = {0, {123}};
    t_EntierLong b = {1, {456}};
    t_EntierLong c = {1, {312}};
    
    TEST_ASSERT_TRUE(EntierLongIsEqual(a, a));
    TEST_ASSERT_TRUE(EntierLongIsEqual(b, b));
    TEST_ASSERT_FALSE(EntierLongIsEqual(a, b));
    TEST_ASSERT_FALSE(EntierLongIsEqual(b, c));
    TEST_ASSERT_FALSE(EntierLongIsEqual(a, c));
}

void test_initialize(void) {
    // Test 1: Initialisation d'un EntierLong
    t_EntierLong test_init;
    initializeEntierLong(test_init);
    
    // Vérifier que tous les chiffres sont à 0
    for (unsigned int i = 0; i < MAXCHIFFRES; i++) {
        TEST_ASSERT_EQUAL(0, test_init.chiffres[i]);
    }

    // Test 2: Initialisation d'un EntierLong déjà utilisé
    t_EntierLong dirty = {1, {9, 8, 7, 6, 5}};
    initializeEntierLong(dirty);
    
    // Le signe n'est pas modifié par initializeEntierLong
    TEST_ASSERT_EQUAL(1, dirty.negatif);
    // Mais tous les chiffres doivent être à 0
    for (unsigned int i = 0; i < MAXCHIFFRES; i++) {
        TEST_ASSERT_EQUAL(0, dirty.chiffres[i]);
    }
}

void test_abs_comparison(void) {
    // Test 1: Comparaison simple (3 <= 10)
    t_EntierLong large = {0, {10}};
    t_EntierLong small = {0, {3}};
    TEST_ASSERT_TRUE(EntierLongAbsComparison(small, large));
    TEST_ASSERT_FALSE(EntierLongAbsComparison(large, small));

    // Test 2: Comparaison avec nombres identiques (5 >= 5)
    t_EntierLong same_a = {0, {5}};
    t_EntierLong same_b = {1, {5}}; // Même valeur absolue, signe différent
    TEST_ASSERT_TRUE(EntierLongAbsComparison(same_a, same_b));
    TEST_ASSERT_TRUE(EntierLongAbsComparison(same_b, same_a));

    // Test 3: Comparaison avec zéro
    t_EntierLong number = {0, {7}};
    t_EntierLong zero = {0, {0}};
    TEST_ASSERT_TRUE(EntierLongAbsComparison(zero, number));
    TEST_ASSERT_TRUE(EntierLongAbsComparison(zero, zero));

    // Test 4: Comparaison nombres avec plusieurs chiffres
    t_EntierLong multi = {0, {0, 0, 1}}; // 100 (selon ton format)
    t_EntierLong single = {0, {9}};      // 9
    TEST_ASSERT_FALSE(EntierLongAbsComparison(multi, single));
    TEST_ASSERT_TRUE(EntierLongAbsComparison(single, multi));
}

void test_add(void) {
    // ===== TEST ADD SAME SIGN SEULEMENT =====
    
    // Test 1: Addition positifs simples (5 + 3 = 8)
    t_EntierLong pos_a = {0, {5}};
    t_EntierLong pos_b = {0, {3}};
    t_EntierLong add_pos_result = addSameSign(pos_a, pos_b);
    
    TEST_ASSERT_EQUAL(0, add_pos_result.negatif);
    int expected_add1[1] = {8};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_add1, add_pos_result.chiffres, 1);

    // Test 2: Addition négatifs (-7 + -2 = -9)
    t_EntierLong neg_a = {1, {7}};
    t_EntierLong neg_b = {1, {2}};
    t_EntierLong add_neg_result = addSameSign(neg_a, neg_b);
    
    TEST_ASSERT_EQUAL(1, add_neg_result.negatif);
    int expected_add2[1] = {9};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_add2, add_neg_result.chiffres, 1);

    // Test 3: Addition avec zéro (5 + 0 = 5)
    t_EntierLong number = {0, {5}};
    t_EntierLong zero = {0, {0}};
    t_EntierLong add_zero_result = addSameSign(number, zero);
    
    TEST_ASSERT_EQUAL(0, add_zero_result.negatif);
    int expected_add3[1] = {5};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_add3, add_zero_result.chiffres, 1);

    // Test 4: Addition de deux zéros (0 + 0 = 0)
    t_EntierLong zero_a = {0, {0}};
    t_EntierLong zero_b = {0, {0}};
    t_EntierLong double_zero = addSameSign(zero_a, zero_b);
    
    TEST_ASSERT_EQUAL(0, double_zero.negatif);
    int expected_add4[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_add4, double_zero.chiffres, 1);

    // Test 5: Addition avec retenue (9 + 5 = 14, format: {4, 1})
    t_EntierLong carry_a = {0, {9}};
    t_EntierLong carry_b = {0, {5}};
    t_EntierLong carry_result = addSameSign(carry_a, carry_b);
    
    TEST_ASSERT_EQUAL(0, carry_result.negatif);
    int expected_add5[2] = {4, 1}; // 14 stocké comme {4, 1} selon ton format
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_add5, carry_result.chiffres, 2);
    
    // Test 6: addSameSign avec signes différents (devrait échouer)
    exit_called = 0;
    t_EntierLong pos = {0, {5}};
    t_EntierLong neg = {1, {3}};
    
    if (setjmp(test_exit_jmp) == 0) {
        addSameSign(pos, neg);
        TEST_FAIL_MESSAGE("Expected exit() for different signs in addSameSign");
    } else {
        TEST_ASSERT_EQUAL(EXIT_FAILURE, exit_called);
    }
}

void test_sub(void) {
    // ===== TEST SUBTRACTION SAME SIGN SEULEMENT =====
    
    // Test 1: Soustraction positifs simples (10 - 3 = 7)
    t_EntierLong pos_a = {0, {10}};
    t_EntierLong pos_b = {0, {3}};
    t_EntierLong sub_pos_result = subtractionSameSign(pos_a, pos_b);
    
    TEST_ASSERT_EQUAL(0, sub_pos_result.negatif);
    int expected_sub1[1] = {7};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub1, sub_pos_result.chiffres, 1);

    // Test 2: Soustraction négatifs (-10 - (-3) = -7)
    t_EntierLong neg_a = {1, {10}};
    t_EntierLong neg_b = {1, {3}};
    t_EntierLong sub_neg_result = subtractionSameSign(neg_a, neg_b);
    
    TEST_ASSERT_EQUAL(1, sub_neg_result.negatif);
    int expected_sub2[1] = {7};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub2, sub_neg_result.chiffres, 1);

    // Test 3: Soustraction avec zéro (5 - 0 = 5)
    t_EntierLong number = {0, {5}};
    t_EntierLong zero = {0, {0}};
    t_EntierLong sub_zero_result = subtractionSameSign(number, zero);
    
    TEST_ASSERT_EQUAL(0, sub_zero_result.negatif);
    int expected_sub3[1] = {5};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub3, sub_zero_result.chiffres, 1);

    // Test 4: Soustraction identiques (5 - 5 = 0)
    t_EntierLong same_a = {0, {5}};
    t_EntierLong same_b = {0, {5}};
    t_EntierLong sub_same_result = subtractionSameSign(same_a, same_b);
    
    TEST_ASSERT_EQUAL(0, sub_same_result.negatif);
    int expected_sub4[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub4, sub_same_result.chiffres, 1);

    // Test 5: Soustraction avec retenue (12 - 5 = 7)
    t_EntierLong borrow_a = {0, {12}};
    t_EntierLong borrow_b = {0, {5}};
    t_EntierLong borrow_result = subtractionSameSign(borrow_a, borrow_b);
    
    TEST_ASSERT_EQUAL(0, borrow_result.negatif);
    int expected_sub5[1] = {7};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub5, borrow_result.chiffres, 1);

    // Test 6: subtractionSameSign avec signes différents (devrait échouer)
    exit_called = 0;
    t_EntierLong pos = {0, {10}};
    t_EntierLong neg = {1, {3}};
    
    if (setjmp(test_exit_jmp) == 0) {
        subtractionSameSign(pos, neg);
        TEST_FAIL_MESSAGE("Expected exit() for different signs in subtractionSameSign");
    } else {
        TEST_ASSERT_EQUAL(EXIT_FAILURE, exit_called);
    }

    // Test 7: subtractionSameSign avec n1 < n2 (devrait échouer)
    exit_called = 0;
    t_EntierLong small = {0, {3}};
    t_EntierLong large = {0, {10}};
    
    if (setjmp(test_exit_jmp) == 0) {
        subtractionSameSign(small, large);
        TEST_FAIL_MESSAGE("Expected exit() when n1 < n2 in subtractionSameSign");
    } else {
        TEST_ASSERT_EQUAL(EXIT_FAILURE, exit_called);
    }
}

void test_add_general(void) {
    // ===== TEST ADD GÉNÉRAL (tous cas de signes) =====
    
    // Test 1: Addition même signe positif (5 + 7 = 12)
    t_EntierLong pos_a = {0, {5}};
    t_EntierLong pos_b = {0, {7}};
    t_EntierLong add_pos_result = add(pos_a, pos_b);
    
    TEST_ASSERT_EQUAL(0, add_pos_result.negatif);
    int expected_gen1[2] = {2,1};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_gen1, add_pos_result.chiffres, 2);

    // Test 2: Addition même signe négatif (-4 + -6 = -10)
    t_EntierLong neg_a = {1, {4}};
    t_EntierLong neg_b = {1, {6}};
    t_EntierLong add_neg_result = add(neg_a, neg_b);
    
    TEST_ASSERT_EQUAL(1, add_neg_result.negatif);
    int expected_gen2[2] = {0,1};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_gen2, add_neg_result.chiffres, 2);

    // Test 3: Addition positif + négatif (positif plus grand) (10 + (-3) = 7)
    t_EntierLong pos_large = {0, {10}};
    t_EntierLong neg_small = {1, {3}};
    t_EntierLong add_result1 = add(pos_large, neg_small);
    
    TEST_ASSERT_EQUAL(0, add_result1.negatif);
    int expected_gen3[1] = {7};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_gen3, add_result1.chiffres, 1);

    // Test 4: Addition positif + négatif (négatif plus grand) (3 + (-10) = -7)
    t_EntierLong pos_small = {0, {3}};
    t_EntierLong neg_large = {1, {10}};
    t_EntierLong add_result2 = add(pos_small, neg_large);
    
    TEST_ASSERT_EQUAL(1, add_result2.negatif);
    int expected_gen4[1] = {7};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_gen4, add_result2.chiffres, 1);

    // Test 5: Addition négatif + positif (-5 + 8 = 3)
    t_EntierLong neg_first = {1, {5}};
    t_EntierLong pos_second = {0, {8}};
    t_EntierLong add_result3 = add(neg_first, pos_second);
    
    TEST_ASSERT_EQUAL(0, add_result3.negatif);
    int expected_gen5[1] = {3};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_gen5, add_result3.chiffres, 1);

    // Test 6: Addition avec zéro (5 + 0 = 5)
    t_EntierLong number = {0, {5}};
    t_EntierLong zero = {0, {0}};
    t_EntierLong add_zero_result = add(number, zero);
    
    TEST_ASSERT_EQUAL(0, add_zero_result.negatif);
    int expected_gen6[1] = {5};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_gen6, add_zero_result.chiffres, 1);

    // Test 7: Addition opposés (5 + (-5) = 0)
    t_EntierLong positive = {0, {5}};
    t_EntierLong negative = {1, {5}};
    t_EntierLong add_opposite_result = add(positive, negative);
    
    TEST_ASSERT_EQUAL(0, add_opposite_result.negatif);
    int expected_gen7[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_gen7, add_opposite_result.chiffres, 1);
}

void test_sub_general(void) {
    // ===== TEST SUBTRACTION GÉNÉRAL (tous cas de signes) =====
    
    // Test 1: Soustraction même signe positif simple (10 - 3 = 7)
    t_EntierLong pos_a = {0, {10}};
    t_EntierLong pos_b = {0, {3}};
    t_EntierLong sub_pos_result = sub(pos_a, pos_b);
    
    TEST_ASSERT_EQUAL(0, sub_pos_result.negatif);
    int expected_sub_gen1[1] = {7};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen1, sub_pos_result.chiffres, 1);

    // Test 2: Soustraction même signe négatif (-10 - (-3) = -7)
    t_EntierLong neg_a = {1, {10}};
    t_EntierLong neg_b = {1, {3}};
    t_EntierLong sub_neg_result = sub(neg_a, neg_b);
    
    TEST_ASSERT_EQUAL(1, sub_neg_result.negatif);
    int expected_sub_gen2[1] = {7};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen2, sub_neg_result.chiffres, 1);

    // Test 3: Soustraction positif - négatif (5 - (-3) = 8)
    t_EntierLong pos_num = {0, {5}};
    t_EntierLong neg_num = {1, {3}};
    t_EntierLong sub_result1 = sub(pos_num, neg_num);
    
    TEST_ASSERT_EQUAL(0, sub_result1.negatif);
    int expected_sub_gen3[1] = {8};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen3, sub_result1.chiffres, 1);

    // Test 4: Soustraction avec retenue - plusieurs chiffres (123 - 45 = 78)
    t_EntierLong large_pos = {0, {3, 2, 1}};  // 123
    t_EntierLong medium_pos = {0, {5, 4}};     // 45
    t_EntierLong sub_multi_result1 = sub(large_pos, medium_pos);
    
    TEST_ASSERT_EQUAL(0, sub_multi_result1.negatif);
    int expected_sub_gen4[2] = {8, 7}; // 78 selon ton format
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen4, sub_multi_result1.chiffres, 2);

    // Test 5: Soustraction avec résultat négatif - plusieurs chiffres (45 - 123 = -78)
    t_EntierLong small_multi = {0, {5, 4}};     // 45
    t_EntierLong large_multi = {0, {3, 2, 1}};  // 123
    t_EntierLong sub_multi_result2 = sub(small_multi, large_multi);
    
    TEST_ASSERT_EQUAL(1, sub_multi_result2.negatif);
    int expected_sub_gen5[2] = {8, 7}; // -78 selon ton format
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen5, sub_multi_result2.chiffres, 2);

    // Test 6: Soustraction négatif - positif avec plusieurs chiffres (-56 - 34 = -90)
    t_EntierLong neg_multi = {1, {6, 5}};      // -56
    t_EntierLong pos_multi = {0, {4, 3}};      // 34
    t_EntierLong sub_multi_result3 = sub(neg_multi, pos_multi);
    
    TEST_ASSERT_EQUAL(1, sub_multi_result3.negatif);
    int expected_sub_gen6[2] = {0, 9}; // -90 selon ton format
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen6, sub_multi_result3.chiffres, 2);

    // Test 7: Soustraction avec retenue complexe (1000 - 999 = 1)
    t_EntierLong thousand = {0, {0, 0, 0, 1}};  // 1000
    t_EntierLong nine_nine_nine = {0, {9, 9, 9}}; // 999
    t_EntierLong sub_complex_result = sub(thousand, nine_nine_nine);
    
    TEST_ASSERT_EQUAL(0, sub_complex_result.negatif);
    int expected_sub_gen7[1] = {1};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen7, sub_complex_result.chiffres, 1);

    // Test 8: Soustraction identiques avec plusieurs chiffres (456 - 456 = 0)
    t_EntierLong same_multi_a = {0, {6, 5, 4}};  // 456
    t_EntierLong same_multi_b = {0, {6, 5, 4}};  // 456
    t_EntierLong sub_same_multi = sub(same_multi_a, same_multi_b);
    
    TEST_ASSERT_EQUAL(0, sub_same_multi.negatif);
    int expected_sub_gen8[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_sub_gen8, sub_same_multi.chiffres, 1);
}

void test_multiplication(void) {
    // ===== TEST MULTIPLICATION =====
    
    // Test 1: Multiplication positifs simples (5 × 4 = 20)
    t_EntierLong mult_a = {0, {5}};
    t_EntierLong mult_b = {0, {4}};
    t_EntierLong mult_result1 = multiplication(mult_a, mult_b);
    
    TEST_ASSERT_EQUAL(0, mult_result1.negatif);
    int expected_mult1[2] = {0,2};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_mult1, mult_result1.chiffres, 2);

    // Test 2: Multiplication avec signes différents (positif × négatif = négatif)
    t_EntierLong mult_pos = {0, {3}};
    t_EntierLong mult_neg = {1, {7}};
    t_EntierLong mult_result2 = multiplication(mult_pos, mult_neg);
    
    TEST_ASSERT_EQUAL(1, mult_result2.negatif);
    int expected_mult2[2] = {1,2};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_mult2, mult_result2.chiffres, 2);

    // Test 3: Multiplication de deux négatifs (négatif × négatif = positif)
    t_EntierLong mult_neg_a = {1, {6}};
    t_EntierLong mult_neg_b = {1, {2}};
    t_EntierLong mult_result3 = multiplication(mult_neg_a, mult_neg_b);
    
    TEST_ASSERT_EQUAL(0, mult_result3.negatif);
    int expected_mult3[2] = {2,1};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_mult3, mult_result3.chiffres, 2);

    // Test 4: Multiplication par zéro (8 × 0 = 0)
    t_EntierLong mult_number = {0, {8}};
    t_EntierLong mult_zero = {0, {0}};
    t_EntierLong mult_zero_result = multiplication(mult_number, mult_zero);
    
    TEST_ASSERT_EQUAL(0, mult_zero_result.negatif);
    int expected_mult4[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_mult4, mult_zero_result.chiffres, 1);

    // Test 5: Multiplication par 1 (9 × 1 = 9)
    t_EntierLong mult_num = {0, {9}};
    t_EntierLong mult_one = {0, {1}};
    t_EntierLong mult_one_result = multiplication(mult_num, mult_one);
    
    TEST_ASSERT_EQUAL(0, mult_one_result.negatif);
    int expected_mult5[1] = {9};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_mult5, mult_one_result.chiffres, 1);

    // Test 6: Multiplication avec retenue (9 × 9 = 81, format: {1, 8})
    t_EntierLong mult_carry_a = {0, {9}};
    t_EntierLong mult_carry_b = {0, {9}};
    t_EntierLong mult_carry_result = multiplication(mult_carry_a, mult_carry_b);
    
    TEST_ASSERT_EQUAL(0, mult_carry_result.negatif);
    int expected_mult6[2] = {1, 8}; // 81 stocké comme {1, 8} selon ton format
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_mult6, mult_carry_result.chiffres, 2);

    // Test 7: Multiplication de zéros (-0 × 0 = 0)
    t_EntierLong mult_zero_a = {1, {0}};
    t_EntierLong mult_zero_b = {0, {0}};
    t_EntierLong mult_double_zero = multiplication(mult_zero_a, mult_zero_b);
    
    TEST_ASSERT_EQUAL(1, mult_double_zero.negatif);
    int expected_mult7[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_mult7, mult_double_zero.chiffres, 1);
}

void test_division(void) {
    // ===== TEST DIVISION EUCLIDIENNE =====
    
    // Test 1: Division simple positif (20 ÷ 4 = 5 reste 0)
    t_EntierLong dividende1 = {0, {0,2}};
    t_EntierLong diviseur1 = {0, {4}};
    t_EntierLong quotient1, reste1;
    
    divisionEuclidienne(dividende1, diviseur1, quotient1, reste1);
    
    TEST_ASSERT_EQUAL(0, quotient1.negatif);
    int expected_quotient1[1] = {5};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_quotient1, quotient1.chiffres, 1);
    
    TEST_ASSERT_EQUAL(0, reste1.negatif);
    int expected_reste1[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reste1, reste1.chiffres, 1);

    // Test 2: Division avec reste (23 ÷ 5 = 4 reste 3)
    t_EntierLong dividende2 = {0, {3,2}};
    t_EntierLong diviseur2 = {0, {5}};
    t_EntierLong quotient2, reste2;
    
    divisionEuclidienne(dividende2, diviseur2, quotient2, reste2);
    
    TEST_ASSERT_EQUAL(0, quotient2.negatif);
    int expected_quotient2[1] = {4};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_quotient2, quotient2.chiffres, 1);
    
    TEST_ASSERT_EQUAL(0, reste2.negatif);
    int expected_reste2[1] = {3};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reste2, reste2.chiffres, 1);

    // Test 3: Division positif ÷ négatif (-15 ÷ 3 = -5 reste 0)
    t_EntierLong dividende3 = {1, {5,1}};  // -15
    t_EntierLong diviseur3 = {0, {3}};    // 3
    t_EntierLong quotient3, reste3;
    
    divisionEuclidienne(dividende3, diviseur3, quotient3, reste3);
    
    TEST_ASSERT_EQUAL(1, quotient3.negatif);  // Quotient négatif
    int expected_quotient3[1] = {5};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_quotient3, quotient3.chiffres, 1);
    
    TEST_ASSERT_EQUAL(1, reste3.negatif);    // Reste a le signe du dividende
    int expected_reste3[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reste3, reste3.chiffres, 1);

    // Test 4: Division par 1 (42 ÷ 1 = 42 reste 0)
    t_EntierLong dividende4 = {0, {2,4}};
    t_EntierLong diviseur4 = {0, {1}};
    t_EntierLong quotient4, reste4;
    
    divisionEuclidienne(dividende4, diviseur4, quotient4, reste4);
    
    TEST_ASSERT_EQUAL(0, quotient4.negatif);
    int expected_quotient4[2] = {2,4};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_quotient4, quotient4.chiffres, 2);
    
    TEST_ASSERT_EQUAL(0, reste4.negatif);
    int expected_reste4[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reste4, reste4.chiffres, 1);

    // Test 5: Division avec plusieurs chiffres (156 ÷ 12 = 13 reste 0)
    t_EntierLong dividende5 = {0, {6, 5, 1}};  // 156
    t_EntierLong diviseur5 = {0, {2, 1}};      // 12
    t_EntierLong quotient5, reste5;
    
    divisionEuclidienne(dividende5, diviseur5, quotient5, reste5);
    
    TEST_ASSERT_EQUAL(0, quotient5.negatif);
    int expected_quotient5[2] = {3, 1};  // 13
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_quotient5, quotient5.chiffres, 2);
    
    TEST_ASSERT_EQUAL(0, reste5.negatif);
    int expected_reste5[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reste5, reste5.chiffres, 1);

    // Test 6: Division par zéro (devrait échouer)
    exit_called = 0;
    t_EntierLong dividende6 = {0, {10}};
    t_EntierLong diviseur_zero = {0, {0}};
    t_EntierLong quotient6, reste6;
    
    if (setjmp(test_exit_jmp) == 0) {
        divisionEuclidienne(dividende6, diviseur_zero, quotient6, reste6);
        TEST_FAIL_MESSAGE("Expected exit() for division by zero");
    } else {
        TEST_ASSERT_EQUAL(EXIT_FAILURE, exit_called);
    }

    // Test 7: Division plus petit ÷ plus grand (3 ÷ 10 = 0 reste 3)
    exit_called = 0;
    t_EntierLong dividende7 = {0, {3}};
    t_EntierLong diviseur7 = {0, {0,1}};
    t_EntierLong quotient7, reste7;
    
    divisionEuclidienne(dividende7, diviseur7, quotient7, reste7);
    
    TEST_ASSERT_EQUAL(0, quotient7.negatif);
    int expected_quotient7[1] = {0};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_quotient7, quotient7.chiffres, 1);
    
    TEST_ASSERT_EQUAL(0, reste7.negatif);
    int expected_reste7[1] = {3};
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_reste7, reste7.chiffres, 1);
}


int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_convertInt_Entierlong);
    RUN_TEST(test_EntierLongIsEqual);
    RUN_TEST(test_initialize);
    RUN_TEST(test_abs_comparison);
    RUN_TEST(test_add);
    RUN_TEST(test_sub);
    RUN_TEST(test_add_general);
    RUN_TEST(test_sub_general);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_division);
    
    return UNITY_END();
}