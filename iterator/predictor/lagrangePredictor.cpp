#pragma once

#include "predictorBase.h"

/**
   implements the lagrange formula to get predictors out of
   buffers created by equidistant points i.e.
   \f[
        x_{n+1} \approx \sum_{j=0}^{ \texttt{buff\_size} } b_j x_{n-j}
   \f]
 **/
/// predictor based on the lagrange formula
class lagrangePredictor : public predictor{
private:
	coefficient_vector p;
public:
	/**
	   \param[in] f            the righthandside of the ode
	   \param[in] buff_size    how much buffer should be used for the extrapolation.
	                           The higher the order is picked, the better the
	                           extrapolation is
	   
	 **/
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
