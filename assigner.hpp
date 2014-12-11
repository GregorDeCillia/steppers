//
//  Copyright (c) 2010
//  Nasos Iliopoulos
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASSIGNER_HPP
#define ASSIGNER_HPP
#include <boost/numeric/ublas/vector_expression.hpp>
#include <boost/numeric/ublas/matrix_expression.hpp>

namespace boost { namespace numeric { namespace ublas {

// Let's just hide the non_vector_tf as it will be accesible only through the free function non_vector
namespace {
    template <typename T>
    class non_vector_tf {
    public:
        non_vector_tf(T i): size_(i) {
        }
        T size() {
            return size_;
        }
    private:
        T size_;
    };
}

template <typename T>
non_vector_tf<T> non_vector(T i) {
    return non_vector_tf<T>(i);
}

template <class E>
class vector_expression_assigner {
public:
    typedef typename E::expression_type::value_type value_type;
    typedef typename E::expression_type::size_type size_type;

    vector_expression_assigner(E &e, value_type val):i(0), ve(e) {
        operator,(val);
    }

    template <class AE>
    vector_expression_assigner(E &e, const vector_expression<AE> &nve):i(0), ve(e) {
        operator,(nve);
    }

    template <typename T>
    vector_expression_assigner(E &e, non_vector_tf<T> nv):i(0), ve(e) {
        operator,(nv);
    }

    vector_expression_assigner &operator, (const value_type& val) {
        BOOST_UBLAS_CHECK(i<=ve().size(), bad_index());
        ve()(i++)=val;
        return *this;
    }
    
    template <typename T>
    vector_expression_assigner &operator, (non_vector_tf<T> nv) {
        i+=nv.size();
        return *this;
    }

    template <class AE>
    vector_expression_assigner &operator, (const vector_expression<AE> &nve) {
        for (typename AE::size_type k = 0; k!= nve().size(); k++)
            operator,(nve()(k));
        return *this;
    }
private:
    size_type i;
    E &ve;
};

template <class E>
vector_expression_assigner<vector_expression<E> > operator<<(vector_expression<E> &v, const typename E::value_type &val) {
    return vector_expression_assigner<vector_expression<E> >(v,val);
}

template <class E1, class E2>
vector_expression_assigner<vector_expression<E1> > operator<<(vector_expression<E1> &v, const vector_expression<E2> &ve) {
    return vector_expression_assigner<vector_expression<E1> >(v,ve);
}

template <class E, typename T>
vector_expression_assigner<vector_expression<E> > operator<<(vector_expression<E> &v, non_vector_tf<T> nv) {
    return vector_expression_assigner<vector_expression<E> >(v,nv);
}

template <class E>
class matrix_expression_assigner {
public:
    typedef typename E::expression_type::size_type size_type;

    matrix_expression_assigner(E &e, typename E::expression_type::value_type val):i(0), j(0), me(e) {
        operator,(val);
    }

     template <class AE>
    matrix_expression_assigner(E &e, const vector_expression<AE> &nve):i(0), j(0), me(e) {
        operator,(nve);
    }

    template <typename T>
    matrix_expression_assigner(E &e, non_vector_tf<T> nv):i(0), j(0), me(e) {
        operator,(nv);
    }

    matrix_expression_assigner &operator, (const typename E::expression_type::value_type& val) {
        if (j==me().size2()) {
            j=0;
            i++;
        }
        me()(i,j++) = val;
        return *this;
    }

    template <typename T>
    matrix_expression_assigner &operator, (non_vector_tf<T> nv) {
        size_type v = i*me().size2()+j+nv.size();
        i=v/me().size2();
        j=v-i*me().size2();
        return *this;
    }

    template <class AE>
    matrix_expression_assigner &operator, (const vector_expression<AE> &nve) {
        for (typename AE::size_type k = 0; k!= nve().size(); k++)
            operator,(nve()(k));
        return *this;
    }
private:
    size_type i;
    size_type j;
    E &me;
};

template <class E>
matrix_expression_assigner<matrix_expression<E> > operator<<(matrix_expression<E> &v, const typename E::value_type &val) {
    return matrix_expression_assigner<matrix_expression<E> >(v,val);
}

template <class E1, class E2>
matrix_expression_assigner<matrix_expression<E1> > operator<<(matrix_expression<E1> &v, const vector_expression<E2> &ve) {
    return matrix_expression_assigner<matrix_expression<E1> >(v,ve);
}

template <class E, typename T>
matrix_expression_assigner<matrix_expression<E> > operator<<(matrix_expression<E> &v, non_vector_tf<T> nv) {
    return matrix_expression_assigner<matrix_expression<E> >(v,nv);
}

} } }

#endif // ASSIGNER_HPP
