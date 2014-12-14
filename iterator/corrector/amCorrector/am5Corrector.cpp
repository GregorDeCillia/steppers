#pragma once

#include "amCorrector.cpp"

class am5Corrector : public amCorrector
{
public:
	am5Corrector( rhs_type f ) :
		amCorrector( f, "am5Cor", 5, 
		             { 251.0/720.0, 646.0/720.0,-264.0/720.0, 
				             106.0/720.0, -19.0/720.0 } 
		             ){}
};
