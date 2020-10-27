
// MFC_TP3_videoDlg.h : fichier d'en-tête
//

#pragma once
#include <Vfw.h>

// boîte de dialogue CMFC_TP3_videoDlg
class CMFC_TP3_videoDlg : public CDialogEx
{
// Construction
public://************************************************************************************ Classe qui gere la video
	CMFC_TP3_videoDlg(CWnd* pParent = NULL);	// constructeur standard
	HWND hWndC; // variable membre de la classe CMFC_TP3_videoDlg(classe principale).
	int Largeur, Hauteur;
	unsigned char * Imrgb = NULL;
	
	unsigned char * imInter = NULL;
	
	int choixTraitement =0;  // variable qui sert à choisir quel type de traitement on opte pour.
	//************* fonctions membres
	static LPVOID CALLBACK Traitement(HWND hWndC, LPVIDEOHDR pV);



// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_TP3_VIDEO_DIALOG };
#endif

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedinit();
	afx_msg void OnBnClickedvideoformat();
//	afx_msg void OnBnClickedvideoformat2();
	afx_msg void OnBnClickedvideosource();
	afx_msg void OnBnClickedtraitement();
	//********************
	
	afx_msg void OnBnClickedinversion();
	afx_msg void OnBnClickedseuillage();
	afx_msg void OnBnClickedrotation();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedflou();
	afx_msg void OnBnClickedImageOriginale();
};
