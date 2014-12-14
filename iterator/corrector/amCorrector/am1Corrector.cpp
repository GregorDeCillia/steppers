#pragma once

#include "amCorrector.cpp"

class am1Corrector : public amCorrector
{
public:
	am1Corrector( rhs_type f ) :
		amCorrector( f, "am1Cor", 1, {1} ){};
};
