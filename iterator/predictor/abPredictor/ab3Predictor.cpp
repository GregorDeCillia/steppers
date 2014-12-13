#pragma once

#include "abPredictorBase.h"
#include "../../../include/assigner.hpp"

vector<value_type> getVector3(){
	vector<value_type> a(3);

	a[0] = 23.0/12.0;
	a[1] =  -4.0/3.0;
    a[2] = 5.0/12.0;

	return a;       
}

class ab3Predictor : public abPredictor
{
public:
ab3Predictor( rhs_type f ) :
	abPredictor( f, "am3Pred", 3 , getVector3() ){};
};
