#pragma once

#include "../iteratorBase.h"

class predictor : public iterator
{
 protected:
	/// how much steps do have to be stored before predict can be called
	int buffer_size;

 public:

 predictor( rhs_type f, string name, int ord , int buffer_size ) :
	iterator( f, name, ord ),
		buffer_size( buffer_size ){};

 int getBufferSize(){	 
	 return buffer_size;
 }

	virtual void predict( time_type &t, state_type &x, time_type h,
	                      buffer_type buffer_x, buffer_type buffer_dx ) = 0;

};
