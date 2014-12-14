#pragma once

#include "../iteratorBase.h"

class corrector : public iterator
{
 protected:
	int buffer_size;
 public:
	
 corrector( rhs_type f, string name, int ord , int buffer_size ) :
	iterator( f, name, ord ),
		buffer_size( buffer_size ){};

	int getBufferSize(){
		return( buffer_size );
	}

	virtual void correct( time_type &t_, state_type &x_, time_type h,
	                      buffer_type buffer_x_, buffer_type buffer_dx_ ) = 0;

};
