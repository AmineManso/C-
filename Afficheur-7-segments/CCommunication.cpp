//  CCommunication .cpp  

#include "stdafx.h"
#include "Communication.h"
#include "DialBoitier.h"

////********************
//#include <SFML/Graphics.hpp>

CCommunication::CCommunication()
{
}

CCommunication::~CCommunication()
{
}

CCommunication::CCommunication(CDialBoitier * ptra)
{
	ptrCDialBoitier = ptra;	 //ptrCDialBoitier : variable memebre de la classe CComunication
}

void CCommunication::EcrireValeur(int valeur, int numAfficheur) // valeur : en decimal  /  numAfficheur: numero de l'afficheur voulu.
{
	//codage de l'afficheur 7 segments :
	int tab[23] = { 0x3F , 0x30, 0x6D, 0x79 ,0x72, 0x5B, 0x5F, 0x31, 0x7F, 0x7B, 0xBF, 0xB0, 0xED, 0xF9,  0xF2, 0xDB ,0xDF,0xB1,0xFF,0xFB, 0x4F, 0xCF };
	// condition qui nous pérmet de passer vers le deuxiéme afficheur:
	if (numAfficheur == 1) numAfficheur += 9;
	// affichage de "valeur" sur le port A:
	if(ptrCDialBoitier->actif)ptrCDialBoitier->outp(tab[valeur + numAfficheur], 0x278);
}

void CCommunication::EcrireMot(int valeurMot)
{
	int reste = 0;
	int resultatDivision;

	if (valeurMot <= 9) {
		CCommunication::EcrireValeur(valeurMot, 1);
		CCommunication::EcrireValeur(0, 0);
	}
	else
	{
		if (valeurMot > 99 ||  valeurMot < 0) {
			CCommunication::EcrireValeur(0, 0); 
			CCommunication::EcrireValeur(11, 1); // 11 <=> à Erreur, dans l'afficheur 1. 	
		}
		else {
			resultatDivision = (int)(valeurMot / 10);
			reste = valeurMot % 10;
			CCommunication::EcrireValeur(resultatDivision, 0);
			CCommunication::EcrireValeur(reste, 1);
		}
	}
}

void CCommunication::boucleAfficheur()
{
	int i = 0;
	while (i < 100 && (ptrCDialBoitier->actif == true))    //!(Keyboard::isKeyPressed(Keyboard::Left) )
	// actif : variable membre de CDialBoitier qui sert à fermer la boite de dialogue pDial. 
	{
		EcrireMot(i); 
		Sleep(50);
		i++;
	}	

	/*
	for (int i = 0; i < 100; i++)
	{
		if (!ptrCDialBoitier->actif) break;
		EcrireMot(i);
		Sleep(100);
	}
	*/
}

void CCommunication::affVitesseMoteur(CDialBoitier *ptr)
{
	//ptr->m_Marche = true;
	while(ptr->m_Marche == true) {
		ptr->CDialBoitier::OnBnClickedCheck1();
		int val =  (ptr->inp(0x279));//0
		
		//if (ptr->m_Marche) ptr->VitesseMoteur = (double)rand() / (RAND_MAX + 1) * (0x50 - 0x00) + 0x00 ; //    		// vitesse entre 0x10 et 0x210
		//else ptr->VitesseMoteur = 0;

		EcrireMot(val);
		Sleep(300);
	}
}
