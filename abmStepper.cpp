#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

#include "typedefs.h"
#include "stepperBase/stepperBase.h"

#include <boost/numeric/ublas/io.hpp>

using namespace boost::numeric::ublas;

class abmStepper: public stepper
{
private:
	buffer_type buffer_;
	int buffer_index_;

	void rk4step( time_type h ){
		deriv_type k1 = dx_;
		deriv_type k2 = f ( t_ + h/2.0 , x_ + k1*h/2.0 );
		deriv_type k3 = f ( t_ + h/2.0 , x_ + k2*h/2.0 );
		deriv_type k4 = f ( t_ + h     , x_ + k3*h ); 
		x_ = x_ + h/6.0*( k1 + 2.0*k2 + 2.0*k3 + k4 );
		t_ = t_ + h;
		dx_ = f( t_, x_ );
	}
	

public:
	abmStepper( unsigned int nStates ) :
		stepper( nStates ),
		buffer_( 4 ),
		buffer_index_( 0 ){
	};

	state_type f(time_type t, state_type x){
		value_type k = 100;
		return( x ); 
	}

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
		if ( h != h_ )
			buffer_index_ = 0;
		h_ = h;
		//std::cout << buffer_ << std::endl;
		//std::cout << buffer_.size() << std::endl;
		if ( buffer_index_ < 4 )
			{
			rk4step( h );
			buffer_.insert_element( buffer_index_,  dx_ );
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

int main(){
	int nSteps = pow(2,5);
	std::cout << "number of steps: " << nSteps << std::endl;
	int nStates = 4;
	abmStepper stepper( nStates );
	time_type t,t2 = 0;
	state_type x(nStates), x2(nStates);
	for ( int i = 0; i < nStates; i++ )
		x[i]= i;
	stepper.printLabels();
	stepper.setStates(t,x);
	stepper.printStates();
	for ( int i = 0; i < nSteps; i++ ){
		stepper.doStep( 1.0/nSteps );
	}
	stepper.printStates();
	stepper.getStates( t, x2 );
	t = t - 1; x2 = x2 - x*exp(1);
	stepper.setStates(t, x2);
	std::cout << "Errors:" << std::endl;
	stepper.printStates();
}
