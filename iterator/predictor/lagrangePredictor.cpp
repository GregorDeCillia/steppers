#pragma once

#include "predictorBase.h"


class lagrangePredictor : public predictor{
private:
	coefficient_vector p;
public:
	lagrangePredictor( rhs_type f, int buff_size ) :
		predictor( f, "lagPred",  buff_size-1, buff_size ),
		p( buff_size )
		
	{
		for ( int i = 0; i < buff_size; i++ ){
			p[i] = 1;
			for ( int j = 0; j < buff_size; j++ )
				if ( i != j )
					p[i] *= ( 1.0 + j )/( j - i );
		}
	}

	void predict( time_type &t_, state_type &x_, time_type h_, 
	              buffer_type buffer_x_, buffer_type buffer_dx_ )
	{
		x_ *= 0;
		for ( int i = 0; i < buffer_size; i++ ){
			x_ += p[i]*buffer_x_[i];
		}
		t_ += h_;
	}
};
