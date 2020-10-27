
// SimAff7Dlg.h : fichier d'en-tête
//

#pragma once
#include "DialBoitier.h"

// boîte de dialogue CSimAff7Dlg
class CSimAff7Dlg : public CDialogEx
{
// Construction
public:
	CSimAff7Dlg(CWnd* pParent = NULL);	// constructeur standard
	enum { IDD = IDD_SIMAFF7_DIALOG };
	//***********************************************************************************************************************
	CDialBoitier *pDial; // necessaire pour utiliser le pointeur quand on clique sur Go ou dans la fonction OnTimer
	
// Données de boîte de dialogue
	

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;

	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
