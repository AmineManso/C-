// CCommunication.h // 

#pragma once
#include "DialBoitier.h"

class CCommunication
{
private:
	CDialBoitier *ptrCDialBoitier;

public:
	CCommunication();
	CCommunication(CDialBoitier *ptra);
	~CCommunication();
//******
	void EcrireValeur(int valeur, int numAfficheur);
public:	
	void EcrireMot(int valeurMot); // valeurMot doit étre compriqe entre  0 < valeurMot < 99.

	void boucleAfficheur(); //voucle qui varie de 0 à 99.
	void affVitesseMoteur(CDialBoitier *ptr);
};


