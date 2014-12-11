## Base class for steppers

This bsase class defines functionalities all steppers have

### Virtual functions
- `doStep( h )` performs a step of size h

### Other functions
- `getStates( t, x )`
- `printStates()`
- `setStates( t, x )`
- `printLabels()` Generates a row `t    x1    x2` wich fits the format of printStates
- `getName()`