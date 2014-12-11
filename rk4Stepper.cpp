#pragma once

#include <boost/numeric/ublas/vector.hpp>

#include "typedefs.h"
#include "stepperBase/stepperBase.h"

using namespace std;

class rk4Stepper: public stepper
{
public:
	deriv_type k1, k2, k3, k4;

	rk4Stepper( unsigned int nStates , rhs_type f ) :
		stepper( nStates, f , 4, "rk4" ),
		k1( nStates ),
		k2( nStates ),
		k3( nStates ),
		k4( nStates ){};

	void doStep( time_type h ){
		k1 = dx_;
		k2 = f( t_ + h/2.0 , x_ + k1*h/2.0 );
		k3 = f( t_ + h/2.0 , x_ + k2*h/2.0 );
		k4 = f( t_ + h     , x_ + k3*h );
		x_ = x_ + h/6.0*( k1 + 2.0*k2 + 2.0*k3 + k4 );
		t_ = t_ + h;
		dx_ = f( t_, x_ );
	}

};

