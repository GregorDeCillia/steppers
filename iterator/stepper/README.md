## Base class for steppers

Defines basic funtionalities for steppers like getters/setters and memory management.

### Constructor

``` cpp
stepper( unsigned int nStates, rhs_type f , int ord , string name )
```

Argument | Meaning
---- | -----
`nStates` | dimension of the state space
`f`| rhs of the ode
`ord` | order of convergence for the program
`name` | name of the solver

### Virtual functions
Name | Purpose
--- | ----
`void doStep( h )` | performs a step of size h

### Other functions
Name | Purpose
---- | -----
`getStates( t, x )` | passes the state of the stepper to the variables `t` and `x`
`printStates()` | prints the states to the console using `std::cout << boost::format`
`setStates( t, x )` | update the states of the stepper
`printLabels()` | generates a row `t    x1    x2` wich fits the format of printStates
`getName()` | returns the name of the stepper as string
