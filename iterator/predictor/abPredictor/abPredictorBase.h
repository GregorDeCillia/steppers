#pragma once

#include "../predictorBase.h"

class abPredictor : public predictor
{

 private:	
	coefficient_vector a_;
 public:
	/// the only real characteristic of the childs is the `coefficient_vector` a
 abPredictor( rhs_type f , string name, int ord, 
              coefficient_vector a ) :
	predictor( f, name, ord, a.size() ),
		a_( a ){};
	/// make a predictor step. t and x get updated. The buffer remains unchanged by the call
	void predict( time_type &t_, state_type &x_, time_type h_, 
	              buffer_type buffer_x_, buffer_type buffer_dx_ )
	{

		state_type dx = 0*x_;
		for ( int i = 0; i < buffer_size; i++ ){
			dx += a_[i]*buffer_dx_[i];
		}
		x_ = buffer_x_[0] + h_*dx;
		t_+=h_;
	}

};
