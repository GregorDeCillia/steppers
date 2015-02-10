#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/io.hpp>


using namespace boost::numeric::ublas;

typedef double     value_type;
typedef value_type time_type;
typedef vector<value_type> state_type;
typedef vector<state_type> storage_type;

void rhs( const state_type &x, state_type &dx, const time_type t )
{
	dx[0] = cos(t);
}

/// adams bashforth moulton method with adaptive step size
class vode{
	matrix<value_type> B;	///< coefficient matrix for the predictor
	state_type r;			///< coefficient vector for the corrector
	storage_type derivs;	///< vector of derivatives 0 to 3, scled by stepsize
	double step_size;		///< internal stepsize
	time_type t;			///< internal time
	/// helper function for the constructor
	int factorial( int i )
	{
		if ( i == 0 ) 
			return 1;
		return( i * factorial( i - 1 ) );
	}
	/// calculates the predictor using the taylor formula
	void predict(){
			for ( int i = 0; i < 4; i++ )
				for ( int j = i+1; j < 4; j++ )
					derivs[i] += B( i, j )*derivs[j];
	}
	/// calculates the corrector
	void correct(){
		state_type f( 1 );
		rhs( derivs[0], f, t );
		state_type alpha = step_size*f - derivs[1];
		for ( int i = 0; i < 4; i++ )
			derivs[i] = derivs[i] + r[i] * alpha;
	}
public:
	/// constrctor. requires three derivatives in the statring position
	vode( storage_type derivatives /* y(t0), y'(t0), y''(t0), y'''(t0) */,
		  time_type t0,
		  value_type stepsize ) : 
		B( 4, 4 ),
		r( 4 ),
		derivs( 4 ),
		step_size( 1 ),
		t( t0 )
	{
		/// * set the elements of \f$B\f$ and \f$r\f$
		B<<= 1, 1, 1, 1,
			0, 1, 2, 3,
			0, 0, 1, 3,
			0, 0, 0, 1;
		r<<= 5.0/12.0, 1.0, 3.0/4.0, 1.0/6.0;
		/// * rescale the derivatives
		for ( int i = 0; i < 4; i++ )
			derivs[i] = derivatives[i]/factorial( i );

		set_stepsize( stepsize );
	}
	/// change the step_size. this also rescales the derivatives
	void set_stepsize( double newstepsize )
	{
		for ( int i = 0; i < 4; i++ )
			derivs[i] = derivs[i]*pow( newstepsize/step_size, i );
		step_size = newstepsize;
	}
	/// print the derivatives to screen using boost/numeric/ublas/io.hpp
	void printderivs()
	{
		std::cout << derivs << std::endl;
	}
	/// make a step with the internal step size and internal states
	void do_step(){
		/** the prdictor of the formula is just the taylor formula for all derivatives
		 * \f{eqnarray*}{
		 *           y_{i+1}  &=& y_i+h\dot{y}_i + h^2/2 \ddot{y}_i
		 *               + h^3/6 \dot{\ddot{y}}_i   \\
		 *      \dot{y}_{i+1} &=& \dot{y}_i+h\ddot{y}_i + h^2/2 \dot{\ddot{y}}_i\\
		 *      \ddot{y}_{i+1} &=& \ddot{y}_i + h\dot{\ddot{y}}_i\\
		 *      \dot{\ddot{y}}_{i+1} &=& \dot{\ddot{y}}_{i}  
		 * \f}
		 */
		predict();
		t += step_size;
		correct();
	}

	/// performs the actual step and updates all components of deriv as well as t
	void do_step( time_type dt )
	{
		set_stepsize( dt );
		do_step();
	}
	/// get internal time
	value_type time(){
		return t;
	}
	/// get internal state ( first element of the derivatives vector )
	state_type get_state(){
		return derivs[0];
	}	
};


main()
{
	storage_type derivatives(4);
	state_type x(1);
	x[0] = 1; 	

	derivatives[0] = 0*x; derivatives[1] = 1*x; 
	derivatives[2] = 0*x; derivatives[3] = -1*x; 
	int nsteps = 1000;
	vode stepper( derivatives, 0.0, 1.0/nsteps );
	for ( int i = 0; i < nsteps; i++ ){
		stepper.do_step();
		//	std::cout << "Error:" << sin( stepper.time() ) - stepper.get_state()[0] << std::endl;

	}
	std::cout << "Error:" << sin( stepper.time() ) - stepper.get_state()[0] << std::endl;

	nsteps *= 1000;
	stepper.set_stepsize( 1.0/nsteps );
	stepper.do_step();

	std::cout << "Error:" << sin( stepper.time() ) - stepper.get_state()[0] << std::endl;

	stepper.do_step();
	std::cout << "Error:" << sin( stepper.time() ) - stepper.get_state()[0] 
			  << std::endl;
	stepper.do_step();
	std::cout << "Error:" << sin( stepper.time() ) - stepper.get_state()[0] 
			  << std::endl;
	stepper.do_step();
	std::cout << "Error:" << sin( stepper.time() ) - stepper.get_state()[0] 
			  << std::endl;
}
