#include "include/typedefs.h"

#include "iterator/predictor/abPredictor/createAbPredictor.cpp"
#include "iterator/corrector/amCorrector/newAmCorrector.cpp"
#include "iterator/corrector/bdfCorrector/newBdfCorrector.cpp"

#include "iterator/stepper/multiStepper/abmStepper.cpp"
#include "iterator/stepper/multiStepper/bdfStepper.cpp"
#include "iterator/stepper/rkStepper/ode12Stepper.cpp"
#include "iterator/stepper/rkStepper/ode23Stepper.cpp"
#include "iterator/stepper/rkStepper/ode34Stepper.cpp"
#include "iterator/stepper/rkStepper/ode45Stepper.cpp"

#include "iterator/stepper/rkStepper/threeEightStepper.cpp"
#include "iterator/stepper/rkStepper/fehlbergStepper.cpp"

#include "iterator/stepper/eulerStepper.cpp"

#include "iterator/predictor/lagrangePredictor.cpp"

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
		if ( fabs( x[0] - 1.0/(1.0+p) ) > pow( 2, -20 ) ){
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
	x0[0] = 1.0;
	time_type t0 = 0; 

	int nSteps = pow( 2, 8 );

	time_type t;
	state_type x = x0;
	stepper->setStates( t0, x0 );
	for ( int i = 0; i < nSteps; i++ ){
		stepper->doStep( 1.0/nSteps );
		stepper->getStates( t, x );
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
		if ( fabs( x[0] - 1.0/(1.0+p) ) > pow( 2, -20 ) ){
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
	int buffer_size = corrector->getBufferSize();
	p = 0;
	buffer_type buff_x_( buffer_size );
	buffer_type buff_dx_( buffer_size );

	while ( !stepperFailed && p<10 ){
		x = x2;
		for ( int i  = 0; i < buffer_size; i++ ){
			buff_x_[i]=x0*pow(-i,p+1.0)/(p+1.0);
			buff_dx_[i]=x0*pow(-i,p);
		}
		for ( int j = 0; j < 8; j++){
			corrector->correct( t, x, 1, buff_x_, buff_dx_ );
		}
		if ( fabs( x[0] - 1.0/(1.0+p) ) > pow( 2, -20 ) ){
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
	int buffer_size = multiStepper->getBufferSize();
	p = 0;

	bool stepperFailed = false;

	while( p<10 && !stepperFailed ){
		multiStepper->setStates( t0, x0 );
		for ( int i = 0; i < buffer_size + 2; i++ )
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
	
	/**   simulations ( inputs get cast to iterator ) **/
	// rk
	runSimulation( new ode12Stepper( nStates, f ) );
	runSimulation( new ode23Stepper( nStates, f ) );
	runSimulation( new ode34Stepper( nStates, f ) );
    runSimulation( new ode45Stepper( nStates, f ) );
	runSimulation( new threeEightStepper( nStates, f ) );
	runSimulation( new fehlbergStepper( nStates,f ) );



	/** convergence orders of predictors and correctors **/
	// abPredictor
	for ( int i = 1; i <= 5; i++ )
		convergenceOrder( newAbPredictor( f, i ) );

	// lagrangePredictor
	for ( int i = 1; i <= 10; i++ )
		convergenceOrder( new lagrangePredictor( f, i ) );

	/** convergence oder for correctors **/
	// the old abmCorrector
	convergenceOrder( new abmCorrector( f ) );
	// abmCorrectors

	for ( int i = 1; i <= 5; i++ )
		convergenceOrder( newAmCorrector( f, i ) );

	// bdfCorrectors
	for ( int i = 1; i <= 6; i++ )
		convergenceOrder( newBdfCorrector( f, i ) );

	// multistepper
	runSimulation( new abmStepper  ( nStates, f ) );
	runSimulation( new bdfStepper  ( nStates, f ) );

	/** convergence order for multistep methods 	**/
	convergenceOrder( new abmStepper( nStates, f ) );
	convergenceOrder( new bdfStepper( nStates, f ) );

}
