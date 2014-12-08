#include <boost/numeric/odeint.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/format.hpp>

using namespace boost::numeric::ublas;

typedef double value_type;
typedef value_type time_type;
typedef vector<value_type> state_type;
typedef state_type deriv_type;
typedef vector<deriv_type> buffer_type;

class abmStepper
{
private:
	int ord_;
	buffer_type buffer_;
	time_type t_;
	state_type x_;
	state_type dx_;
	

public:
	abmStepper() :
		ord_(1){};

	state_type f(time_type t, state_type x){
		value_type k = 100;
		x[0] = x[0];
		return( x ); 
	}

public:
	void setStates( time_type t, state_type x ){
		if ( t == t_ && x[0] == x_[0] )
			return;
		t_ = t;
		x_ = x;
		dx_ = f( t_, x_);
		buffer_.clear();
	}
	void getStates( time_type &t, state_type &x ){
		t = t_;
		x = x_;
	}

	void printStates(){
		std::cout << boost::format( "%-15E%-15E\n" ) % t_ % x_[0];
	}

	void printLabels(){
		std::cout << boost::format( "%-15s%-15s\n" ) % "time" % "state";
	}

	void rk4step( time_type h ){
		deriv_type k1 = dx_;
		deriv_type k2 = f ( t_ + h/2.0 , x_ + k1*h/2.0 );
		deriv_type k3 = f ( t_ + h/2.0 , x_ + k2*h/2.0 );
		deriv_type k4 = f ( t_ + h     , x_ + k3*h ); 
		x_ = x_ + h/6.0*( k1 + 2.0*k2 + 2.0*k3 + k4 );
		t_ = t_ + h;
	}

	void doStep(){
	}
};

int main(){
	abmStepper stepper;
	time_type t,t2 = 0;
	state_type x(1),x2(1);
	x[0]=3;
	stepper.printLabels();
	stepper.setStates(t,x);
	stepper.printStates();
	stepper.rk4step( 0.1 );
	stepper.printStates();
	stepper.rk4step( 0.1 );
	stepper.printStates();
	stepper.rk4step( 0.1 );
	stepper.printStates();

}
