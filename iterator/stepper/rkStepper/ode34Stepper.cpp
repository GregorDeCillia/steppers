#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

/// 3th order runge kutta method
class ode34Stepper: public rkStepper
{

public:

	/**
	   \f[
	      \begin{array}{r|lll}
	         0 \\
	         1/2 & 1/2 \\
	         1/2 & -1  &   2\\
	         \hline
	             & 1/6 & 2/3 & 1/6

	      \end{array}
	   
	   \f]
	 **/


	ode34Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode34", 3 , 
		           {1.0/6.0, 4.0/6.0,1.0/6.0},
		           { {  0.5, 0.0 }, 
				     { -1.0, 2.0 } }
		           )
	{};
};
