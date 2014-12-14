#pragma once

#include "bdfCorrectorBase.h"

class bdf5Corrector : public bdfCorrector
{
public:
	bdf5Corrector( rhs_type f ):
		bdfCorrector( f , "bdf5Cor", 5,
		              { -300.0/137.0, +300.0/137.0, -200.0/137.0, 
				              75.0/137.0, -12.0/137.0 }, 
		              60.0/137.0 ){};
};
