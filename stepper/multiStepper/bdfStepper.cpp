#pragma once

#include "multiStepperBase.h"
#include "predictor/bdfPredictor.cpp"
#include "corrector/bdfCorrector.cpp"

class bdfStepper: public multiStepper
{

public:

	bdfStepper( unsigned int nStates, rhs_type f ) : 
		multiStepper( nStates, 4, f , 2 , "bdf" , 
			              new bdfPredictor( f ),
			              new bdfCorrector( f ),
			              new ode45Stepper( nStates, f )
			              ){};

};
