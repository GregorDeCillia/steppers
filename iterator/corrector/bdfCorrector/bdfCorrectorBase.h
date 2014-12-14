#pragma once

#include "../correctorBase.h"
#include "boost/numeric/ublas/io.hpp"

class bdfCorrector : public corrector
{
	coefficient_vector a;
	value_type beta;
public:
	bdfCorrector( rhs_type f , string name, int ord, 
	              coefficient_vector a, value_type beta ) :
	corrector( f, name, ord , a.size() ),
		a( a ),
		beta( beta )
		{}

	void correct( time_type &t_, state_type &x_, time_type h_, 
	              buffer_type buffer_x_, buffer_type buffer_dx_ )
	{
		state_type dx = beta*f_( t_, x_ );

		for ( int i = 0; i < getBufferSize(); i++ )
			{
				dx += -a[i]*buffer_x_[i]; 
			}
		x_ = buffer_x_[0] + h_*dx;
	}
};
