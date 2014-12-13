#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

class ode34Stepper: public rkStepper
{

public:
	ode34Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode34", 3 , 
		           {1.0/6.0, 4.0/6.0,1.0/6.0},
		           { {  0.5, 0.0 }, 
				     { -1.0, 2.0 } }
		           )
	{};
};
