#pragma once

#include <boost/numeric/ublas/vector.hpp>

#include "typedefs.h"
#include "stepperBase/stepperBase.h"

using namespace std;

class eulerStepper: public stepper
{
public:

	eulerStepper( unsigned int nStates , rhs_type f ) :
		stepper( nStates, f , 1, "euler" ){};

	void doStep( time_type h ){
		x_ += h*dx_;
		t_ += h;
		dx_ = f( t_, x_ );
	}

};
