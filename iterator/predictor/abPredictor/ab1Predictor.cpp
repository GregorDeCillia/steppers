#pragma once

#include "abPredictorBase.h"

// Euler step implemented as abPredictor
class ab1Predictor : public abPredictor
{
public:
ab1Predictor( rhs_type f ) :
	abPredictor( f, "ab1Pred", 1 , 
	             { 1.0 } 
	             ){};
};
