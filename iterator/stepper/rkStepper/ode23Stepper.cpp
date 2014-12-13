#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

class ode23Stepper: public rkStepper
{

public:
	ode23Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode23", 2 , {0.0, 1.0},
		           {{0.5}})
	{};
};
