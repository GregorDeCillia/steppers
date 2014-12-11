#pragma once

#include "../typedefs.h"
#include "stepperBase.h"
#include "../rk4Stepper.cpp"

#include <boost/format.hpp>

class multiStepper : public stepper
{
protected:
  buffer_type buffer_x_;
  buffer_type buffer_dx_;
  int buffer_index_;

	rk4Stepper singleStepper_;

virtual void predictor() = 0;
virtual void corrector() = 0;

 public:

 multiStepper( unsigned int nStates, int ord, rhs_type f ) :
	stepper( nStates, f ),
		buffer_x_( ord ),
		buffer_dx_( ord ),
		buffer_index_( 0 ),
		singleStepper_( nStates, f )
			{
				ord_ = ord;
			};

	void printBuffer(){
		std::cout << boost::format( "%-15E" ) % t_;
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-15E%-15E" ) % buffer_x_[i][1] % buffer_dx_[i][1];
		}
			std::cout << std::endl;		
		}

	void clearBuffers(){
		buffer_index_ = 0;
	}


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
				buffer_x_.insert_element( buffer_index_,  x_ );
				buffer_dx_.insert_element( buffer_index_,  f( t_, x_ ) );
				buffer_index_++;
			}
		else{
			// calculate the predictor
			predictor();
			// make corrector step
			for( int i = 0; i < ord_; i++ ){
				corrector();
			}

			buffer_x_[0] = buffer_x_[1];
			buffer_x_[1] = buffer_x_[2];
			buffer_x_[2] = buffer_x_[3];
			buffer_x_[3] = x_;

			// cycle the buffer and fill in the new value
			buffer_dx_[0] = buffer_dx_[1];
			buffer_dx_[1] = buffer_dx_[2];
			buffer_dx_[2] = buffer_dx_[3];
			buffer_dx_[3] = f( t_, x_ );
			dx_           = buffer_dx_[3];

		}
	}

	
};
