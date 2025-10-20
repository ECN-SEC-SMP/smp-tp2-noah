#pragma once
//#define TEST_UNITY

/*
fichier entierlong.h
pour définir le type t_EntierLong en C++ 
*/
#ifndef TEST_UNITY
const int MAXCHIFFRES = 420; // pour fibonacci
#else
const int MAXCHIFFRES = 18; // pour les tests unity
#endif

struct t_EntierLong
{
	bool negatif;
	int chiffres[MAXCHIFFRES];
};
