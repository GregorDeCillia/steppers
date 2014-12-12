#pragma once

#include "../iteratorBase.h"

class corrector : public iterator
{

 public:
	
 corrector( rhs_type f, string name, int ord ) :
	iterator( f, name, ord ){};

	virtual void correct( time_type &t_, state_type &x_, time_type h,
	                      buffer_type buffer_x_, buffer_type buffer_dx_ ) = 0;

};
