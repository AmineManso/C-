// CSlice.h

#pragma once
class CSlice
{
private:
	int Lut[16];

public:
	CSlice();
	CSlice(bool e0, bool e1, bool e2, bool e3, bool e4, bool e5, bool e6, bool e7, bool e8, 
		   bool e9, bool e10, bool e11, bool e12, bool e13, bool e14, bool e15);
	~CSlice();
public:	
	bool Out(bool s3, bool s2, bool s1, bool s0);// s3 : MSB.
												 // s0 : LSB.

};

