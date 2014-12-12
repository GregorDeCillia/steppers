#pragma once

#include "../stepperBase.h"
#include "../rkStepper/ode45Stepper.cpp"

#include <boost/format.hpp>
#include <iostream>

#include "predictor/predictorBase.h"
#include "corrector/correctorBase.h"

class multiStepper : public stepper
{
protected:
  buffer_type buffer_x_;
  buffer_type buffer_dx_;
  int buffer_index_;
  int nCorrSteps_;

  predictor* predictor_;
  corrector* corrector_;
  rkStepper* singleStepper_;

public:

  ~multiStepper(){
	  delete predictor_;
	  delete corrector_;
	  delete singleStepper_;
  }

 multiStepper( unsigned int nStates, int ord, rhs_type f,
               int nCorrSteps, string name,
               predictor* predictor,
               corrector* corrector,
               rkStepper* singleStepper
               ) : stepper( nStates , f, ord , name ),
	  buffer_x_( ord ),
	  buffer_dx_( ord ),
	  buffer_index_( 0 ),
	  nCorrSteps_( nCorrSteps ),
	  predictor_( predictor ),
	  corrector_( corrector ),
	  singleStepper_( singleStepper )
	  {
		  if ( singleStepper_->getOrder() < ord )
			  std::cout << "Warning: The singlestepmethod " <<
				  singleStepper_->getName() <<
				  " has a lower order than the multistepmethod " << name
			            << " it is part of." << std::endl;
	                            };

	void printBuffer(){
		std::cout << boost::format( "%-15E" ) % t_;
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-15E%-15E" ) % buffer_x_[i][1] % buffer_dx_[i][1];
		}
			std::cout << std::endl;		
		}

	void clearBuffers(){
		buffer_index_ = 0;
		buffer_x_.insert_element( buffer_index_,  x_ );
		buffer_dx_.insert_element( buffer_index_,  f( t_, x_ ) );
		buffer_index_++;
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
		dx_ = ( *f )( t_, x_);
        clearBuffers();
	}

	void setRHS( rhs_type rhs ){
		f = rhs;
		singleStepper_->setRHS( rhs );
		predictor_->setRHS( rhs );
		corrector_->setRHS( rhs );
	}

	void doStep( time_type h ){
		if ( h != h_ ){
			buffer_index_ = 0;
			h_ = h;
		}
		if ( buffer_index_ < 4 )
			{
				singleStepper_->setStates( t_, x_ );
				singleStepper_->doStep( h );
				singleStepper_->getStates( t_, x_ );
				buffer_x_.insert_element( buffer_index_,  x_ );
				buffer_dx_.insert_element( buffer_index_,  f( t_, x_ ) );
				buffer_index_++;
			}
		else{
			// calculate the predictor
			predictor_->predict( t_, x_, h_, buffer_x_, buffer_dx_ );

			// make corrector steps
			for( int i = 0; i < nCorrSteps_; i++ )
				corrector_->correct( t_, x_, h_, buffer_x_, buffer_dx_ );

			// cycle the buffer and fill in the new value
			buffer_x_[0]  = buffer_x_[1];
			buffer_x_[1]  = buffer_x_[2];
			buffer_x_[2]  = buffer_x_[3];
			buffer_x_[3]  = x_;

			buffer_dx_[0] = buffer_dx_[1];
			buffer_dx_[1] = buffer_dx_[2];
			buffer_dx_[2] = buffer_dx_[3];
			buffer_dx_[3] = f( t_, x_ );

			dx_           = buffer_dx_[3];

		}
	}

	
};
