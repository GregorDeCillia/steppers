#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

class fehlbergStepper: public rkStepper
{

public:
	fehlbergStepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "fe", 5 ,
		           {16.0/135.0, 0.0, 6656.1/12825.0, 28561.0/56430.0,
				           -9.0/50.0, 2.0/55.0},
		           { { 0.25        , 0.0           , 0.0           , 0.0          , 0.0       },
		             {3.0/32.0     , 9.0/32.0      , 0.0           , 0.0          , 0.0       },
		             {1932.0/2197.0, -7200.0/2197.0, 7296.0/2197.0 , 0.0          , 0.0       },
		             { 439.0/216.0  , -8.0         , 3680.0/513.0  , -845.0/4104.0, 0.0       },
		             {-8.0/27.0    , 2.0           , -3544.0/2565.0, 1859.0/4104.0, -11.0/40.0}  } 
		           )
	{};
};
