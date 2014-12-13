#pragma once

#include "../predictorBase.h"

class abPredictor : public predictor
{
 private:
	vector<value_type> a_;
 public:

 abPredictor( rhs_type f , string name, int ord, vector<value_type> a ) :
	predictor( f, name, ord, a.size() ),
		a_(a){};

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
