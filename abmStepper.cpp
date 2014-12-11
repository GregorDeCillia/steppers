#pragma once

#include "typedefs.h"
#include "stepperBase/multiStepperBase.h"

class abmStepper: public multiStepper
{
protected:
	void predictor(){
		x_ = buffer_x_[3] + h_*( 55.0/24.0*buffer_dx_[3]
		                         - 59.0/24.0*buffer_dx_[2]
		                         + 37.0/24.0*buffer_dx_[1]
		                         - 03.0/08.0*buffer_dx_[0] );
		t_ += h_;
	}
	void corrector(){
		x_ = buffer_x_[3] + h_*( 251.0/720.0*f( t_, x_ )
		                         + 646.0/720.0*buffer_dx_[3]
		                         - 264.0/720.0*buffer_dx_[2]
		                         + 106.0/720.0*buffer_dx_[1]
		                         - 019.0/720.0*buffer_dx_[0]
		                         );
	}

public:

	abmStepper( unsigned int nStates , rhs_type f ) :
		multiStepper( nStates, 4, f ){};

};
