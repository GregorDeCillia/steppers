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


int convergenceOrder( stepper* stepper )
{
	state_type x0( 1 ), x( 1 );
	time_type t0 = 0, t;
	x0[0] = 0;
	stepper->setRHS( f2 );

	bool stepperFailed = false;
	p = 0;
	while ( !stepperFailed && p<10 ){
		stepper->setStates( t0, x0 );
		stepper->doStep( 1.0 );
		stepper->getStates( t, x );
		if ( fabs( x[0] - 1.0/(1.0+p) ) > pow( 2, -10 ) ){
			stepperFailed = true;
		}
		p++;
	}
	return( p - 1 );
}


void runSimulation( stepper* stepper,
                    int nSteps,
                    bool deleteStepper,
                    time_type t0, 
                    state_type x0
                    )
{
	time_type t;
	state_type x = x0;
	stepper->setStates( t0, x0 );
	for ( int i = 0; i < nSteps; i++ ){
		stepper->doStep( 1.0/nSteps );
	}
	stepper->getStates( t, x );
	std::cout << stepper->getName() << "\t" << convergenceOrder( stepper ) << "\t";
	stepper->printStates( t - 1, x - x0*exp(1) );

	if ( deleteStepper )
		delete stepper;
}

void runSimulation( stepper* stepper,
                    bool deleteStepper = true,
                    int nSteps = pow( 2, 8 ),
                    time_type t0 = 0 )
{
	state_type x0( 1 );
	x0[0] = 1;
	runSimulation( stepper, nSteps, deleteStepper, t0, x0 );
}

state_type f(time_type t, state_type x)
{
	return( x );
}

int main()
{
	int nStates = 1;
	bool deleteSteppers = true;

	runSimulation( new ode45Stepper( nStates, f ) );
	runSimulation( new abmStepper( nStates, f ) );
	runSimulation( new bdfStepper( nStates, f )  );
	runSimulation( new ode12Stepper( nStates, f ) );
	runSimulation( new ode23Stepper( nStates, f ) );
	runSimulation( new ode34Stepper( nStates, f ) );

}
