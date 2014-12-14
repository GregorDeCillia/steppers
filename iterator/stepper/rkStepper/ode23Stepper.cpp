#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"
/// midpoint rule
class ode23Stepper: public rkStepper
{

	/**
       Creates the classical runge kuta scheme. The tableau is
       \f[
	      \begin{array}{r|rr}
             0                \\
             1/2 & 1/2        \\
             \hline
                 &   0 &  1   \\
          \end{array}	   
       \f]
	 **/

public:
	ode23Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode23", 2 , {0.0, 1.0},
		           {{0.5}})
	{};
};
