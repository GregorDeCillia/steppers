## Base class for iterators

Defines basic operations for steppers, predictors and correctors.

### Constructor

``` cpp
iterator( rhs_type f, string name, int ord )
```

Argument | Meaning
---- | -----
`f`| rhs of the ode
`name` | name of the solver
`ord` | order of convergence for the program. More precisely: the [global truncation error](https://en.wikipedia.org/wiki/Truncation_error_%28numerical_integration%29#Global_truncation_error)

### Public functions
Name | Purpose
---- | -----
`virtual void setRHS( rhs_type f )` | updates the RHS function.
`string getName()` | get `iterator::name_`
`int getOrder()` | get `iterator::ord_`

