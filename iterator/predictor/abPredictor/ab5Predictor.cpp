#pragma once

#include "abPredictorBase.h"
#include "../../../include/assigner.hpp"

vector<value_type> getVector(){
	vector<value_type> a(5);

	a[0] = 1901.0/720.0;
	a[1] =  -1387.0/360.0;
	a[2] =  +109.0/30.0;
	a[3] =  -637/360.0;
	a[4] =  +251/720.0;

	return a;       
}

class ab5Predictor : public abPredictor
{
public:
	ab5Predictor( rhs_type f ):
		abPredictor( f, "ab5Pred", 5, getVector() ){}
};
