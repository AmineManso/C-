//*****  Cima.cpp

#include "stdafx.h"
#include "Ima.h"


CIma::CIma()
{
}

CIma::~CIma()
{
}

byte CIma::clip(int a)
{
	if (a>255) return  (byte)255;
	if (a<0) return  (byte)0;
	return (byte)a;
}

void CIma::ConvertYUY2RGB(BYTE *PtrIn, BYTE *ptrOut, int Larg, int Haut)
{
	int Larg2 = Larg / 2;
	byte r, g, b;
	byte y, u, v;
	byte *pIm = PtrIn;
	int p, l, c, col, c4;
	int y0, u0, v0, y1;

	p = 0;
	for (l = 0; l<Haut; l++)
	{
		for (c = 0; c<Larg2; c++)
		{
			y0 = pIm[0];
			u0 = pIm[1];
			y1 = pIm[2];
			v0 = pIm[3];
			pIm += 4;
			int c = y0 - 16;
			int d = u0 - 128;
			int e = v0 - 128;
			ptrOut[p + 0] = clip((298 * c + 516 * d + 128) >> 8); // blue
			ptrOut[p + 1] = clip((298 * c - 100 * d - 208 * e + 128) >> 8); // green
			ptrOut[p + 2] = clip((298 * c + 409 * e + 128) >> 8); // red

			p += 3;

			c = y1 - 16;
			ptrOut[p + 0] = clip((298 * c + 516 * d + 128) >> 8); // blue
			ptrOut[p + 1] = clip((298 * c - 100 * d - 208 * e + 128) >> 8); // green
			ptrOut[p + 2] = clip((298 * c + 409 * e + 128) >> 8); // red
			p += 3;
		}
	}
}

void CIma::ConvertRGBYUY2(BYTE *ptrIn, BYTE *pyuv, int Larg, int Haut)
{	float R, G, B, Y, U, V;
	int p, l, c, col, c4;
	int Larg2 = Larg / 2;
	byte *pIm = ptrIn;
	byte y, u, v;
	col = 0;
	p = 0;
	for (l = 0; l < Haut; l++)
	{
		for (c = 0; c < Larg; c++)
		{
			R = (float)pIm[p + 2];   //R
			G = (float)pIm[p + 1]; // G
			B = (float)pIm[p];  // B
			Y = (0.256788 * R + 0.504129 * G + 0.097906 * B) + 16;
			U = (-0.148223 * R - 0.290993 * G + 0.439216 * B) + 128;
			V = (0.439216 * R - 0.367788 * G - 0.071427 * B) + 128;

			pyuv[col + 0] = (byte)Y;
			pyuv[col + 1] = (byte)U;
			pyuv[col + 3] = (byte)V;
			c++;
			p += 3;
			R = (float)pIm[p + 2];   //R
			G = (float)pIm[p + 1]; // G
			B = (float)pIm[p];  // B
			Y = (0.256788 * R + 0.504129 * G + 0.097906 * B) + 16;
			y = (byte)Y;
			pyuv[col + 2] = y;
			col += 4;
			p += 3;
		}
	}
}
//*********************************************************************************************************
void CIma::Contour(unsigned char * ImrgbPtr, int Larg, int Haut)
{
	int colorIdx = 0;	
	int x00, x01, x10, x11;
	for (int i = 0; i <Haut - 1; i++) {
		for (int j = 0; j < Larg - 1; j++) {

		for (colorIdx = 0; colorIdx < 3; colorIdx++) {
				x00 = (i * Larg + j) * 3 + colorIdx;	
				x01 = (i * Larg + (j+1)) * 3 + colorIdx;
				x10 = ((i+1) * Larg  + j) * 3 + colorIdx;
				x11 = ((i+1) * Larg + (j+1)) * 3 + colorIdx;
ImrgbPtr[x00] = (int) sqrt((ImrgbPtr[x00] - ImrgbPtr[x11])*(ImrgbPtr[x00] - ImrgbPtr[x11])  +  (ImrgbPtr[x01] - ImrgbPtr[x10])*(ImrgbPtr[x01] - ImrgbPtr[x10]));
			}
		}
	}
}

	
void CIma::inversion(unsigned char * ImrgbPtr, int Larg, int Haut)
{
	int colorIdx = 0;
	int x00, x01, x10, x11;
	for (int i = 0; i < Haut - 1; i++) {
		for (int j = 0; j < Larg - 1; j++) {
			for (colorIdx = 0; colorIdx < 3; colorIdx++) {
				x00 = (i * Larg + j) * 3 + colorIdx;
				ImrgbPtr[x00] = 255 - ImrgbPtr[x00];
			}
		}
	}
}

void CIma::seuillage(unsigned char * ImrgbPtr, int Larg, int Haut)
{
	int colorIdx = 0;
	int seuil = 130;
	int x00, x01, x10, x11;
	for (int i = 0; i < Haut - 1; i++) {
		for (int j = 0; j < Larg - 1; j++) {
			for (colorIdx = 0; colorIdx < 3; colorIdx++) {
				x00 = (i * Larg + j) * 3 + colorIdx;
				if (ImrgbPtr[x00] > seuil) {    // seuil = 130 : seuil arbitraire.
					ImrgbPtr[x00] = 255;		// 255 : couleur blanche
				}
				else ImrgbPtr[x00] = 0;			// 0 : couleur noire.
			}
		}
	}
}

void CIma::blur(unsigned char * ImrgbPtr, int Larg, int Haut)
{	int colorIdx = 0;
	int x00, x01,x02, x03, x04,   x10, x11, x12, x13, x14,  x20, x21, x22, x23, x24, x30, x31, x32, x33, x34, x40, x41, x42, x43, x44;
	for (int i = 0; i < Haut - 4; i++) {
		for (int j = 0; j < Larg - 4; j++) {
			for (colorIdx = 0; colorIdx < 3; colorIdx++) {
				x00 = (i * Larg + j) * 3 + colorIdx;
				x01 = (i * Larg + (j + 1)) * 3 + colorIdx;
				x02 = (i * Larg + (j + 2)) * 3 + colorIdx;
				x03 = (i * Larg + (j + 3)) * 3 + colorIdx;
				x04 = (i * Larg + (j + 4)) * 3 + colorIdx;
				
				x10 = ((i + 1) * Larg + j) * 3 + colorIdx;
				x11 = ((i + 1) * Larg + (j + 1)) * 3 + colorIdx;
				x12 = ((i + 1) * Larg + (j + 2)) * 3 + colorIdx;
				x13 = ((i + 1) * Larg + (j + 3)) * 3 + colorIdx;
				x14 = ((i + 1) * Larg + (j + 4)) * 3 + colorIdx;
				
				x20 = ((i + 2) * Larg + j) * 3 + colorIdx;
				x21 = ((i + 2) * Larg + (j + 1)) * 3 + colorIdx;
				x22 = ((i + 2) * Larg + (j + 2)) * 3 + colorIdx;
				x23 = ((i + 2) * Larg + (j + 3)) * 3 + colorIdx;
				x24 = ((i + 2) * Larg + (j + 4)) * 3 + colorIdx;

				x30 = ((i + 3) * Larg + j) * 3 + colorIdx;
				x31 = ((i + 3) * Larg + (j + 1)) * 3 + colorIdx;
				x32 = ((i + 3) * Larg + (j + 2)) * 3 + colorIdx;
				x33 = ((i + 3) * Larg + (j + 3)) * 3 + colorIdx;
				x34 = ((i + 3) * Larg + (j + 4)) * 3 + colorIdx;

				x40 = ((i + 4) * Larg + j) * 3 + colorIdx;
				x41 = ((i + 4) * Larg + (j + 1)) * 3 + colorIdx;
				x42 = ((i + 4) * Larg + (j + 2)) * 3 + colorIdx;
				x43 = ((i + 4) * Larg + (j + 3)) * 3 + colorIdx;
				x44 = ((i + 4) * Larg + (j + 4)) * 3 + colorIdx;

				ImrgbPtr[x00] = (int)((	  1 * ImrgbPtr[x00] + 4 * ImrgbPtr[x01] + 6 * ImrgbPtr[x02]  + 4 * ImrgbPtr[x03] + 1 * ImrgbPtr[x04]
										+4 * ImrgbPtr[x10] + 16 * ImrgbPtr[x11] + 24 * ImrgbPtr[x12] + 16 * ImrgbPtr[x13] + 4 * ImrgbPtr[x14]
										+6 * ImrgbPtr[x20] + 24 * ImrgbPtr[x21] + 36 * ImrgbPtr[x22] + 24 * ImrgbPtr[x23] + 6 * ImrgbPtr[x24]
										+4 * ImrgbPtr[x30] + 16 * ImrgbPtr[x31] + 24 * ImrgbPtr[x32] + 16 * ImrgbPtr[x33] + 4 * ImrgbPtr[x34]
										+ 1 * ImrgbPtr[x40] + 4 * ImrgbPtr[x41] + 6 * ImrgbPtr[x42]  + 4 * ImrgbPtr[x43] + 1 * ImrgbPtr[x44]) / 256);
			}
		}
	}
}
//// For a 3x3 Gaussien Kernel
/*				ImrgbPtr[x00] =(int)( (    1*ImrgbPtr[x00] + 2*ImrgbPtr[x01] + 4*ImrgbPtr[x02] + 2*ImrgbPtr[x03] + 1*ImrgbPtr[x04]
							 + 2*ImrgbPtr[x10] + 4*ImrgbPtr[x11] + 8*ImrgbPtr[x12] + 4 * ImrgbPtr[x13] +  2 * ImrgbPtr[x14]
							 + 1*ImrgbPtr[x20] + 2*ImrgbPtr[x21] + 4*ImrgbPtr[x22] + 2 * ImrgbPtr[x23] + 1 * ImrgbPtr[x24]) / 38);
*/

void CIma::rotation(unsigned char * ImrgbPtr,  unsigned char *imInterPtr,  int Larg, int Haut, double angle)
{
	int colorIdx = 0;
	int idxI, idxJ, Taille = (Haut * Larg * 3);
	for (int i = 0; i < Haut - 1; i++) {
		for (int j = 0; j < Larg - 1; j++) {
					
			int t1 = (sin(angle)* j + cos(angle)* i);
			int t2 = (cos(angle)* j - sin(angle)* i);

			for (colorIdx = 0; colorIdx < 3; colorIdx++) {
				idxI = (int) ((i * Larg + j) * 3 + colorIdx); //  compression d'image pour idxI => idxI = position *2;
				idxJ = (int) ((t1 * Larg + t2) * 3 + colorIdx); //  compression d'image pour idwJ => idxJ= position /2;
				if((idxJ >= 0) && (idxJ < Taille)  && (idxI != idxJ)) imInterPtr[idxJ] = ImrgbPtr[idxI];				
			}
		}
	}

	for (int idx = 0; idx < (Larg * Haut *3); idx ++ ) {
		ImrgbPtr[idx] = imInterPtr[idx]; // restituer l'image dans la variable ImrgbPtr pour pouvoir l'afficher.
	}
}
//*************************************** Rotation avec effet miroire:
/*
void CIma::rotation(unsigned char * ImrgbPtr,  unsigned char *imInterPtr,  int Larg, int Haut, double angle)
{
	int colorIdx = 0;
	int idxI, idxJ, Taille = (Haut * Larg * 3);
	for (int i = 0; i < Haut - 1; i++) {
		for (int j = 0; j < Larg - 1; j++) {

			int t1 = (sin(angle)* j + cos(angle)* i);
			int t2 = (cos(angle)* j - sin(angle)* i);

			for (colorIdx = 0; colorIdx < 3; colorIdx++) {
				idxI = (int) (i * Larg + j) * 3 + colorIdx;
				idxJ = (int) ((t1 * Larg + t2) * 3 + colorIdx);
				if(idxJ >= 0 && idxJ < Taille  ) ImrgbPtr[idxJ] = ImrgbPtr[idxI]; // meme capture
			}
		}
	}
}
*/    //////////////////////////////////////////////////////////////////

////******************************** This part of code doen't work:
//***************************************** Multi-Threading Test :
/*int m_Hauteur ;
int m_Largeur ;
unsigned char * m_pImage ;

void CIma::PasseBasMultiThread(unsigned char * pImage, int Larg, int Haut)
{
	DWORD tid;
	HANDLE hTache[2];
	//
	 m_Hauteur = Haut;
	 m_Largeur = Larg;
	 m_pImage = pImage;
	//
	hTache[0] = CreateThread(NULL, 0, Filtre1, this, &tid );
	hTache[1] = CreateThread(NULL, 0, Filtre2, this, &tid );

	WaitForMultipleObjects(2, hTache, true, INFINITE);
	CloseHandle(hTache[0]);
	CloseHandle(hTache[1]);
}

DWORD WINAPI CIma::Filtre1(void * parametre) {
	CIma * pIma = (CIma *) parametre;
	pIma->Contour(m_pImage,m_Largeur, m_Hauteur );

}

DWORD WINAPI Filtre2(void * parametre){
	CIma * pIma = (CIma *)parametre;
	pIma->seuillage(m_pImage, m_Largeur, m_Hauteur);
}*/
///////////////////////////////////////////////////////////////////


