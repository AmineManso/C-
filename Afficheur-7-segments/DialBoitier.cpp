// DialBoitier.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "SimAff7.h"
#include "DialBoitier.h"
#include "afxdialogex.h"
#include "Communication.h"


// Boîte de dialogue CDialBoitier

IMPLEMENT_DYNAMIC(CDialBoitier, CDialog)

CDialBoitier::CDialBoitier(CWnd* pParent /*=NULL*/)
	: CDialog(CDialBoitier::IDD, pParent)
	, m_Marche(FALSE)
{
	VitesseMoteur=0;
	actif = true;										//****************************************************************
}

CDialBoitier::~CDialBoitier()
{
}

void CDialBoitier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_Marche);
}


BEGIN_MESSAGE_MAP(CDialBoitier, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, &CDialBoitier::OnBnClickedCheck1)
	ON_BN_CLICKED(IDCANCEL, &CDialBoitier::OnBnClickedCancel)
END_MESSAGE_MAP()


// Gestionnaires de messages de CDialBoitier


void CDialBoitier::OnBnClickedCheck1()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	UpdateData(true); // mise à jour de m_Marche
	if (m_Marche) VitesseMoteur=(double)rand() / (RAND_MAX + 1) * (0x210 - 0x10) + 0x10; // vitesse entre 0x10 et 0x210
	else VitesseMoteur=0;
}


void CDialBoitier::outp(BYTE Val, WORD AdressePort)
{
	if (AdressePort==0x27A) // port C
	{
		//if (Val&0x20) // port A en sortie //
		//else
		//{
		// port A en entrée
	//	}
	}
	if (AdressePort==0x278) // port A
	{
		// Si A7=0, premier afficheur
		if ((Val&0x80) == 0)
		{
			Affiche7(Val,1);
		}
		// si A7=1, second afficheur
		else
		{
			Affiche7(Val,120);
		}
	}
	if (AdressePort==0x27B) // port B
	{
		// rien car on lit sur le port B
	}
}



BYTE CDialBoitier::inp(WORD Adresse)
{
	if (Adresse==0x279 || Adresse == 0)	return VitesseMoteur;
	else return 0;
}

void CDialBoitier::Affiche7(BYTE val,int num)
{
	CClientDC dc(this);

	
	//Invalidate(true);
	int Haut=100;
	int Larg=70;
	int x,y;
	x=30;y=30;
	CPen Stylo(PS_SOLID, 3, RGB(255,0,0));
	CPen StyloBlanc(PS_SOLID, 3, RGB(255,255,255));

	CRect rect;
	GetClientRect(rect);
	int Hautb=rect.Height();
	dc.SelectObject(&StyloBlanc);
	if (num==1) dc.Rectangle(0,Hautb,120,Hautb-(Haut+y+70));
	else dc.Rectangle(140,Hautb,250,Hautb-(Haut+y+70));
	dc.SelectObject(&Stylo);

	if (val&1) // allume A0
	{
		dc.MoveTo(x+num,Hautb-(y+Haut));
		dc.LineTo(x+num+Larg,Hautb-(y+Haut));
	}
	if (val&2) // allume A1
	{
		dc.MoveTo(x+num,Hautb-(y+Haut/2));
		dc.LineTo(x+num,Hautb-(y+Haut));
	}
	if (val&4) // allume A2
	{
		dc.MoveTo(x+num,Hautb-y);
		dc.LineTo(x+num,Hautb-(y+Haut/2));
	}
	if (val&8) // allume A3
	{
		dc.MoveTo(x+num,Hautb-y);
		dc.LineTo(x+num+Larg,Hautb-y);
	}
	if (val&0x10) // allume A4
	{
		dc.MoveTo(x+num+Larg,Hautb-y);
		dc.LineTo(x+num+Larg,Hautb-(y+Haut/2));
	}
	if (val&0x20) // allume A5
	{
		dc.MoveTo(x+num+Larg,Hautb-(y+Haut/2));
		dc.LineTo(x+num+Larg,Hautb-(y+Haut));
	}
	if (val&0x40) // allume A6
	{
		dc.MoveTo(x+num,Hautb-(y+Haut/2));
		dc.LineTo(x+num+Larg,Hautb-(y+Haut/2));
	}
	ReleaseDC(&dc);
}

void CDialBoitier::OnBnClickedCancel()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	
	CDialog::OnCancel();
	//delete(pDial);
	actif = false;
	
	
}
