/*
fichier lit_ecrit.cxx
contient
	- l'action AfficheEntierLong(a)
	- la fonction LitEntierLong
*/

//inclusion de fichiers entetes

#include <iostream> //pour cout et cin
using namespace std;

#include <cstring> // pour strlen
//#include <ctype> // pour toascii

#include "../include/entierlong.h" //pour le type t_EntierLong


//fonction AfficheEntierLong(n)
//affiche sur l'ecran un t_EntierLong
void afficheEntierLong(t_EntierLong a)
{
    //variables
    int i,j;
    // debut
    // signe
    if (a.negatif)
    {
	   cout <<"-";
    }
    // Chiffres
    /* on recherche le 1er chiffre non nul (ou le chiffre des unites dans le cas
    d'un entier nul*/
    i=MAXCHIFFRES-1;
    while ((a.chiffres[i]==0)&&(i>0))
    {
    	i=i-1;
    }
    /*on ecrit les Chiffres "utiles"*/
    for(j=i;j>=0;j=j-1)
    {
    	cout << a.chiffres[j];
    }
    cout << endl;
    // fin
}

//fonction LitEntierLong
//lit au clavier un t_EntierLong
t_EntierLong litEntierLong()
{
    char Nb[MAXCHIFFRES+1];
    t_EntierLong a;
    int i,l;
    // debut
    cin >> Nb;
    a.negatif = (Nb[0]=='-');
    l=strlen(Nb);
    if ((a.negatif)||(Nb[0]=='+'))
    {
    	//on decale le caractere de fin de chaine d'un indice a gauche
    	for(i=0;i<l;i=i+1)
    	{
    		Nb[i]=Nb[i+1];
    	}
    	l=strlen(Nb);
    }
    for (i=0;i<l;i=i+1)
    {
    	a.chiffres[i] = toascii(Nb[l-1-i])-toascii('0');
    }
    // on complete par des 0
    for (i=l;i<MAXCHIFFRES;i=i+1)
    {
    	a.chiffres[i]=0;
    }
    return a;
    // fin
}
