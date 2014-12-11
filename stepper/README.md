## Base class for steppers

This bsase class defines functionalities all steppers have

### Virtual functions
- `clearBuffers()` Gets tiggered whenever the states change. This function is trivial for single step methods
- `doStep( h )` performs a step of size h

### Other functions
- `getStates( t, x )`
- `printStates()`
- `setStates( t, x )`
- `printLabels()` Generates a row `t    x1    x2` wich fits the format of printStates