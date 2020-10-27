
// MFC_TP3_video.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux


// CMFC_TP3_videoApp :
// Consultez MFC_TP3_video.cpp pour l'implémentation de cette classe
//

class CMFC_TP3_videoApp : public CWinApp
{
public:
	CMFC_TP3_videoApp();

// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CMFC_TP3_videoApp theApp;
