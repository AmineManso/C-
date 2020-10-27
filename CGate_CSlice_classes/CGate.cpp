// CGate.cpp

#include "stdafx.h"
#include "Gate.h"
CGate::CGate()
{
	A = B = C = D = false;
}
CGate::~CGate()
{
}

CGate::CGate(bool Aint, bool Bint, bool Cint, bool Dint)
{
	A = Aint;
	B = Bint;
	C = Cint;
	D = Dint;
}

bool CGate::Et(bool Aet, bool Bet)
{
	return Aet & Bet;
}

bool CGate::Or(bool Aor, bool Bor)
{
	return Aor | Bor ;
}

bool CGate::Xor(bool Axor, bool Bxor)
{
	return (  (Axor | Bxor) &! (Axor & Bxor) );
}

bool CGate::SignalSortie()
{
	CGate Signal;

	bool SignalReturn = Signal.Xor(  Signal.Or(   Signal.Et(A, B), C  )   , D);
	return  SignalReturn;
}
