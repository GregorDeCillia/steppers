#pragma once

#include "correctorBase.h"

class abmCorrector : public corrector
{
public:
	abmCorrector( rhs_type f ) :
		corrector( f, "abmCorr", 4 ){};

	void correct( time_type &t_, state_type &x_, time_type h_, 
	              buffer_type buffer_x_, buffer_type buffer_dx_ )
	{
		
		x_ = buffer_x_[3] + h_*( 251.0/720.0*f( t_, x_ )
		                         + 646.0/720.0*buffer_dx_[3]
		                         - 264.0/720.0*buffer_dx_[2]
		                         + 106.0/720.0*buffer_dx_[1]
		                         - 019.0/720.0*buffer_dx_[0]
		                         );
			}

};
