
// MFC_TP3_videoDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "MFC_TP3_video.h"
#include "MFC_TP3_videoDlg.h"
#include "afxdialogex.h"
#include <Vfw.h>
#include "Ima.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*****************************
CMFC_TP3_videoDlg *pDial;					// pDiad :est un pointeur vers une boite de dialogue qui comporte : Hauteur, Largeur,... Imrgb(vecteur de stockage d'image)....

// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	unsigned char * Imrgb= NULL; //******************* ajout pointeur

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// boîte de dialogue CMFC_TP3_videoDlg



CMFC_TP3_videoDlg::CMFC_TP3_videoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_TP3_VIDEO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC_TP3_videoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC_TP3_videoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC_TP3_videoDlg::OnBnClickedOk)
	ON_BN_CLICKED(m_init, &CMFC_TP3_videoDlg::OnBnClickedinit)
	ON_BN_CLICKED(m_videoFormat, &CMFC_TP3_videoDlg::OnBnClickedvideoformat)
	ON_BN_CLICKED(m_videoSource, &CMFC_TP3_videoDlg::OnBnClickedvideosource)
	ON_BN_CLICKED(m_traitement, &CMFC_TP3_videoDlg::OnBnClickedtraitement)
	ON_BN_CLICKED(m_inversion, &CMFC_TP3_videoDlg::OnBnClickedinversion)
	ON_BN_CLICKED(m_seuillage, &CMFC_TP3_videoDlg::OnBnClickedseuillage)
	ON_BN_CLICKED(m_rotation, &CMFC_TP3_videoDlg::OnBnClickedrotation)
	ON_BN_CLICKED(IDCANCEL, &CMFC_TP3_videoDlg::OnBnClickedCancel)
	ON_BN_CLICKED(m_flou, &CMFC_TP3_videoDlg::OnBnClickedflou)
	ON_BN_CLICKED(m_IMAGE_ORIGINALE, &CMFC_TP3_videoDlg::OnBnClickedImageOriginale)
END_MESSAGE_MAP()


// gestionnaires de messages pour CMFC_TP3_videoDlg

BOOL CMFC_TP3_videoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO: ajoutez ici une initialisation supplémentaire

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CMFC_TP3_videoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CMFC_TP3_videoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CMFC_TP3_videoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC_TP3_videoDlg::OnBnClickedOk()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	free(Imrgb);
	free(imInter);
	CDialogEx::OnOK();
}

void CMFC_TP3_videoDlg::OnBnClickedCancel()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
	free(Imrgb);
	free(imInter);
	CDialogEx::OnCancel();
}

bool b = false;// b: variable globale de sécurité(il faut actionner le bouton 'init' pour pouvoir accéder au boutons:'Format' et 'Source' )
void CMFC_TP3_videoDlg::OnBnClickedinit()
{
	if (!b) {
		b = true;
		pDial = this; //******* initialiser le pointeur pour l'utilise dans le CIma (traitement d'image).
		hWndC = capCreateCaptureWindow(L"Fenetre de Capture", WS_CHILD | WS_VISIBLE, 0, 0, 640, 480, m_hWnd, 0);
		capDriverConnect(hWndC, 0);//La macro (fonction) capDriverConnect connecte une fenêtre de capture à un pilote de capture.
		capPreviewRate(hWndC, 40);//La macro capPreviewRate définit la fréquence d'affichage des images en mode aperçu.
		capPreview(	hWndC, TRUE);//La macro capPreview active ou désactive le mode d'aperçu. En mode aperçu, les images sont transférées du matériel de capture vers la mémoire système, puis affichées dans la fenêtre de capture à l'aide des fonctions 
		//*****************************
		// La structure CAPSTATUS définit l'état actuel de la fenêtre de capture.
		CAPSTATUS capStatus;  // capStatus : variable de type CAPSTATUS, avec plusieur paramètres associés à cette variable.
		capGetStatus(hWndC, &capStatus, sizeof(capStatus)); // Fonction qui retrouve le statusde la capture window.
		Largeur = capStatus.uiImageWidth; // retourner la largeur  de la fenètre de capture
		Hauteur = capStatus.uiImageHeight;// retourner l'Hauteur de la fenètre de capture
		//************************************* Allocation mémoire pour le pointeur Imrgb:
		if (Imrgb != NULL) { free(Imrgb); }
		Imrgb = (unsigned char *)malloc(Largeur * Hauteur * 3 * sizeof(unsigned char *));

		if (imInter != NULL) { free(imInter); }
		imInter = (unsigned char *)malloc(Largeur * Hauteur * 3 * sizeof(unsigned char *));
	}

}
//********************************************************
void CMFC_TP3_videoDlg::OnBnClickedvideoformat()
{
	if (b) {// b: variable globale de sécurité(il faut actionner le bouton 'init' pour pouvoir accéder au bouton 'Source' )
		capDlgVideoFormat(hWndC);

		// Mise à jour de Largeur et Hauteur si la fonction format applique un changement.
		CAPSTATUS capStatus;
		capGetStatus(hWndC, &capStatus, sizeof(capStatus));
		Largeur = capStatus.uiImageWidth;
		Hauteur = capStatus.uiImageHeight;
	}
}

void CMFC_TP3_videoDlg::OnBnClickedvideosource()
{
	if (b) 	capDlgVideoSource(hWndC);  // b: variable globale de sécurité(il faut actionner 
									   //  le bouton 'init' pour pouvoir accéder au bouton 'Source' )
}


void CMFC_TP3_videoDlg::OnBnClickedtraitement()
{
	pDial->choixTraitement = 0;
	capSetCallbackOnFrame(hWndC, CMFC_TP3_videoDlg::Traitement);
}

LPVOID CALLBACK CMFC_TP3_videoDlg::Traitement(HWND hWndC, LPVIDEOHDR pV)
{	unsigned char *PImage;
	PImage = pV->lpData; // PImage devient le pointeur vers les données
	CIma Ima;
	Ima.ConvertYUY2RGB(pV->lpData, pDial->Imrgb, pDial->Largeur, pDial->Hauteur);
		// passage en RGB 24 bits , résultat dans Imrgb 
		// pv->lpData: pointe vers l'image d'entrée (prise par la camera)
		// pDial->Imrgb: pointeur de destination (stockage image recu par camera, pour faire le traitement).
	//**********************************************
	switch (pDial->choixTraitement)
	{	case 1:		Ima.inversion(pDial->Imrgb, pDial->Largeur, pDial->Hauteur); // traitement de Imrgb en RGB 24 bits 
			break;
		case 2:
				Ima.seuillage(pDial->Imrgb, pDial->Largeur, pDial->Hauteur); // traitement de Imrgb en RGB 24 bits 		
			break;	
		case 3:
				Ima.rotation(pDial->Imrgb, pDial->imInter, pDial->Largeur, pDial->Hauteur, (3.1415/2));//utilisation d'angle en radian.		
			break;
		case 4:
				Ima.blur(pDial->Imrgb, pDial->Largeur, pDial->Hauteur);		
			break;
		case 6: //ce cas est utiliser pour retourner à l'image original après un traitement, pour eviter de fermer et réouvrir à nouveau 
				// la boite de dialogue:
			// ********* Zone qui reste vide.		
			break;
		default:	Ima.Contour(pDial->Imrgb, pDial->Largeur, pDial->Hauteur); // traitement de Imrgb en RGB 24 bits 
				
			break;
	}
	Ima.ConvertRGBYUY2(pDial->Imrgb, pV->lpData, pDial->Largeur, pDial->Hauteur); // passage en YUY2		
return 0;
}


void CMFC_TP3_videoDlg::OnBnClickedinversion()
{
	pDial->choixTraitement = 1;
	capSetCallbackOnFrame(hWndC, CMFC_TP3_videoDlg::Traitement);
}

void CMFC_TP3_videoDlg::OnBnClickedseuillage()
{
	pDial->choixTraitement = 2;
	capSetCallbackOnFrame(hWndC, CMFC_TP3_videoDlg::Traitement);
}


void CMFC_TP3_videoDlg::OnBnClickedrotation()
{
	pDial->choixTraitement = 3;
	capSetCallbackOnFrame(hWndC, CMFC_TP3_videoDlg::Traitement);
}



void CMFC_TP3_videoDlg::OnBnClickedflou()
{
	pDial->choixTraitement = 4;
	capSetCallbackOnFrame(hWndC, CMFC_TP3_videoDlg::Traitement);
}

void CMFC_TP3_videoDlg::OnBnClickedImageOriginale()
{
	pDial->choixTraitement = 6;
	capSetCallbackOnFrame(hWndC, CMFC_TP3_videoDlg::Traitement);
}
