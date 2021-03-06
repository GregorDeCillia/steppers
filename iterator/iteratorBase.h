#pragma once

#include "../include/typedefs.h"

class iterator
{
 protected:
	/// right hand size of the ode
	rhs_type f_;
	/// name of the iterator
	string name_;
	/// order of convergence or [global trunounciation error](https://en.wikipedia.org/wiki/Truncation_error_%28numerical_integration%29#Global_truncation_error)
	int ord_;

 public:
	/**
	   \param[in]    f      the righthandside of the ODE 
	   \param[in]    name   the name of the method
	   \param[in]    ord    the global trunounciation error

	 **/
	/// constructor
 iterator( rhs_type f, string name, int ord ) :
	ord_( ord ),
		name_( name ),
		f_( f ){}
	/// return the name of the siterator
	string getName(){
		return name_;
	}
	/// get the [global trunounciation error](https://en.wikipedia.org/wiki/Truncation_error_%28numerical_integration%29#Global_truncation_error) of the method
	int getOrder(){
		return ord_;
	}
	/// change the rhs of the ode. note that this will call clearBuffers() for LMMs
	virtual void setRHS( rhs_type f ){
		f_ = f;
	}

};
