#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

/// classical runge kutta method
class ode45Stepper: public rkStepper
{

	/**
       Creates the classical runge kuta scheme. The tableau is
       \f[
	      \begin{array}{r|rrrr}
             0                           \\
             1/2 & 1/2                   \\
             1/2 &   0 & 1/2             \\
               1 &   0 &   0 &   1       \\
             \hline
                 & 1/6 & 1/3 & 1/3 & 1/6 
          \end{array}	   
       \f]
	 **/

public:
	ode45Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode45", 4 ,
		             {1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0}, 
		           { {    0.5,     0.0,     0.0 },
				     {    0.0,     0.5,     0.0 },
					 {    0.0,     0.0,     1.0 } }

		           )
	{};
};

