## Base class for Linear Multistep Methods

### Constructor

``` cpp
multiStepper( unsigned int nStates, int ord, rhs_type f, int nCorrSteps, string name )
```

Agrument | Meaning
-------- | ---------
`nStates`  | dimension of the state space
`ord`      | order of the mehtod
`f`        | rhs of the ODE
`nCorrSteps` | number of corrector steps
`name` | Name of the Stepper

### Virtual Funtions
Name | Function
---- | -----
`void predictor()` | the explicit part of the multistep method.
`void corrector()` | a corrector method. This function is trivial for explicit steppers


### Private Members

Member | Function
------ | --------
`buffer_type buffer_x_, buffer_dx_` | contains previous evaluations of state values and derivatives. It is assumed that the buffer size is equal to the order of the program.
`int buffer_index_` | how much of the buffer is already generated?
`int nCorrSteps` | number of corretor steps
`rk4Stepper singleStepper_` | if `buffer_index_ < buffer_size_`, the integration has to be done with a single step method.
