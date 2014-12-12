#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

class ode23Stepper: public rkStepper
{

public:
	ode23Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode23", 1, 2 )
	{
          A << 0.5;

          b << 0.0, 1.0;

          //c << 0.5, 0.5, 1.0;
          calculateC();
	};
};
