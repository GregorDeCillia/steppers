#pragma once

#include "stepperBase/multiStepperBase.h"

class bdfStepper: public multiStepper
{
protected:
	void predictor(){
			x_  = - 1.0*buffer_x_[0] + 4.0*buffer_x_[1]
				  - 6.0*buffer_x_[2] + 4.0*buffer_x_[3] ;
			t_ += h_;
	}

	void corrector(){
		x_ = +01.0/25.0*( 48.0*buffer_x_[3]-36.0*buffer_x_[2]
		                 +16.0*buffer_x_[1]-03.0*buffer_x_[0] )
			+12.0/25.0*h_*f( t_, x_ );
	}

public:

	bdfStepper( unsigned int nStates, rhs_type f ) : 
		multiStepper( nStates, 4, f , 2 , "bdf" ){};

};
