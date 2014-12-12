#include "include/typedefs.h"
#include "stepper/multiStepper/abmStepper.cpp"
#include "stepper/multiStepper/bdfStepper.cpp"
#include "stepper/rkStepper/ode12Stepper.cpp"
#include "stepper/rkStepper/ode23Stepper.cpp"
#include "stepper/rkStepper/ode34Stepper.cpp"
#include "stepper/rkStepper/ode45Stepper.cpp"
#include "stepper/rkStepper/threeEightStepper.cpp"
#include "stepper/rkStepper/fehlbergStepper.cpp"

static int p = 1;

static state_type f2( time_type t, state_type x )
{
	x[0] = pow( t, p );
	return( x );
}

template <class STEPPERTYPE>
int convergenceOrder( STEPPERTYPE stepper )
{
	state_type x0( 1 ), x( 1 );
	time_type t0 = 0, t;
	x0[0] = 0;
	stepper.setRHS( f2 );

	bool stepperFailed = false;
	p = 0;
	while ( !stepperFailed && p<10 ){
		stepper.setStates( t0, x0 );
		stepper.doStep( 1.0 );
		stepper.getStates( t, x );
		if ( fabs( x[0] - 1.0/(1.0+p) ) > pow( 2, -10 ) ){
			stepperFailed = true;
		}
		p++;
	}
	return( p - 1 );
}

template <class STEPPERTYPE>
void runSimulation( STEPPERTYPE stepper,
                    int nSteps,
                    time_type t0, 
                    state_type x0
                    )
{
	time_type t;
	state_type x = x0;
	stepper.setStates( t0, x0 );
	for ( int i = 0; i < nSteps; i++ ){
		stepper.doStep( 1.0/nSteps );
	}
	stepper.getStates( t, x );
	std::cout << stepper.getName() << "\t" << convergenceOrder( stepper ) << "\t";
	stepper.printStates( t - 1, x - x0*exp(1) );

}

template <class STEPPERTYPE>
void runSimulation( STEPPERTYPE stepper,
                    int nSteps = pow( 2, 8 ),
                    time_type t0 = 0 )
{
	state_type x0( 1 );
	x0[0] = 1;
	runSimulation( stepper, nSteps, t0, x0 );
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

	ode23Stepper stepper5( nStates, f );
	runSimulation( stepper5 );

	ode34Stepper stepper6( nStates, f );
	runSimulation( stepper6 );

	threeEightStepper stepper7( nStates, f );
	runSimulation( stepper7 );

	fehlbergStepper stepper8( nStates, f );
	runSimulation( stepper8 );

}
