// DialBoitier.h     **** pour la création de la boite de dialogue.
#pragma once
#include "resource.h"

// Boîte de dialogue CDialBoitier

class CDialBoitier : public CDialog
{
	DECLARE_DYNAMIC(CDialBoitier)

public:
	CDialBoitier(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CDialBoitier();
	//***************************
	bool actif= true;																	//******************************************
// Données de boîte de dialogue
	enum { IDD = IDD_DIALOG_BOITIER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_Marche;
	afx_msg void OnBnClickedCheck1();
	BYTE inp(WORD AdressePort);
	void outp(BYTE Val,WORD AdressePort);
	void Affiche7(BYTE val,int num);
	int VitesseMoteur;
	afx_msg void OnBnClickedCancel();
};
