#pragma once

#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

#include <boost/numeric/ublas/io.hpp>
#include "typedefs.h"
#include "stepperBase/stepperBase.h"
#include "rk4Stepper.cpp"

using namespace boost::numeric::ublas;

class bdfStepper: public stepper
{
private:
	buffer_type buffer_;
	int buffer_index_;

	rk4Stepper singleStepper_;

public:
	bdfStepper( unsigned int nStates, rhs_type f ) : 
		stepper( nStates, f ),
		buffer_( 4 ),
		buffer_index_( 0 ),
		singleStepper_( nStates, f )
	{
		ord_ = 4;
	};

	void clearBuffers(){
		buffer_index_ = 0;
	};

	void printBuffer(){
		std::cout << boost::format( "%-15E" ) % t_;
		for ( unsigned int i = 0; i < buffer_index_; i++ ){
			std::cout << boost::format( "%-15E" ) % buffer_[i][0];
		}
		std::cout << std::endl;		
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
				buffer_.insert_element( buffer_index_,  x_ );
				buffer_index_++;
			}
		else{
			// calculate the predictor
			x_ = - 1.0*buffer_[0] + 4.0*buffer_[1]
				- 6.0*buffer_[2] + 4.0*buffer_[3] ;
			t_+=h;
			// make corrector step
			for( int i = 0; i < ord_; i++ ){
				x_=+01.0/25.0*( 48.0*buffer_[3]-36.0*buffer_[2]
				                +16.0*buffer_[1]-03.0*buffer_[0] )
					+12.0/25.0*h*f(t_,x_);
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
