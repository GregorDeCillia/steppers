#pragma once

#include "../iteratorBase.h"

class corrector : public iterator
{
 private:
	int buffer_size;
 public:
	/// constructor of the base class. passes order to rhs
 corrector( rhs_type f, string name, int ord , int buffer_size ) :
	iterator( f, name, ord ),
		buffer_size( buffer_size ){};

	/// How much buffer as to be generated to use this formula
	int getBufferSize(){
		return( buffer_size );
	}
	/// performs a corrector step
	virtual void correct( time_type &t_, state_type &x_, time_type h,
	                      buffer_type buffer_x_, buffer_type buffer_dx_ ) = 0;

};
