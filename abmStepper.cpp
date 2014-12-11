#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

#include "typedefs.h"
#include "stepperBase/stepperBase.h"
#include "rk4Stepper.cpp"

#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

class abmStepper: public stepper
{
private:
	buffer_type buffer_;
	int buffer_index_;

	rk4Stepper singleStepper_;

public:

	abmStepper( unsigned int nStates , rhs_type f) :
		stepper( nStates, f ),
		buffer_( 4 ),
		buffer_index_( 0 ),
		singleStepper_( nStates, f )
	{
		ord_ = 4;
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
			state_type xAB = x_ + h*(  55.0/24.0*buffer_[3] 
			                           - 59.0/24.0*buffer_[2] 
			                           + 37.0/24.0*buffer_[1] 
			                           - 03.0/08.0*buffer_[0] );
			t_+=h;
			// make corrector step
			for( int i = 0; i < ord_; i++ ){
				xAB = x_ + h*(  251.0/720.0*f(t_,xAB)  + 646.0/720.0*buffer_[3]
				               -264.0/720.0*buffer_[2] + 106.0/720.0*buffer_[1]
				               -019.0/720.0*buffer_[0] );
			}
			x_ = xAB;
			// cycle the buffer and fill in the new value
			buffer_[0] = buffer_[1]; 
			buffer_[1] = buffer_[2]; 
			buffer_[2] = buffer_[3];
			buffer_[3] = f( t_, x_ );
			dx_ = buffer_[3];

		}
	}
};
