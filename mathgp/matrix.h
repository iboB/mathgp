//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright
#pragma once

#include "ntuple.h"

namespace mathgp
{
namespace _internal
{

template <size_t _n, typename _type, typename _this_type>
class matrixnxnt : public ntuple<_n*_n, _type, _this_type>
{
public:
    static const size_type order = _n;

    typedef typename vector_space<order, _type>::vector order_vector;

    ////////////////////////////////////////////////////////
    // named constructors
    static _this_type identity()
    {
        _this_type ret = _this_type::zero();

        for(size_type i=0; i<order; ++i) 
            a(i, i) = value_type(1);

        return ret;
    }

    ////////////////////////////////////////////////////////
    // access
    value_type* column(size_type i)
    {
        return as_array() + i*order;
    }

    const value_type* column() const        
    {
        return as_array() + i*order;
    }

    value_type& m(size_type row, size_type column)
    {
        return this->column(column)[row];
    }

    const value_type& m(size_type row, size_type column) const
    {
        return this->column(column)[row];
    }
    
    value_type& operator()(size_type row, size_type column)
    {
        return m(row, column);
    }

    const value_type& operator()(size_type row, size_type column) const
    {
        return m(row, column);
    }

    order_vector& column_vector(size_type i)
    {
        return *reinterpret_cast<order_vector>(column(i));
    }

    template <size_type _dim>
    const order_vector& column_vector(size_type i) const
    {
        return *reinterpret_cast<order_vector>(column(i) + offset);
    }

    template <size_type _dim>
    typename vector_space<_dim, _type>::vector& column_vector(size_type i, size_t offset = 0)
    {
        return *reinterpret_cast<vector_space<_dim, _type>::vector*>(column(i) + offset);
    }

    template <size_type _dim>
    const typename vector_space<_dim, _type>::vector& column_vector(size_type i, size_t offset = 0) const
    {
        return *reinterpret_cast<const vector_space<_dim, _type>::vector*>(column(i) + offset);
    }

    ////////////////////////////////////////////////////////
    // functions

    value_type adjunct(size_type row, size_type col) const
    {
         return first_minor(row, col) * (((row+col)&1)?value_type(-1):value_type(1));
    }

    value_type first_minor(size_type row, size_type col) const
    {
        matrixnxnt<order-1, value_type> minor;

        for(size_type r=0; r<row; ++r)
        {
            for(size_type c=0; c<col; ++c)
                minor(r, c) = (*this)(r, c);

            for(size_type c=col+1; c<order; ++c)
                minor(r, c-1) = (*this)(r, c);
        }

        for(size_type r=row+1; r<order; ++r)
        {
            for(size_type c=0; c<col; ++c)
                minor(r-1, c) = (*this)(r, c);

            for(size_type c=col+1; c<order; ++c)
                minor(r-1, c-1) = (*this)(r, c);
        }

        return minor.determinant();
    }

    value_type determinant() const
    {
        return det_impl<order>::eval(*this);
    }


private:

    //_unused is a stupid gcc workaround
    //it doesn't allow fully specialized member types, or any specialization of methods
    //
    //update:
    //As http://tinyurl.com/bmaa9yh suggests, this is (unexplicably) fobidden by the standard.
    //One would wonder why this is so, considering that it works fine with msvc without the dummy type
    //and even as a specialized template method.
    template <size_type _order, typename _unused = int>
    struct det_impl
    {
        static value_type eval(const matrixnxnt<_order, value_type, _this_type>& m)
        {
            //laplace
            value_type det = 0;

            for(size_type i=0; i<_d; ++i)
            {
                det += m(0, i) * m.adjunct(0, i);
            }

            return det;
        }
    };

    template <typename _unused>
    struct det_impl<2, _unused>
    {
        static value_type eval(const matrixnxnt<2, value_type, _this_type>& m)
        {
            return m(0, 0)*m(1, 1) - m(0, 1)*m(1, 0);
        }
    };

};

} // namespace _internal


template <typename _type>
class matrix1x1t : public _internal::matrixnxnt<1, _type, matrix1x1t<_type>>
{
};

template <typename _type>
class matrix2x2t : public _internal::matrixnxnt<2, _type, matrix2x2t<_type>>
{
public:
    static matrix2x2t columns(
        float cr00, float cr01, //column 1
        float cr10, float cr11  //column 2
        )
    {
        matrix2x2t ret;
        ret(0, 0) = cr00; ret(1, 0) = cr01;
        ret(0, 1) = cr10; ret(1, 1) = cr11;
        return ret;
    }

    static matrix2x2t rows(
        float rc00, float rc01, //row 1
        float rc10, float rc11, //row 2
        )
    {
        matrix2x2t ret;
        ret(0, 0) = rc00; ret(1, 0) = rc10;
        ret(0, 1) = rc01; ret(1, 1) = rc11;
        return ret;
    }
};

template <typename _type>
class matrix3x3t : public _internal::matrixnxnt<3, _type, matrix3x3t<_type>>
{
public:
    static matrix3x3t columns(
        float cr00, float cr01, float cr02, //column 1
        float cr10, float cr11, float cr12, //column 2
        float cr20, float cr21, float cr22  //column 3
        )
    {
        matrix3x3t ret;
        ret(0, 0) = cr00; ret(1, 0) = cr01; ret(2, 0) = cr02;
        ret(0, 1) = cr10; ret(1, 1) = cr11; ret(2, 1) = cr12;
        ret(0, 2) = cr20; ret(1, 2) = cr21; ret(2, 2) = cr22;
        return ret;
    }

    static matrix3x3t rows(
        float rc00, float rc01, float rc02, //row 1
        float rc10, float rc11, float rc12, //row 2
        float rc20, float rc21, float rc22  //row 3
        )
    {
        matrix3x3t ret;
        ret(0, 0) = rc00; ret(1, 0) = rc10; ret(2, 0) = rc20;
        ret(0, 1) = rc01; ret(1, 1) = rc11; ret(2, 1) = rc21;
        ret(0, 2) = rc02; ret(1, 2) = rc12; ret(2, 2) = rc22;
        return ret;
    }
};

template <typename _type>
class matrix4x4t : public _internal::matrixnxnt<4, _type, matrix4x4t<_type>>
{
public:
    static matrix4x4t columns(
        float cr00, float cr01, float cr02, float cr03, //column 1
        float cr10, float cr11, float cr12, float cr13, //column 2
        float cr20, float cr21, float cr22, float cr23, //column 3
        float cr30, float cr31, float cr32, float cr33  //column 4
        )
    {
        matrix4x4t ret;
        ret(0, 0) = cr00; ret(1, 0) = cr01; ret(2, 0) = cr02; ret(3, 0) = cr03;
        ret(0, 1) = cr10; ret(1, 1) = cr11; ret(2, 1) = cr12; ret(3, 1) = cr13;
        ret(0, 2) = cr20; ret(1, 2) = cr21; ret(2, 2) = cr22; ret(3, 2) = cr23;
        ret(0, 3) = cr30; ret(1, 3) = cr31; ret(2, 3) = cr32; ret(3, 3) = cr33;
        return ret;
    }

    static matrix4x4t rows(
        float rc00, float rc01, float rc02, float rc03, //row 1
        float rc10, float rc11, float rc12, float rc13, //row 2
        float rc20, float rc21, float rc22, float rc23, //row 3
        float rc30, float rc31, float rc32, float rc33  //row 4
        )
    {
        matrix4x4t ret;
        ret(0, 0) = rc00; ret(1, 0) = rc10; ret(2, 0) = rc20; ret(3, 0) = rc30;
        ret(0, 1) = rc01; ret(1, 1) = rc11; ret(2, 1) = rc21; ret(3, 1) = rc31;
        ret(0, 2) = rc02; ret(1, 2) = rc12; ret(2, 2) = rc22; ret(3, 2) = rc32;
        ret(0, 3) = rc03; ret(1, 3) = rc13; ret(2, 3) = rc23; ret(3, 3) = rc33;
        return ret;
    }
};

} // namespace mathgp
