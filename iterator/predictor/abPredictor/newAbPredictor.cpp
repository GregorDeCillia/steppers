#pragma once

#include "abPredictorBase.h"

#include "ab1Predictor.cpp"
#include "ab2Predictor.cpp"
#include "ab3Predictor.cpp"
#include "ab4Predictor.cpp"
#include "ab5Predictor.cpp"

abPredictor* newAbPredictor( rhs_type f, int i  )
{
	switch ( i ){
	case 1: return new ab1Predictor( f );
	case 2: return new ab2Predictor( f );
	case 3: return new ab3Predictor( f );
	case 4: return new ab4Predictor( f );
	case 5: return new ab5Predictor( f );
    default:
         std::cout << "ab predictor of order " << i
                   << " does not exist" << std::endl;

	}
}
