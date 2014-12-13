#pragma once

#include <initializer_list>
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

unbounded_array<value_type> makeVector(std::initializer_list<value_type> list) {
    unbounded_array<value_type> result(list.size());
    for(unsigned i = 0; i < list.size(); ++ i)
        result[i] = *(list.begin() + i);
    return result;
}
