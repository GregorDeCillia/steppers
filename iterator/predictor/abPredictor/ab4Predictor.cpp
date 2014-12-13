#pragma once

#include "abPredictorBase.h"

class ab4Predictor : public abPredictor
{
public:
	ab4Predictor( rhs_type f ) :
	abPredictor( f, "am4Pred", 4 , 
	             {55.0/24.0, -59.0/24.0, 
			             37.0/24.0, -3.0/08.0} 
	             ){};
};

