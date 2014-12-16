#pragma once

#include "bdfCorrectorBase.h"

#include "bdf1Corrector.cpp"
#include "bdf2Corrector.cpp"
#include "bdf3Corrector.cpp"
#include "bdf4Corrector.cpp"
#include "bdf5Corrector.cpp"
#include "bdf6Corrector.cpp"

/**
 * creates a pointer to a new instance of a bdfCorrector. This instance has
 * order i. The maximal value for i is 6 since bdf methods with a bigger
 * order are not zero stable
 **/
bdfCorrector* newBdfCorrector( rhs_type f, int i  )
{
	switch ( i ){
	case 1: return new bdf1Corrector( f );
	case 2: return new bdf2Corrector( f );
	case 3: return new bdf3Corrector( f );
	case 4: return new bdf4Corrector( f );
	case 5: return new bdf5Corrector( f );
	case 6: return new bdf6Corrector( f );
    default:
         std::cout << "bdf corrector of order " << i
                   << " does not exist" << std::endl;
	}
}
