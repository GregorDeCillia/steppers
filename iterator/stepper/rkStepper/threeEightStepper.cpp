#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

class threeEightStepper: public rkStepper
{

public:
	threeEightStepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "3/8rule", 4,
		           { 1.0/8.0, 3.0/8.0, 3.0/8.0, 1.0/8.0 },
		           {  {  1.0/3.0,  0.0, 0.0 },
				      { -1.0/3.0,  1.0, 0.0 },
					  { 1.0     , -1.0, 1.0 }  }
		           )
	{};
};
