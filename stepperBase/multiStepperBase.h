#pragma once

#include "../typedefs.h"
#include "stepperBase.h"
#include "../rk4Stepper.cpp"

#include <boost/format.hpp>

class multiStepper : public stepper
{
 protected:
	buffer_type buffer_;
	int buffer_index_;

	rk4Stepper singleStepper_;

 public:

 multiStepper( unsigned int nStates, int ord, rhs_type f ) :
	stepper( nStates, f ),
		buffer_( ord ),
		buffer_index_( 0 ),
		singleStepper_( nStates, f )
			{
				ord_ = ord;
			};

	void printBuffer(){
		std::cout << boost::format( "%-15E" ) % t_;
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-15E" ) % buffer_[i][1];
		}
			std::cout << std::endl;		
		}

	void clearBuffers(){
		buffer_index_ = 0;
	}

	
};
