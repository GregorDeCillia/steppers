#pragma once

#include "amPredictorBase.h"
#include "../../../include/assigner.hpp"

vector<value_type> getVector2(){
	vector<value_type> a(2);

	a[1] = 3.0/2.0;
	a[0] =  -1.0/2.0;

	return a;       
}


class am2Predictor : public amPredictor
{
public:
am2Predictor( rhs_type f ) :
	amPredictor( f, "am2Pred", 2 , getVector2() ){};
};

