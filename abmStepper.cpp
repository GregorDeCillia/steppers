#pragma once

#include "typedefs.h"
#include "stepperBase/stepperBase.h"
#include "stepperBase/multiStepperBase.h"
#include "rk4Stepper.cpp"

class abmStepper: public multiStepper
{
private:
	state_type xAB_;
	void predictor(){
		xAB_ = x_ + h_*(  55.0/24.0*buffer_[3] 
		                 - 59.0/24.0*buffer_[2] 
		                 + 37.0/24.0*buffer_[1] 
		                 - 03.0/08.0*buffer_[0] );
		t_+=h_;
	}
	void corrector(){
		xAB_ = x_ + h_*(  251.0/720.0*f(t_,xAB_)  + 646.0/720.0*buffer_[3]
		                 -264.0/720.0*buffer_[2] + 106.0/720.0*buffer_[1]
		                 -019.0/720.0*buffer_[0] );
	}

public:

	abmStepper( unsigned int nStates , rhs_type f) :
		multiStepper( nStates, 4, f ),
		xAB_( nStates ){};

	void doStep( time_type h ){
		if ( h != h_ ){
			buffer_index_ = 0;
			h_ = h;
		}
		if ( buffer_index_ < 4 )
			{
				singleStepper_.setStates( t_, x_ );
				singleStepper_.doStep( h );
				singleStepper_.getStates( t_, x_ );
				buffer_.insert_element( buffer_index_,  f( t_, x_ ) );
				buffer_index_++;
			}
		else{
			// calculate the predictor
			predictor();
			// make corrector step
			for( int i = 0; i < ord_; i++ ){
				corrector();
			}
			x_ = xAB_;
			// cycle the buffer and fill in the new value
			buffer_[0] = buffer_[1]; 
			buffer_[1] = buffer_[2]; 
			buffer_[2] = buffer_[3];
			buffer_[3] = f( t_, x_ );
			dx_ = buffer_[3];

		}
	}
};
