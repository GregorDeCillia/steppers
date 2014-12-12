## Base class for predictors

### Constructor

```cpp
predictor( rhs_type f, string name, int ord )
```

Argument | Meaning
---- | -----
`f`| rhs of the ode
`name` | name of the solver
`ord` | order of convergence for the program

### Pure virtual functions

```cpp
virtual void predict( time_type &t, state_type &x, 
                      time_type h, buffer_type buffer_x, 
                      buffer_type buffer_dx 
                      )
``` 