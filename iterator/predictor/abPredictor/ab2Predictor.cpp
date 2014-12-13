#pragma once

#include "abPredictorBase.h"

class ab2Predictor : public abPredictor
{
public:
ab2Predictor( rhs_type f ) :
	abPredictor( f, "ab2Pred", 2 , 
	             makeVector({ 3.0/2.0, -1.0/2.0 }) 
	             ){};
};

