#pragma once

#include "bdfCorrectorBase.h"

class bdf1Corrector : public bdfCorrector
{
public:
	bdf1Corrector( rhs_type f ):
		bdfCorrector( f , "bdf1Cor", 1,
		              {-1}, 1 ){};
};
