// CGate.h 

#pragma once
class CGate
{
public:
	// Fonctions membres:
	bool Et(bool Aet, bool Bet);
	bool Or(bool Aor, bool Bor);
	bool Xor(bool Axor, bool Bxor);

	CGate();
	~CGate();
	CGate(bool Aint, bool Bint, bool Cint, bool Dint);
	
	// Variables membres:
	bool A, B, C, D;

	bool SignalSortie();
	
};

