## Base class for Runge Kutta steppers

### Constructor

``` cpp
rkStepper( unsigned int nStates, rhs_type f, string name, int ord,
            coefficient_vector b, 
            coefficient_matrix A
            )
```

Argument  | Meaning                                
--------- | ---------------------------------------
`nStates` | dimension of the state space
`f`       | rhs of the ode
`name`    | name of the solver
`ord`     | order of convergence for the program
`A`       | Butcher Tableau
`b`       | weight vector

### Members
Type   | Name           | Purpose
------ | -------------- | -----------------------------
`int`  | `butcher_size` | Size of the butcher tableau A
`void` | `calulateC()`  | calculates a vector for the mehtod
