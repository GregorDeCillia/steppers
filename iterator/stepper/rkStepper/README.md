## Base class for Runge Kutta steppers

### Constructor

``` cpp
rkStepper( unsigned int nStates, rhs_type f, str name, int butcher_size, int ord )
```

Argument | Meaning
---- | -----
`nStates` | dimension of the state space
`f`| rhs of the ode
`name` | name of the solver
`butcher_size` | size of the Butcher tableau
`ord` | order of convergence for the program

### Members
Type| Name | Purpose
---- | ---- | ------
`matrix<value_type>` | `A` | Butcher Tableau
`vector<value_type>` | `b` | Weight Vetor
`int` | `butcher_size` | Size of the butcher tableau A
`void` | `calulateC()` | calculates a vector for the mehtod

It is assumed that `A` and `b` get declared in the constructor like so.

``` cpp
  ode45Stepper( unsigned int nStates , rhs_type f ) :
		rkStepper( nStates, f, "ode45", 3, 4 )
	{
          A << 0.5, 0.0, 0.0,
		       0.0, 0.5, 0.0,
			   0.0, 0.0, 1.0;

          b << 1.0/6.0, 1.0/3.0, 1.0/3.0, 1.0/6.0;

          //c << 0.5, 0.5, 1.0;
          calculateC();
	};
```
