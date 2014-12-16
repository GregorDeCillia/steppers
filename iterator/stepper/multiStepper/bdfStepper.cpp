#pragma once

#include "multiStepperBase.h"

#include "../../predictor/lagrangePredictor.cpp"
#include "../../corrector/bdfCorrector/newBdfCorrector.cpp"
#include "../rkStepper/newRkStepper.cpp"

/// backward differentiation formula
class bdfStepper: public multiStepper
{
public:
	bdfStepper( unsigned int nStates, rhs_type f ) : 
		multiStepper( nStates, 5, 5, f , 1 , "bdf" ,
		              new lagrangePredictor( f, 4 ),
		              newBdfCorrector      ( f, 5 ),
		              newRkStepper( nStates, f, 5 )
		              ){};
};
