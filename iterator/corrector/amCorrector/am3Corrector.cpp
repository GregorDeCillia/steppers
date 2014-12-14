#pragma once

#include "amCorrector.cpp"

class am3Corrector : public amCorrector
{
public:
	am3Corrector( rhs_type f ) :
		amCorrector( f, "am3Cor", 3, 
		             {5.0/12.0, 2.0/3.0, -1.0/12.0} ){};
};
