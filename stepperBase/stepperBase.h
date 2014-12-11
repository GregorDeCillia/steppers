#pragma once

#include "../typedefs.h"

class stepper{
 protected:
	int ord_;
	unsigned int nStates_;
	time_type h_;
	time_type t_;
	state_type x_;
	state_type dx_;


	virtual state_type f( time_type t, state_type x ) = 0;

 public:

 stepper( int nStates ) : ord_(1), nStates_( nStates ){};

	void getStates( time_type &t, state_type &x ){
		t = t_;
		x = x_;
	}
 
	void printStates(){
		std::cout << boost::format( "%-15E" ) % t_;
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-15E" ) % x_[i];
		}
		std::cout << std::endl;
	}


	void setStates( time_type t, state_type x ){
		if ( t == t_ )
			{
				bool flag = true;
				for ( int i = 0; i < nStates_; i++ )
					if ( x[i] != x_[i] ); flag = false;
				if ( flag )
					return;
			}
		t_ = t;
		x_ = x;
		dx_ = f( t_, x_);
		clearBuffers();
	}

	void printLabels(){
		std::cout << boost::format( "%-15s" ) % "time";
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-1s%-14i" ) % "x" % i;
		}
		std::cout << std::endl;
	}	

	virtual void clearBuffers(){};
	virtual void doStep( time_type h ) = 0;
};
