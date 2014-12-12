#pragma once

#include "../../../include/typedefs.h"

class corrector
{
 protected:
	rhs_type f;
	string name_;
	int ord;

 public:

 corrector( rhs_type f, string name, int ord ) :
	ord( ord ),
		name_(name),
		f( f ){}

	virtual void correct( time_type &t_, state_type &x_, time_type h,
	                      buffer_type buffer_x_, buffer_type buffer_dx_ ) = 0;

};
