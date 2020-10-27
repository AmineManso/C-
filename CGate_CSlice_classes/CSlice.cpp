// CSlice.cpp

#include "stdafx.h"
#include "Slice.h"

CSlice::CSlice()
{
}

CSlice::~CSlice()
{
}

CSlice::CSlice(bool e0, bool e1, bool e2, bool e3, bool e4, bool e5, bool e6, bool e7,bool e8,
			   bool e9, bool e10, bool e11, bool e12, bool e13, bool e14, bool e15)
{
	Lut[0] = e0;
	Lut[1] = e1;
	Lut[2] = e2;
	Lut[3] = e3;
	Lut[4] = e4;
	Lut[5] = e5;
	Lut[6] = e6;
	Lut[7] = e7;
	Lut[8] = e8;
	Lut[9] = e9;
	Lut[10] = e10;
	Lut[11] = e11;
	Lut[12] = e12;
	Lut[13] = e13;
	Lut[14] = e14;
	Lut[15] = e15;
}

bool CSlice::Out(bool s3, bool s2, bool s1, bool s0)
{
	//int n = s0 * 1 + s1 * 2 + s2 * 4 + s3 * 8;
	int n = s0 << 0 | s1 << 1 | s2 << 2 | s3 << 3;
	return  Lut[n];
}
// Ou on peur utiliser l'operateur de decalage <<


