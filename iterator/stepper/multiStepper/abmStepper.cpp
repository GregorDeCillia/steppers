#pragma once

#include "multiStepperBase.h"

#include "../../predictor/abPredictor/newAbPredictor.cpp"
#include "../../corrector/amCorrector/newAmCorrector.cpp"
#include "../rkStepper/newRkStepper.cpp"


/// adams bashforth moulton method
class abmStepper: public multiStepper
{

public:

	abmStepper( unsigned int nStates , rhs_type f ) :
		multiStepper( nStates, 5, 4, f , 1, "abm",
		              newAbPredictor(          f, 4 ),
		              newAmCorrector(          f, 5 ),
		              newRkStepper  ( nStates, f, 5 )
		              ){};

};
