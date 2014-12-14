#pragma once

#include "amCorrector.cpp"

class am4Corrector : public amCorrector
{
public:
	am4Corrector( rhs_type f ) :
		amCorrector( f, "am4Cor", 4, 
		             { 3.0/8.0, 19.0/24.0, -5.0/24.0, 1.0/24.0 } 
		             ){} 
};
