#pragma once

#include "../../include/assigner.hpp"
#include "rkStepperBase.h"

class ode34Stepper: public rkStepper
{

public:
	ode34Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode34", 2, 3 )
	{
		A << 0.50, 0.00, 
			-1.00, 2.00;

		b << 1.0/6.0, 4.0/6.0, 1.0/6.0;

		//c << 0.5, 1.0;
		calculateC();
	};
};
