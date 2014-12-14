#pragma once

#include <iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "../stepperBase.h"

/// single stepper of the [runge kutta](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods) type
class rkStepper: public stepper
{
 protected:
	int butcher_size;
	buffer_type k_;
	coefficient_matrix A;
	coefficient_vector b;
    coefficient_vector c;
	state_type x2_;

	void calculateC()
	{
		for ( int i = 0; i < butcher_size; i++ ){
			c[ i ] = 0;
			for ( int j = 0; j < butcher_size; j++ )
				c[i] += A[i][j];
		}
	}

	
 public:
 rkStepper( unsigned int nStates, rhs_type f, string name, int ord,
            coefficient_vector b, 
            coefficient_matrix A
            ) : stepper( nStates, f, ord, name ),
		butcher_size( b.size() - 1 ),
		k_( butcher_size + 1 ),
		b( b ),
		A( A ),
		c( butcher_size ),
		x2_( nStates ){ 
			calculateC();
		};		

	void doStep( time_type h ){
		k_[0] = f_( t_, x_ );
		for ( int i = 1; i < ( butcher_size + 1 ); i++ ){
			x2_ *= 0;
			for ( int j = 0; j < i; j++ ){
				x2_ += A[i-1][j] *k_[j];
			}
			k_[i] = f_( t_ + h*c[i-1], x_+h*x2_ );
		}
		x2_ *= 0;
		for ( int i = 0; i < butcher_size+1; i++ ){
			x2_ += k_[i]*b[i];
		}
		x_ = x_ + h*x2_;
		t_ += h;
	}

};
