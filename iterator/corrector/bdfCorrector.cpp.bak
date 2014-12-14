#pragma once

#include "correctorBase.h"

class bdfCorrector : public corrector
{
public:
	bdfCorrector( rhs_type f ) :
		corrector( f, "bdfCorr", 4 ){};

	void correct( time_type &t_, state_type &x_, time_type h_, 
	              buffer_type buffer_x_, buffer_type buffer_dx_ ){
		
		x_ = +01.0/25.0*(  48.0*buffer_x_[0]-36.0*buffer_x_[1]
		                  +16.0*buffer_x_[2]-03.0*buffer_x_[3] )
			+12.0/25.0*h_*f_( t_, x_ );
	}

};
