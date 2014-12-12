#pragma once

#include "../../../include/typedefs.h"

class predictor
{
 protected:
	rhs_type f;
	string name_;
	int ord;

public:

 predictor( rhs_type f, string name, int ord ) :
	name_(name),
		f( f ),
		ord( ord ){};

	virtual void predict( time_type &t, state_type &x, time_type h,
	                      buffer_type buffer_x, buffer_type buffer_dx ) = 0;
};

