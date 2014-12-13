#pragma once

#include "abPredictorBase.h"
#include "../../../include/assigner.hpp"

vector<value_type> getVector2(){
	vector<value_type> a(2);

	a[0] = 3.0/2.0;
	a[1] =  -1.0/2.0;

	return a;       
}


class ab2Predictor : public abPredictor
{
public:
ab2Predictor( rhs_type f ) :
	abPredictor( f, "ab2Pred", 2 , getVector2() ){};
};

