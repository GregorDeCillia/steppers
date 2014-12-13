#pragma once

#include "abPredictorBase.h"
#include "../../../include/assigner.hpp"

vector<value_type> getVector4(){
	vector<value_type> a(4);

	a[0] = 55.0/24.0;
	a[1] =-59.0/24.0;
	a[2] = 37.0/24.0;
    a[3] = -3.0/08.0;

    return a;       
}

class ab4Predictor : public abPredictor
{
public:
	ab4Predictor( rhs_type f ) :
	abPredictor( f, "am4Pred", 4 , getVector4()){};
};

