#pragma once

#include "../../../include/assigner.hpp"
#include "rkStepperBase.h"

/// an alternative to the "classic" rk4 method with the same order.
class threeEightStepper: public rkStepper
{
	/**
        \f[
            \begin{array}{r|rrr}
	              0                        \\
	            1/3 & 1/3 &                \\
				2/3 &-1/3 &  1             \\
				  1 &   1 & -1  & 1.0      \\ 
				  \hline
                    & 1/8 & 3/8 & 3/8 & 1/8 
			\end{array}		  
       \f]
	 **/


public:
	threeEightStepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "3/8rule", 4,
		           { 1.0/8.0, 3.0/8.0, 3.0/8.0, 1.0/8.0 },
		           {  {  1.0/3.0,  0.0, 0.0 },
				      { -1.0/3.0,  1.0, 0.0 },
					  { 1.0     , -1.0, 1.0 }  }
		           )
	{};
};
