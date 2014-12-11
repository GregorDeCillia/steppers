#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

#include <boost/numeric/ublas/io.hpp>
#include "typedefs.h"
#include "stepperBase/stepperBase.h"
using namespace boost::numeric::ublas;

class rk4Stepper: public stepper
{
private:
	state_type f( time_type t, state_type x ){
		value_type k = 100;
		return( x ); 
	}
public:
	rk4Stepper( unsigned int nStates ) :
		stepper( nStates )
	{
		ord_ = 4;
	};

	void doStep( time_type h ){
		deriv_type k1 = dx_;
		deriv_type k2 = f ( t_ + h/2.0 , x_ + k1*h/2.0 );
		deriv_type k3 = f ( t_ + h/2.0 , x_ + k2*h/2.0 );
		deriv_type k4 = f ( t_ + h     , x_ + k3*h ); 
		x_ = x_ + h/6.0*( k1 + 2.0*k2 + 2.0*k3 + k4 );
		t_ = t_ + h;
		dx_ = f( t_, x_ );
	}
};

