#pragma once

#include "../stepperBase.h"
#include "../rkStepper/rkStepperBase.h"

#include <boost/format.hpp>
#include <iostream>

#include "../../predictor/predictorBase.h"
#include "../../corrector/correctorBase.h"

/// base class for multisteppers
class multiStepper : public stepper
{
 private:
  buffer_type buffer_x_;
  buffer_type buffer_dx_;  
  int buffer_index_;
  int nCorrSteps_;
  int buffer_size_;
  predictor* predictor_;
  corrector* corrector_;
  rkStepper* singleStepper_;

  /// delete buffered values
  void clearBuffers(){
	  buffer_index_ = buffer_size_ - 1;
	  buffer_x_.insert_element( buffer_index_,  x_ );
	  buffer_dx_.insert_element( buffer_index_,  f_( t_, x_ ) );
	  buffer_index_--;
  }

 public:

  ~multiStepper(){
	  delete predictor_;
	  delete corrector_;
	  delete singleStepper_;
  }

 multiStepper( unsigned int nStates, int ord, int buffer_size, rhs_type f,
               int nCorrSteps, string name,
               predictor* predictor,
               corrector* corrector,
               rkStepper* singleStepper
               ) : stepper( nStates , f, ord , name ),
	  buffer_x_( buffer_size ),
	  buffer_dx_( buffer_size ),
	  buffer_index_( buffer_size-1 ),
	  nCorrSteps_( nCorrSteps ),
	  buffer_size_( buffer_size ),
	  predictor_( predictor ),
	  corrector_( corrector ),
	  singleStepper_( singleStepper )
	  {
		  if ( singleStepper_->getOrder() < ord )
			  std::cout << "Warning: The singlestepmethod " <<
				  singleStepper_->getName() <<
				  " has a lower order than the multistepmethod " << name
			            << " it is part of." << std::endl;
		  
		  if ( predictor_->getOrder() >= corrector_->getOrder() ){
			  std::cout << "Warning: your predictor is at least as accurate" 
			            << " as your corrector. Setting nCorrSteps to 0"
			            << std::endl;
			  nCorrSteps_ = 0;
		  }

		  if ( corrector_->getOrder() - predictor_->getOrder() != nCorrSteps_ )
			  std::cout << "wrong nuber of corrector steps in " 
			            << getName() << ": " << std::endl 
			            << "predictor Order" << predictor_->getOrder() << std::endl
			            << "corrector Order" << corrector_->getOrder() << std::endl
			            << "corrector Steps" << nCorrSteps_ << std::endl;		  
	  }

  int getBufferSize(){ return buffer_size_; } 

	void printBuffer(){
		std::cout << boost::format( "%-15E" ) % t_;
		for ( unsigned int i = 0; i < nStates_; i++ ){
			std::cout << boost::format( "%-15E%-15E" ) % buffer_x_[i][1] % buffer_dx_[i][1];
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
		dx_ = f_( t_, x_);
        clearBuffers();
	}

	void setRHS( rhs_type rhs ){
		f_ = rhs;
		singleStepper_->setRHS( rhs );
		predictor_->setRHS( rhs );
		corrector_->setRHS( rhs );
		clearBuffers();
	}

	void doStep( time_type h ){
		//std::cout << "do step. Buffer Index: " << buffer_index_ << std::endl;
		if ( h != h_ ){
			clearBuffers();
			h_ = h;
		}
		if ( buffer_index_ >= 0 )
			{
				singleStepper_->setStates( t_, x_ );
				singleStepper_->doStep( h );
				singleStepper_->getStates( t_, x_ );
				buffer_x_.insert_element( buffer_index_,  x_ );
				buffer_dx_.insert_element( buffer_index_,  f_( t_, x_ ) );
				buffer_index_--;
			}
		else{
			// calculate the predictor
			predictor_->predict( t_, x_, h_, buffer_x_, buffer_dx_ );

			// make corrector steps
			for( int i = 0; i < nCorrSteps_; i++ )
				corrector_->correct( t_, x_, h_, buffer_x_, buffer_dx_ );

			// cycle the buffer and fill in the new value
			for ( int i = buffer_size_-1; i > 0; i-- ){
				buffer_x_[i]  = buffer_x_[i-1];
				buffer_dx_[i] = buffer_dx_[i-1];
			}
			buffer_x_[0]=x_;
			buffer_dx_[0]=f_(t_,x_);
			dx_ = buffer_dx_[0];
		}
	}

	
};
