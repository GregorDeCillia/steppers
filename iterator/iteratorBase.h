#pragma once

#include "../include/typedefs.h"

class iterator
{
 protected:
	rhs_type f_;
	string name_;
	int ord_;

 public:

 iterator( rhs_type f, string name, int ord ) :
	ord_( ord ),
		name_( name ),
		f_( f ){}

	string getName(){
		return name_;
	}

	int getOrder(){
		return ord_;
	}

	virtual void setRHS( rhs_type f ){
		f_ = f;
	}

};
