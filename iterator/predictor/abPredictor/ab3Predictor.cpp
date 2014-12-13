#pragma once

#include "abPredictorBase.h"

class ab3Predictor : public abPredictor
{
public:
ab3Predictor( rhs_type f ) :
	abPredictor( f, "am3Pred", 3 , 
	             {23.0/12.0, -4.0/3.0, 5.0/12.0} 
	             ){};
};
