#pragma once

#include "typedefs.h"
#include "stepperBase/stepperBase.h"
#include "stepperBase/multiStepperBase.h"
#include "rk4Stepper.cpp"

class bdfStepper: public multiStepper
{
private:
	
	void predictor(){
			x_  = - 1.0*buffer_[0] + 4.0*buffer_[1]
				  - 6.0*buffer_[2] + 4.0*buffer_[3] ;
			t_ += h_;
	}

	void corrector(){
		x_= +01.0/25.0*( 48.0*buffer_[3]-36.0*buffer_[2]
		                +16.0*buffer_[1]-03.0*buffer_[0] )
			+12.0/25.0*h_*f(t_,x_);		
	}

public:

	bdfStepper( unsigned int nStates, rhs_type f ) : 
		multiStepper( nStates, 4, f ){};

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
				buffer_.insert_element( buffer_index_,  x_ );
				buffer_index_++;
			}
		else{
			// calculate the predictor
			predictor();
			// make corrector step
			for( int i = 0; i < ord_; i++ ){
				corrector();
			}
			// cycle the buffer and fill in the new value
			buffer_[0] = buffer_[1]; 
			buffer_[1] = buffer_[2]; 
			buffer_[2] = buffer_[3];
			buffer_[3] = x_;
			dx_ = f( t_, x_ );
		}
	}
};
