#pragma once

#include "rkStepperBase.h"

#include "ode12Stepper.cpp"
#include "ode23Stepper.cpp"
#include "ode34Stepper.cpp"
#include "ode45Stepper.cpp"
#include "fehlbergStepper.cpp"

rkStepper* newRkStepper( int nStates, rhs_type f, int i )
{
   switch( i ){
        case 1: return new ode12Stepper( nStates, f );
        case 2: return new ode23Stepper( nStates, f );
        case 3: return new ode34Stepper( nStates, f );
        case 4: return new ode45Stepper( nStates, f );
        case 5: return new fehlbergStepper( nStates, f );
        default:
           std::cout << "rk stepper of order " << i << " does not exist" << std::endl;
        }
}
