#pragma once

#include "multiStepperBase.h"

#include "../../predictor/lagrangePredictor.cpp"
#include "../../corrector/bdfCorrector.cpp"
#include "../rkStepper/ode45Stepper.cpp"

/// backward differentiation formula
class bdfStepper: public multiStepper
{

public:

	bdfStepper( unsigned int nStates, rhs_type f ) : 
		multiStepper( nStates, 4, f , 1 , "bdf" , 
		              new lagrangePredictor( f, 4 ),
		              new bdfCorrector( f ),
		              new ode45Stepper( nStates, f )
		              ){};

};
