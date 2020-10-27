///// CIma.h

#pragma once
#include <iostream>
using namespace std;

class CIma
{
public:
	CIma();
	~CIma();
	//**************
	byte clip(int a);

	void ConvertRGBYUY2(BYTE *ptrIn, BYTE *pyuv, int Larg, int Haut);
	void ConvertYUY2RGB(BYTE *PtrIn, BYTE *ptrOut, int Larg, int Haut);
	void Contour(unsigned char * ImrgbPtr, int Larg, int Haut);
	void inversion(unsigned char *ImrgbPtr, int Larg, int Haut);
	void seuillage(unsigned char *ImrgbPtr, int Larg, int Haut);
	void blur(unsigned char *ImrgbPtr, int Larg, int Haut);
	void rotation(unsigned char *ImrgbPtr, unsigned char *imInterPtr,  int Larg, int Haut, double angle);
///////////// multi thread:
		/*void PasseBasMultiThread(BYTE *pImage, int Larg, int Haut);
		DWORD WINAPI Filtre1(void * parametre);
		DWORD WINAPI Filtre2(void * parametre);
		*/

};


