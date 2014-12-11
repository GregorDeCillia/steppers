#pragma once

#include "../include/typedefs.h"
#include <boost/format.hpp>

class stepper{

protected:
    int ord_;
    string name_;
    unsigned int nStates_;
	time_type h_;
	time_type t_;
	state_type x_;
	state_type dx_;

	rhs_type f;

public:

stepper( int nStates, rhs_type f , int ord , string name ) : ord_(ord),
		name_( name ),
		nStates_( nStates ),
		x_( nStates ),
		dx_( nStates ),
		f( f ) {};

	void getStates( time_type &t, state_type &x ){
		t = t_;
		x = x_;
	}

	int getOrder(){
		return ord_;
	}

	string getName(){
		return  name_;
	}
 
	void printStates(){
		std::cout << boost::format( "%-15E" ) % t_;
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-15E" ) % x_[i];
		}
		std::cout << std::endl;
	}


	void setStates( time_type t, state_type x ){
		t_ = t;
		x_ = x;
		dx_ = f( t_, x_);
	}

	void printLabels(){
		std::cout << boost::format( "%-15s" ) % "time";
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-1s%-14i" ) % "x" % i;
		}
		std::cout << std::endl;
	}	

	virtual void doStep( time_type h ) = 0;
};