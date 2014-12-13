#pragma once

#include "amPredictorBase.h"
#include "../../../include/assigner.hpp"

vector<value_type> getVector(){
	vector<value_type> a(5);

	a[4] = 1901.0/720.0;
	a[3] =  -1387.0/360.0;
	a[2] =  +109.0/30.0;
	a[1] =  -637/360.0;
	a[0] =  +251/720.0;

	return a;       
}

class am5Predictor : public amPredictor
{
public:
	am5Predictor( rhs_type f ):
		amPredictor( f, "am5Pred", 5, getVector() ){}
};
