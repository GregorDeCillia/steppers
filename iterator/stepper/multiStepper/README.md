## Base class for Linear Multistep Methods

### Constructor

``` cpp
multiStepper( unsigned int nStates, int ord, rhs_type f, 
              int nCorrSteps, string name ,
              predictor* predictor,
              corrector* corrector,
              rkStepper* singleStepper)
```

Agrument | Meaning
-------- | ---------
`nStates`  | dimension of the state space
`ord`      | order of the mehtod
`f`        | rhs of the ODE
`nCorrSteps` | number of corrector steps
`name` | Name of the Stepper
`predictor` | predictor method
`corrector` | corrector method
`rkStepper` | singlestepper used to inititialize the buffer 

### Public Funtions
Name | Function
---- | -----
`void printBuffer()` | Prints buffer to the screen. Similar to `stepper::printStates()`.
`void setStates()` | set `states_`
`void setRHS()`  | set `f_`
`void doStep` | If the buffer is not filled, call the `rkStepper`. Otherwise, call the `predictor` and then the `corrector`

### Private Members

Member | Function
------ | --------
`buffer_type buffer_x_, buffer_dx_` | contains previous evaluations of state values and derivatives. It is assumed that the buffer size is equal to the order of the program.
`int buffer_index_` | how much of the buffer is already generated?
`int nCorrSteps` | number of corretor steps
`predictor* predictor_` | the Predictor
`corrector* corrector_` | the Corrector
`rkStepper* singleStepper_` | the SingleStepper
`void clearBuffers()` | Is called whenever the rhs or the state changes. This indicates that the `rkStepper` has to be used again for the net calls of `doStep()`.
