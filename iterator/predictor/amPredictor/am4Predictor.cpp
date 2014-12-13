#pragma once

#include "amPredictorBase.h"
#include "../../../include/assigner.hpp"

vector<value_type> getVector4(){
	vector<value_type> a(4);

	a[3] = 55.0/24.0;
	a[2] =-59.0/24.0;
	a[1] = 37.0/24.0;
    a[0] = -3.0/08.0;

    return a;       
}

class am4Predictor : public amPredictor
{
public:
	am4Predictor( rhs_type f ) :
	amPredictor( f, "am4Pred", 4 , getVector4()){};
};

