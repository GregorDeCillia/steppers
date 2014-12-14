#pragma once

#include "abPredictorBase.h"

class ab5Predictor : public abPredictor
{
public:
	ab5Predictor( rhs_type f ):
		abPredictor( f, "am5Pred", 5, 
		             {1901.0/720.0, -1387.0/360.0,
				             +109.0/30.0, -637/360.0,
				             +251/720.0} 
		             ){}
};
