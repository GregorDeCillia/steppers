#pragma once

#include "amCorrector.cpp"

class am2Corrector : public amCorrector
{
public:
	am2Corrector( rhs_type f ) :
		amCorrector( f, "am2Cor", 2, {0.5, 0.5} ){};
};
