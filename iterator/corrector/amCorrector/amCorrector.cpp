#pragma once

#include "../correctorBase.h"
#include "boost/numeric/ublas/io.hpp"

class amCorrector : public corrector
{
	coefficient_vector b;
	int buffer_size;
public:
	amCorrector( rhs_type f , string name, int ord, 
	             coefficient_vector b ) :
		corrector( f, name, ord ),
		b( b ),
		buffer_size( b.size()-1 ){}

	void correct( time_type &t_, state_type &x_, time_type h_, 
	              buffer_type buffer_x_, buffer_type buffer_dx_ )
	{
		state_type dx = b[0]*f_( t_, x_ );

		for ( int i = 0; i < buffer_size; i++ )
			{
				dx += b[i+1]*buffer_dx_[i]; 
			}
		x_ = buffer_x_[0] + h_*dx;
	}
};
