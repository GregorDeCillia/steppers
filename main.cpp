#include "include/typedefs.h"
#include "stepper/multiStepper/abmStepper.cpp"
#include "stepper/multiStepper/bdfStepper.cpp"
#include "stepper/rkStepper/ode12Stepper.cpp"
#include "stepper/rkStepper/ode45Stepper.cpp"

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
	std::cout << stepper.getName() << "\t";
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

	ode45Stepper stepper1( nStates, f );
	runSimulation( stepper1 );

	abmStepper stepper2( nStates, f );
	runSimulation( stepper2 );

	bdfStepper stepper3( nStates, f );
	runSimulation( stepper3 );

	ode12Stepper stepper4( nStates, f );
	runSimulation( stepper4 );

}
