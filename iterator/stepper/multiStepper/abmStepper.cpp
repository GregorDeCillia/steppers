#pragma once

#include "multiStepperBase.h"

#include "../../predictor/abPredictor/ab4Predictor.cpp"
#include "../../corrector/abmCorrector.cpp"
#include "../rkStepper/fehlbergStepper.cpp"
//#include "../rkStepper/ode45Stepper.cpp"

/// adams bashforth moulton method
class abmStepper: public multiStepper
{

public:

	abmStepper( unsigned int nStates , rhs_type f ) :
		multiStepper( nStates, 5, f , 1, "abm",
			              new ab4Predictor( f ),
			              new abmCorrector( f ),
			              new fehlbergStepper( nStates, f )
		              ){};

};
