#pragma once

#include "amPredictorBase.h"
#include "../../../include/assigner.hpp"

vector<value_type> getVector3(){
	vector<value_type> a(3);

	a[2] = 23.0/12.0;
	a[1] =  -4.0/3.0;
    a[0] = 5.0/12.0;

	return a;       
}

class am3Predictor : public amPredictor
{
public:
am3Predictor( rhs_type f ) :
	amPredictor( f, "am3Pred", 3 , getVector3() ){};
};
