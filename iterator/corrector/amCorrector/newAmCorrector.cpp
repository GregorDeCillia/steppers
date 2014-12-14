#include "amCorrector.cpp"

#include "am1Corrector.cpp"
#include "am2Corrector.cpp"
#include "am3Corrector.cpp"
#include "am4Corrector.cpp"
#include "am5Corrector.cpp"

static amCorrector* newAmCorrector( rhs_type f, int i  )
{
	switch ( i ){
	case 1: return new am1Corrector( f );
	case 2: return new am2Corrector( f );
	case 3: return new am3Corrector( f );
	case 4: return new am4Corrector( f );
	case 5: return new am5Corrector( f );
	}
}
