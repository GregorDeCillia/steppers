#pragma once

#include <iostream>
#include <boost/numeric/ublas/vector.hpp>
#include <string>

using namespace boost::numeric::ublas;

typedef double value_type;
typedef value_type time_type;
typedef vector<value_type> state_type;
typedef state_type deriv_type;
typedef vector<deriv_type> buffer_type;

typedef state_type (*rhs_type) (time_type , state_type);
typedef std::string string;

typedef std::vector<double> coefficient_vector;
typedef std::vector<std::vector<double> > coefficient_matrix;
