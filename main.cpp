#include "include/typedefs.h"
#include "iterator/stepper/multiStepper/abmStepper.cpp"
#include "iterator/stepper/multiStepper/bdfStepper.cpp"
#include "iterator/stepper/rkStepper/ode12Stepper.cpp"
#include "iterator/stepper/rkStepper/ode23Stepper.cpp"
#include "iterator/stepper/rkStepper/ode34Stepper.cpp"
#include "iterator/stepper/rkStepper/ode45Stepper.cpp"
#include "iterator/stepper/rkStepper/threeEightStepper.cpp"
#include "iterator/stepper/rkStepper/fehlbergStepper.cpp"

#include "iterator/stepper/eulerStepper.cpp"
#include "iterator/predictor/abPredictor/ab2Predictor.cpp"
#include "iterator/predictor/abPredictor/ab3Predictor.cpp"
#include "iterator/predictor/abPredictor/ab5Predictor.cpp"

#include "iterator/predictor/lagrangePredictor.cpp"
#include "iterator/corrector/amCorrector/am1Corrector.cpp"
#include "iterator/corrector/amCorrector/am2Corrector.cpp"
#include "iterator/corrector/amCorrector/am3Corrector.cpp"
#include "iterator/corrector/amCorrector/am4Corrector.cpp"
#include "iterator/corrector/amCorrector/am5Corrector.cpp"

#include <boost/numeric/ublas/io.hpp>

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

	if ( p-1 != stepper->getOrder() )
		{			
			std::cout << "wrong order specified for " << stepper->getName()
			          << std::endl;
		}

	return( p - 1 );
}


void runSimulation( stepper* stepper,
                    bool deleteStepper = true )
{
	// starting conditions for the simulation
	state_type x0( 1 );
	x0[0] = 1;
	time_type t0 = 0; 

	int nSteps = pow( 2, 8 );

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


int convergenceOrder( predictor* predictor )
{
	state_type x0( 1 ), x( 1 );
	time_type t0 = 0, t=0;
	int buffer_size = predictor->getBufferSize();
	x0[0] = 1;
	x[0] = 0;
	predictor->setRHS( f2 );

	bool stepperFailed = false;
	p = 0;
	buffer_type buff_x_( buffer_size );
	buffer_type buff_dx_( buffer_size );

	while ( !stepperFailed && p<10 ){
		for ( int i  = 0; i < buffer_size; i++ ){
			buff_x_[i]=x0*pow(-i,p+1.0)/(p+1.0);
			buff_dx_[i]=x0*pow(-i,p);
		}
		
		predictor->predict( t, x, 1, buff_x_, buff_dx_ );
		if ( fabs( x[0] - 1.0/(1.0+p) ) > pow( 2, -10 ) ){
			stepperFailed = true;
		}
		p++;
	}

	std::cout << predictor->getName() << "\t" << p-1 << std::endl;
	return( p - 1 );

	if ( p-1 != predictor->getOrder() )
		{			
			std::cout << "wrong order specified for " << predictor->getName()
			          <<  std::endl;
		}

}

int convergenceOrder( corrector* corrector )
{
	state_type x0( 1 ), x( 1 ), x2(1);
	time_type t0 = 0, t=1;
	x0[0] = 1;
	x2[0] = 7;
	x[0] = 1/2;
	corrector->setRHS( f2 );

	bool stepperFailed = false;
	p = 0;
	buffer_type buff_x_(4);
	buffer_type buff_dx_(4);

	while ( !stepperFailed && p<10 ){
		x = x2;
		for ( int i  = 0; i < 4; i++ ){
			buff_x_[i]=x0*pow(-i,p+1.0)/(p+1.0);
			buff_dx_[i]=x0*pow(-i,p);
		}
		for ( int j = 0; j < 8; j++){
			corrector->correct( t, x, 1, buff_x_, buff_dx_ );
		}
		if ( fabs( x[0] - 1.0/(1.0+p) ) > pow( 2, -10 ) ){
			stepperFailed = true;
		}
		p++;
	}

	std::cout << corrector->getName() << "\t" << p-1 << std::endl;

	if ( p-1 != corrector->getOrder() )
		{			
			std::cout << "wrong order specified for " << corrector->getName()
			          <<  std::endl;
		}

	return( p - 1 );
}


int convergenceOrder( multiStepper* multiStepper )
{
	state_type x0( 1 ), x( 1 );
	x0[0] = 0;
	x = x0;
	time_type t0 = 0;
	time_type t;
	multiStepper->setRHS( f2 );
	p = 0;

	bool stepperFailed = false;

	while( p<10 && !stepperFailed ){
		multiStepper->setStates( t0, x0 );
		for ( int i = 0; i < 6; i++ )
			{
				multiStepper->doStep( 1 );
				multiStepper->getStates( t, x );
				if ( fabs( x[0] - pow( t, 1.0 + p )/( 1.0 + p ) ) > pow( 2, -10 ) ){
					stepperFailed = true;
				}
			}
		p++;
	}
	std::cout << multiStepper->getName() << "\t" << p - 1 << std::endl;
	if ( p-1 != multiStepper->getOrder() )
		{			
			std::cout << "wrong order specified for " << multiStepper->getName()
			          <<  std::endl;
		}
	return ( p - 1 );
}


state_type f(time_type t, state_type x)
{
	return( x );
}

int main()
{
	int nStates = 1;
	
	// simulations
	runSimulation( new ode12Stepper( nStates, f ) );
	runSimulation( new ode23Stepper( nStates, f ) );
	runSimulation( new ode34Stepper( nStates, f ) );
    runSimulation( new ode45Stepper( nStates, f ) );

	runSimulation( new threeEightStepper( nStates, f ) );
	runSimulation( new fehlbergStepper( nStates,f ) );

	runSimulation( new abmStepper  ( nStates, f ) );
	runSimulation( new bdfStepper  ( nStates, f ) );

	// convergence orders of predictors and
	// correctors
	
	convergenceOrder( new ab2Predictor( f ) );
	convergenceOrder( new ab3Predictor( f ) );
	convergenceOrder( new ab4Predictor( f ) );
	convergenceOrder( new ab5Predictor( f ) );
	convergenceOrder( new lagrangePredictor( f, 4 ) );

	convergenceOrder( new abmCorrector( f ) );
	convergenceOrder( new bdfCorrector( f ) );

	// convergence order for multistep methods
	convergenceOrder( new bdfStepper( nStates, f ) );
	convergenceOrder( new abmStepper( nStates, f ) );

	convergenceOrder( new am1Corrector( f ) );
	convergenceOrder( new am2Corrector( f ) );
	convergenceOrder( new am3Corrector( f ) );
	convergenceOrder( new am4Corrector( f ) );
	convergenceOrder( new am5Corrector( f ) );

}
