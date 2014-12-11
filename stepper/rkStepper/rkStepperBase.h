#pragma once

#include <iostream>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "../stepperBase.h"

class rkStepper: public stepper
{
 protected:
	int butcher_size; 
	buffer_type k_;
	matrix<value_type> A;
    vector<value_type> b;
    vector<value_type> c;
	state_type x2_;

	void calculateC()
	{
		for ( int i = 0; i < butcher_size; i++ ){
			c[ i ] = 0;
			for ( int j = 0; j < butcher_size; j++ )
				c[i] += A( i, j );
		}
	}

	
 public:
 rkStepper( unsigned int nStates, rhs_type f, string name, 
	            int butcher_size, int ord ) : stepper( nStates, f, ord, name ),
		butcher_size( butcher_size ),
		k_( butcher_size + 1 ),
		A( butcher_size, butcher_size ),
		b( butcher_size + 1 ),
		c( butcher_size ),
		x2_( nStates ){
		};		

	void doStep( time_type h ){
		k_[0] = f( t_, x_ );
		for ( int i = 1; i < ( butcher_size + 1 ); i++ ){
			x2_ *= 0;
			for ( int j = 0; j < i; j++ ){
				x2_ += A(i-1,j) *k_[j];
			}
			k_[i] = f( t_ + h*c[i-1], x_+h*x2_ );
		}
		x2_ *= 0;
		for ( int i = 0; i < butcher_size+1; i++ ){
			x2_ += k_[i]*b[i];
		}
		x_ = x_ + h*x2_;
		t_ += h;
	}

};
