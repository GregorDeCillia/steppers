## Base class for Runge Kutta steppers

### Constructor
`rkStepper( nStates, f, name, butcher_size, ord )`

Argument | Meaning
---- | -----
`nStates` | dimension of the state space
`f`| rhs of the ode
`name` | name of the solver
`butcher_size` | size of the Butcher tableau
`ord` | order of convergence for the program

### Private Members
`matrix<value_type> A; vector<value_type> b;` Butcher tableau and weight vector of the RK-Method. It is assumed that these Members get declared in the constructor.