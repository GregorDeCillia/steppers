#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"



/**
   Creates the classical runge kuta scheme. The tableau is
   \f[
   \begin{array}{r|rrrrrr}
       0                                                                    \\
     1/4 &       1/4                                                        \\
     3/8 &      3/32 &       9/32                                           \\
   12/13 & 1932/2197 & -7200/2197 &  7296/2197                              \\ 
       1 &   439/216 &         -8 &   3680/513 &   -485/4104                \\
     1/2 &     -8/27 &          2 & -3544/2565 &   1859/4104 & -11/40       \\
   \hline
	     &    16/135 &          0 & 6656/12825 & 28561/56430 &  -9/50 & 2/55
   \end{array}	   
   \f]
**/


/// the 5t order part of the [fehlberg RK method](https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta%E2%80%93Fehlberg_method)
class fehlbergStepper: public rkStepper
{

public:
	fehlbergStepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "fe", 5 ,
		             {16.0/135.0, 0.0,  6656.1/12825.0, 28561.0/56430.0,      -9.0/50.0,   2.0/55.0 },
		           { {          0.25 ,            0.0 ,            0.0 ,           0.0 ,        0.0 },
		             {      3.0/32.0 ,       9.0/32.0 ,            0.0 ,           0.0 ,        0.0 },
		             { 1932.0/2197.0 , -7200.0/2197.0 ,  7296.0/2197.0 ,           0.0 ,        0.0 },
		             {   439.0/216.0 ,           -8.0 ,   3680.0/513.0 , -845.0/4104.0 ,        0.0 },
		             {     -8.0/27.0 ,            2.0 , -3544.0/2565.0 , 1859.0/4104.0 , -11.0/40.0 }  } 
		           )
	{};
};
