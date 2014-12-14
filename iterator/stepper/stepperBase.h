#pragma once

#include "../iteratorBase.h"
#include <boost/format.hpp>

class stepper : public iterator{

protected:
	/// dimension of the state space
    unsigned int nStates_;
    /// step size. Gets updated by each call of doStep
	time_type h_;
	/// time
	time_type t_;
	/// state
	state_type x_;
	/// derivative
	state_type dx_;

public:

stepper( int nStates, rhs_type f , int ord , string name ) : 
	iterator( f, name, ord ),
		nStates_( nStates ),
		x_( nStates ),
		dx_( nStates ){};

	void getStates( time_type &t, state_type &x ){
		t = t_;
		x = x_;
	}

	void printStates( time_type t, state_type x, bool printName = false )
	{
		if ( printName )
			std::cout << boost::format( "%-15s" ) % name_;
		std::cout << boost::format( "%-15E" ) % t;
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-15E" ) % x[i];
		}
		std::cout << std::endl;
	}

	void printStates(){
		printStates( t_, x_ );
	}

	virtual void setStates( time_type t, state_type x ){
		t_ = t;
		x_ = x;
		dx_ = f_( t_, x_);
	}

	void printLabels(){
		std::cout << boost::format( "%-15s" ) % "time";
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-1s%-14i" ) % "x" % i;
		}
		std::cout << std::endl;
	}
	/// perform a step
	virtual void doStep( time_type h ) = 0;
};
