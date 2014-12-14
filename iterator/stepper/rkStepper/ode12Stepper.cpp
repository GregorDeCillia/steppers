#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

/// Euler method imlemented as member of rkStepper
class ode12Stepper: public rkStepper
{

public:
	/**
	   \f[
	      \begin{array}{r|ll}
	         0 &  \\
	         \hline
	           & 1 

	      \end{array}
	   
	   \f]
	 **/


	ode12Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode12",  1 , 
		           {1.0},{{}}
		           )
	{
	};
};
