#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

#include "typedefs.h"
#include "abmStepper.cpp"
#include "bdfStepper.cpp"
#include "rk4Stepper.cpp"

using namespace std;

template <class STEPPERTYPE>
void runSimulation( STEPPERTYPE stepper, 
                    time_type t0, 
                    state_type x0, 
                    int nSteps = pow( 2, 8 ) )
{
	time_type t;
	state_type x = x0;
	stepper.setStates( t0, x0 );
	for ( int i = 0; i < nSteps; i++ ){
		stepper.doStep( 1.0/nSteps );
	}
	stepper.getStates( t, x );
	stepper.setStates( t - 1, x - x0*exp(1) );
	stepper.printStates();	
}

template <class STEPPERTYPE>
void runSimulation( STEPPERTYPE stepper, 
                    time_type t0 = 0 )
{
	state_type x0( 1 );
	x0[0] = 1;
	runSimulation( stepper, t0, x0 );

}

state_type f(time_type t, state_type x)
{
	return( x );
} 


int main()
{
	int nStates = 1;  

	state_type x0( 1 );
	x0[0] = 1; 
	time_type t0 = 0;

	abmStepper abmStepper( nStates, f );
	runSimulation( abmStepper );

	bdfStepper bdfStepper( nStates, f );
	runSimulation( bdfStepper );

	rk4Stepper rk4Stepper( nStates, f );
	runSimulation( rk4Stepper );
}
