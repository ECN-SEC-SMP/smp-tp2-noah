#pragma once

/*
fichier entierlong.h
pour définir le type t_EntierLong en C++ 
*/

const int MAXCHIFFRES = 20;

struct t_EntierLong
{
	bool negatif;
	int chiffres[MAXCHIFFRES];
};
