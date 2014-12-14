#pragma once

#include "bdfCorrectorBase.h"

class bdf3Corrector : public bdfCorrector
{
public:
	bdf3Corrector( rhs_type f ):
		bdfCorrector( f , "bdf3Cor", 3,
		              {-18.0/11.0, 9.0/11.0, -2.0/11.0}, 6.0/11.0 ){};
};
