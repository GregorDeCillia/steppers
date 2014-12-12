#pragma once

#include "../../include/assigner.hpp"
#include "rkStepperBase.h"

class threeEightStepper: public rkStepper
{

public:
	threeEightStepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "3/8rule", 3, 4 )
	{
          A <<  1.0/3.0,  0.0, 0.0,
		       -1.0/3.0,  1.0, 0.0,
			    1.0    , -1.0, 1.0;

          b << 1.0/8.0, 3.0/8.0, 3.0/8.0, 1.0/8.0;

          //c << 0.5, 0.5, 1.0;
          calculateC();
	};
};
