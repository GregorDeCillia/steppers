#pragma once

#include "../../../../include/typedefs.h"

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

	void setRHS( rhs_type f ){
		f = f;
	}

	virtual void predict( time_type &t, state_type &x, time_type h,
	                      buffer_type buffer_x, buffer_type buffer_dx ) = 0;

	string getName(){
	               return name_;
	}
};

