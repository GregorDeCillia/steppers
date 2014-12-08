#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

#include <boost/numeric/ublas/io.hpp>
#include "typedefs.h"
#include "stepperBase.h"

using namespace boost::numeric::ublas;

class bdfStepper: public stepper
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
	bdfStepper( unsigned int nStates ) : 
		stepper( nStates ),
		buffer_( 4 ),
		buffer_index_( 0 ){
	};

	state_type f( time_type t, state_type x ){
		value_type k = 100;
		return( x ); 
	}

	void setStates( time_type t, state_type x ){
		if ( t == t_ )
			{
			bool flag = true;
			for ( int i = 0; i < nStates_; i++ )
				if ( x[i] != x_[i] ); flag = false;
			if ( flag )
				return;
			}
		t_ = t;
		x_ = x;
		dx_ = f( t_, x_);
		buffer_index_ = 1;
		buffer_[0] = x_;
		std::cout << x_[0] << std::endl;
	}

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
			rk4step( h );
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

int main(){
	int nSteps = pow(2,8);
	std::cout << "number of steps: " << nSteps << std::endl;
	int nStates = 1;
	bdfStepper stepper( nStates );
	time_type t,t2 = 0;
	state_type x(nStates), x2(nStates);
	for ( int i = 0; i < nStates; i++ )
		x[i]= i+1;
	
	stepper.printLabels();
	stepper.setStates(t,x);
	
	stepper.printStates();
	
	for ( int i = 0; i < nSteps; i++ ){
		stepper.doStep( 1.0/nSteps );
	}
	stepper.printStates();
	// calculate the errors
	stepper.getStates( t, x2 );
	t = t - 1; x2 = x2 - x*exp(1);
	// write errors into model to print ( buffer gets lost )
	stepper.setStates(t, x2);
	std::cout << "Errors:" << std::endl;
	stepper.printStates();
	
}
