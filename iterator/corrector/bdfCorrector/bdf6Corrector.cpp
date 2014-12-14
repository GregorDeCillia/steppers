#pragma once

#include "bdfCorrectorBase.h"

class bdf6Corrector : public bdfCorrector
{
public:
	bdf6Corrector( rhs_type f ):
		bdfCorrector( f , "bdf6Cor", 6,
		              { -360.0/147.0, +450.0/147.0, -400.0/147.0, 
		                     225.0/147.0, -72.0/147.0, 10.0/147.0 }, 
		              60.0/147.0 ){};
};
