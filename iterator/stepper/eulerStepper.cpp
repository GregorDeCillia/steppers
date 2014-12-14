#pragma once

#include <boost/numeric/ublas/vector.hpp>

#include "stepperBase.h"

/// Good old [Eulerstepper](https://en.wikipedia.org/wiki/Euler_method)
class eulerStepper: public stepper
{
public:

	eulerStepper( unsigned int nStates , rhs_type f ) :
		stepper( nStates, f , 1, "euler" ){};

	void doStep( time_type h ){
		x_ += h*dx_;
		t_ += h;
		dx_ = f_( t_, x_ );
	}

};
