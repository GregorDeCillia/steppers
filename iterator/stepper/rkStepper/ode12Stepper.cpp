#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

class ode12Stepper: public rkStepper
{

public:
	ode12Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode12",  1 , 
		           {1.0},{{}}
		           )
	{
	};
};
