#pragma once
#include "entierlong.h"

using namespace std;

t_EntierLong addSameSign(t_EntierLong n1, t_EntierLong n2);
t_EntierLong subtractionSameSign(t_EntierLong n1, t_EntierLong n2);
t_EntierLong add(t_EntierLong n1, t_EntierLong n2);
t_EntierLong sub(t_EntierLong n1, t_EntierLong n2);
t_EntierLong multiplication(t_EntierLong n1, t_EntierLong n2);
void divisionEuclidienne(t_EntierLong dividende, t_EntierLong diviseur, t_EntierLong &quotient, t_EntierLong &reste);




