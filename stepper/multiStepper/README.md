## Base class for Linear Multistep Methods

### Constructor

``` cpp
multiStepper( unsigned int nStates, int ord, rhs_type f, int nCorrSteps, string name )

```

### Private Members

Member | Function
------ | --------
`buffer_type buffer_x_, buffer_dx_` | contains previous evaluations of state values and derivatives. It is assumed that the buffer size is equal to the order of the program.
`int buffer_index_` | how much of the buffer is already generated?
`int nCorrSteps` | number of corretor steps
`rk4Stepper singleStepper_` | if `buffer_index_ < buffer_size_`, the integration has to be done with a single step method.
`void predictor(), corrector()` | the main parts of the predictor corrector method.
