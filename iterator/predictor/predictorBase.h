#pragma once

#include "../iteratorBase.h"

class predictor : public iterator
{

public:

predictor( rhs_type f, string name, int ord ) :
iterator( f, name, ord ){};

	virtual void predict( time_type &t, state_type &x, time_type h,
	                      buffer_type buffer_x, buffer_type buffer_dx ) = 0;

};
