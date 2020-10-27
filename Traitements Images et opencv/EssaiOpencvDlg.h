
// EssaiOpencvDlg.h : fichier d'en-tête
//

#pragma once

#include "cv.h"
#include "highgui.h"
#include "cxcore.h"
#include "cvaux.h"
// boîte de dialogue CEssaiOpencvDlg
class CEssaiOpencvDlg : public CDialogEx
{
// Construction
public:
	CEssaiOpencvDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ESSAIOPENCV_DIALOG };
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
	afx_msg void OnBnClickedButtonFiltre();
};
