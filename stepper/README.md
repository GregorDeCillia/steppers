## Base class for steppers

This bsase class defines functionalities all steppers have

### Constructor

``` cpp
stepper( int nStates, rhs_type f , int ord , string name )
```

### Virtual functions
- `doStep( h )` performs a step of size h

### Other functions
Name | Purpose
---- | -----
`getStates( t, x )` | passes the state of the stepper to the variables t and x
`printStates()` | prints the states to the console using `std::cout`
`setStates( t, x )` | set states of the stepper
`printLabels()` | Generates a row `t    x1    x2` wich fits the format of printStates
`getName()` | returns the name of the stepper as string