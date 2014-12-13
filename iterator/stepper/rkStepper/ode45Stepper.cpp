#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

class ode45Stepper: public rkStepper
{

public:
	ode45Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode45", 4 ,
		           {1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0}, 
		           { { 0.5, 0.0, 0.0 },
				     { 0.0, 0.5, 0.0 },
					 { 0.0, 0.0, 1.0 } }

		           )
	{};
};

