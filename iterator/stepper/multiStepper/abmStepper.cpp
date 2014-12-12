#pragma once

#include "multiStepperBase.h"

#include "../../predictor/abmPredictor.cpp"
#include "../../corrector/abmCorrector.cpp"
#include "../rkStepper/fehlbergStepper.cpp"

class abmStepper: public multiStepper
{

public:

	abmStepper( unsigned int nStates , rhs_type f ) :
		multiStepper( nStates, 5, f , 1, "abm",
			              new abmPredictor( f ),
			              new abmCorrector( f ),
			              new fehlbergStepper( nStates, f )
		              ){};

};
