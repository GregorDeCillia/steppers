## Base class for correctors

### Constructor

```cpp
corrector( rhs_type f, string name, int ord )
```

Argument | Meaning
---- | -----
`f`| rhs of the ode
`name` | name of the solver
`ord` | order of convergence for the program

### Pure virtual functions

```cpp
virtual void correct( time_type &t, state_type &x, 
                      time_type h, buffer_type buffer_x, 
                      buffer_type buffer_dx 
                      )
``` 