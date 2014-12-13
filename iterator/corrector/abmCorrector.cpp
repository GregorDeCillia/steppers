#pragma once

#include "correctorBase.h"

class abmCorrector : public corrector
{
public:
	abmCorrector( rhs_type f ) :
		corrector( f, "abmCorr", 5 ){};

	void correct( time_type &t, state_type &x, time_type h,
	              buffer_type buffer_x, buffer_type buffer_dx )
	{
		x = buffer_x[0] + h*( 251.0/720.0*f_( t, x )
		                         + 646.0/720.0*buffer_dx[0]
		                         - 264.0/720.0*buffer_dx[1]
		                         + 106.0/720.0*buffer_dx[2]
		                         - 019.0/720.0*buffer_dx[3]
		                         );
			}
};
