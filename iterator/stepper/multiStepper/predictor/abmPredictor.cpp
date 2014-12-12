#pragma once

#include "predictorBase.h"

class abmPredictor : public predictor
{
public:
abmPredictor( rhs_type f ) :
	predictor( f, "abmPred", 4 ){};

void predict( time_type &t_, state_type &x_, time_type h_, 
	              buffer_type buffer_x_, buffer_type buffer_dx_ ){
		x_ = buffer_x_[3] + h_*( 55.0/24.0*buffer_dx_[3]
		                         - 59.0/24.0*buffer_dx_[2]
		                         + 37.0/24.0*buffer_dx_[1]
		                         - 03.0/08.0*buffer_dx_[0] );
		t_ += h_;
}
};

