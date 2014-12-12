#pragma once

#include "../../include/typedefs.h"

class corrector
{
 protected:
	rhs_type f_;
	string name_;
	int ord;

 public:

 corrector( rhs_type f, string name, int ord ) :
	ord( ord ),
		name_(name),
		f_( f ){}

	void setRHS( rhs_type f ){
		f_ = f;
	}

	string getName(){
	               return name_;
	}

	virtual void correct( time_type &t_, state_type &x_, time_type h,
	                      buffer_type buffer_x_, buffer_type buffer_dx_ ) = 0;

};
