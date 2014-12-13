#pragma once

#include "predictorBase.h"

class bdfPredictor : public predictor
{
public:
	bdfPredictor( rhs_type f ) :
		predictor( f, "bdfPred", 3 , 4 ){};

	void predict( time_type &t_, state_type &x_, time_type h_, 
	              buffer_type buffer_x_, buffer_type buffer_dx_ )
	{
		
		x_  = - 1.0*buffer_x_[3] + 4.0*buffer_x_[2]
			- 6.0*buffer_x_[1] + 4.0*buffer_x_[0] ;
		t_ += h_;
	}
};
