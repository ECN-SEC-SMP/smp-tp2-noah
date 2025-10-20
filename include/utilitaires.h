#pragma once
#include "entierlong.h"
#include <string>
using namespace std;

// Prototypes des fonctions utilitaires
t_EntierLong convertInt_Entierlong(long long intToConvert);
bool EntierLongIsEqual(t_EntierLong a, t_EntierLong b);
bool EntierLongAbsComparison(t_EntierLong n1, t_EntierLong n2);
void initializeEntierLong(t_EntierLong &n);


