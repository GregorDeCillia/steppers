#pragma once

#include "bdfCorrectorBase.h"

class bdf2Corrector : public bdfCorrector
{
public:
	bdf2Corrector( rhs_type f ):
		bdfCorrector( f , "bdf2Cor", 2,
		              {-4.0/3.0, 1.0/3.0}, 2.0/3.0 ){};
};
