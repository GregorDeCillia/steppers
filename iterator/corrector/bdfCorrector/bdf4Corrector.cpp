#pragma once

#include "bdfCorrectorBase.h"

class bdf4Corrector : public bdfCorrector
{
public:
	bdf4Corrector( rhs_type f ):
		bdfCorrector( f , "bdf4Cor", 4,
		              { -48.0/25.0, +36.0/25.0, -16.0/25.0, 3.0/25.0 }, 12.0/25.0 ){};
};
