//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright

// matrix.h - definition of the matrix classes
#pragma once

#include "functions.h"
#include "ntuple.h"
#include "vector.h"
#include <utility>

namespace mathgp
{

template <size_t _order, typename _type>
struct matrix_space
{
};

namespace _internal
{

template <size_t _n, typename _type, typename _this_type>
class matrixnxnt;

template <bool copy, size_t _order, typename _type, typename _this_type>
_this_type& matrixnxn_multiply(
    matrixnxnt<_order, _type, _this_type>& out_result,
    const matrixnxnt<_order, _type, _this_type>& a,
    const matrixnxnt<_order, _type, _this_type>& b);

template <size_t _n, typename _type, typename _this_type>
class matrixnxnt : public ntuple<_n*_n, _type, _this_type>
{
public:
    static const size_t order = _n;

    typedef typename vector_space<order, _type>::vector order_vector;

    ////////////////////////////////////////////////////////
    // named constructors
    static _this_type identity()
    {
        _this_type ret = _this_type::zero();

        for(size_t i=0; i<order; ++i)
            ret.m(i, i) = _type(1);

        return ret;
    }

    static _this_type scaling(const order_vector& scale)
    {
        _this_type ret = _this_type::zero();

        for(size_t i=0; i<order; ++i)
            ret.m(i, i) = scale.at(i);

        return ret;
    }

    ////////////////////////////////////////////////////////
    // access
    _type* column(size_t i)
    {
        return this->as_array() + i*order;
    }

    const _type* column(size_t i) const
    {
        return this->as_array() + i*order;
    }

    _type& m(size_t row, size_t column)
    {
        return this->column(column)[row];
    }

    const _type& m(size_t row, size_t column) const
    {
        return this->column(column)[row];
    }

    _type& operator()(size_t row, size_t column)
    {
        return m(row, column);
    }

    const _type& operator()(size_t row, size_t column) const
    {
        return m(row, column);
    }

    template <size_t _dim>
    typename vector_space<_dim, _type>::vector& column_vector(size_t col, size_t offset = 0)
    {
        return *reinterpret_cast<typename vector_space<_dim, _type>::vector*>(column(col) + offset);
    }

    template <size_t _dim>
    const typename vector_space<_dim, _type>::vector& column_vector(size_t col, size_t offset = 0) const
    {
        return *reinterpret_cast<const typename vector_space<_dim, _type>::vector*>(column(col) + offset);
    }

    order_vector& column_vector(size_t col)
    {
        return *reinterpret_cast<order_vector*>(column(col));
    }

    const order_vector& column_vector(size_t col) const
    {
        return *reinterpret_cast<order_vector*>(column(col));
    }

    order_vector row_vector(size_t row) const
    {
        order_vector vec;

        for(size_t col=0; col<order; ++col)
        {
            vec.at(col) = this->column(col)[row];
        }

        return vec;
    }

    template <size_t _dim>
    typename vector_space<_dim, _type>::vector& row_vector(size_t row, size_t offset) const
    {
        typename vector_space<_dim, _type>::vector vec;

        for(size_t col=offset; col<_dim; ++col)
        {
            vec.at(col) = this->column(col)[row];
        }

        return vec;
    }

    ////////////////////////////////////////////////////////
    // arithmetic
    _this_type& operator*=(const matrixnxnt& b)
    {
        return matrixnxn_multiply<true>(*this, *this, b);
    }

    ////////////////////////////////////////////////////////
    // functions
    _this_type& transpose()
    {
        for(size_t r=0; r<order; ++r)
            for(size_t c=0; c<order; ++c)
                std::swap(m(r, c), m(c, r));

        return this->as_this_type();
    }

    _type adjunct(size_t row, size_t col) const
    {
         return first_minor(row, col) * (((row+col)&1)?_type(-1):_type(1));
    }

    _type first_minor(size_t row, size_t col) const
    {
        typename matrix_space<order-1, _type>::matrix minor;

        for(size_t r=0; r<row; ++r)
        {
            for(size_t c=0; c<col; ++c)
                minor(r, c) = (*this)(r, c);

            for(size_t c=col+1; c<order; ++c)
                minor(r, c-1) = (*this)(r, c);
        }

        for(size_t r=row+1; r<order; ++r)
        {
            for(size_t c=0; c<col; ++c)
                minor(r-1, c) = (*this)(r, c);

            for(size_t c=col+1; c<order; ++c)
                minor(r-1, c-1) = (*this)(r, c);
        }

        return minor.determinant();
    }

    _type determinant() const
    {
        return det_impl<order>::eval(*this);
    }


private:
    // renamed template arguments, because they're shadowed otherwise;
    template <bool copy, size_t _o, typename _t, typename _tt>
    friend _tt& mathgp::_internal::matrixnxn_multiply(
        matrixnxnt<_o, _t, _tt>& out_result,
        const matrixnxnt<_o, _t, _tt>& a,
        const matrixnxnt<_o, _t, _tt>& b);

    //_unused is a stupid gcc workaround
    //it doesn't allow fully specialized member types, or any specialization of methods
    //
    //update:
    //As http://tinyurl.com/bmaa9yh suggests, this is (unexplicably) fobidden by the standard.
    //One would wonder why this is so, considering that it works fine with msvc without the dummy type
    //and even as a specialized template method.
    template <size_t _order, typename _unused = int>
    struct det_impl
    {
        static _type eval(const matrixnxnt<_order, _type, _this_type>& m)
        {
            //laplace
            _type det = 0;

            for(size_t i=0; i<_order; ++i)
            {
                det += m(0, i) * m.adjunct(0, i);
            }

            return det;
        }
    };

    template <typename _unused>
    struct det_impl<2, _unused>
    {
        static _type eval(const matrixnxnt<2, _type, _this_type>& m)
        {
            return m(0, 0)*m(1, 1) - m(0, 1)*m(1, 0);
        }
    };

};

template <size_t _order, typename _type, typename _this_type>
_this_type operator*(const matrixnxnt<_order, _type, _this_type>& a, const matrixnxnt<_order, _type, _this_type>& b)
{
    matrixnxnt<_order, _type, _this_type> result;

    return matrixnxn_multiply<false>(result, a, b);
}

template <bool copy, size_t _order, typename _type, typename _this_type>
_this_type& matrixnxn_multiply(
    matrixnxnt<_order, _type, _this_type>& out_result,
    const matrixnxnt<_order, _type, _this_type>& a,
    const matrixnxnt<_order, _type, _this_type>& b)
{
    matrixnxnt<_order, _type, _this_type> copy_matrix;
    matrixnxnt<_order, _type, _this_type>& result = copy ? copy_matrix : out_result;

    for(size_t i=0; i<_order; ++i)
    {
        for(size_t j=0; j<_order; ++j)
        {
            result(i, j) = 0;

            for(size_t k=0; k<_order; ++k)
            {
                result(i, j) += a(i, k) * b(k, j);
            }
        }
    }

    if(copy)
        out_result = copy_matrix;

    return result.as_this_type();
}

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
        _type cr00, _type cr01, //column 1
        _type cr10, _type cr11  //column 2
        )
    {
        matrix2x2t ret;
        ret(0, 0) = cr00; ret(1, 0) = cr01;
        ret(0, 1) = cr10; ret(1, 1) = cr11;
        return ret;
    }

    static matrix2x2t rows(
        _type rc00, _type rc01, //row 1
        _type rc10, _type rc11 //row 2
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
        _type cr00, _type cr01, _type cr02, //column 1
        _type cr10, _type cr11, _type cr12, //column 2
        _type cr20, _type cr21, _type cr22  //column 3
        )
    {
        matrix3x3t ret;
        ret(0, 0) = cr00; ret(1, 0) = cr01; ret(2, 0) = cr02;
        ret(0, 1) = cr10; ret(1, 1) = cr11; ret(2, 1) = cr12;
        ret(0, 2) = cr20; ret(1, 2) = cr21; ret(2, 2) = cr22;
        return ret;
    }

    static matrix3x3t rows(
        _type rc00, _type rc01, _type rc02, //row 1
        _type rc10, _type rc11, _type rc12, //row 2
        _type rc20, _type rc21, _type rc22  //row 3
        )
    {
        matrix3x3t ret;
        ret(0, 0) = rc00; ret(1, 0) = rc10; ret(2, 0) = rc20;
        ret(0, 1) = rc01; ret(1, 1) = rc11; ret(2, 1) = rc21;
        ret(0, 2) = rc02; ret(1, 2) = rc12; ret(2, 2) = rc22;
        return ret;
    }

    ////////////////////////////////////////////////////////
    // transforms
    static matrix3x3t rotation_axis(const vector3t<_type>& axis, _type radians)
    {
        const vector3t<_type> naxis = normalized(axis);

        const _type c = std::cos(radians);
        const _type s = std::sin(radians);
        const _type c1 = 1 - c;
        const _type x = naxis.x();
        const _type y = naxis.y();
        const _type z = naxis.z();

        return matrix3x3t::rows(
            c + c1*sq(x),   c1*y*x - s*z,   c1*z*x + s*y,
            c1*x*y + s*z,   c + c1*sq(y),   c1*z*y - s*x,
            c1*x*z - s*y,   c1*y*z + s*x,   c + c1*sq(z)
        );
    }

    static matrix3x3t rotation_x(_type xradians)
    {
        const _type c = std::cos(xradians);
        const _type s = std::sin(xradians);

        return matrix3x3t::rows(
            1,  0,  0,
            0,  c,  -s,
            0,  s,  c
        );
    }

    static matrix3x3t rotation_y(_type yradians)
    {
        const _type c = std::cos(yradians);
        const _type s = std::sin(yradians);

        return matrix3x3t::rows(
            c,  0,  s,
            0,  1,  0,
            -s, 0,  c
        );
    }

    static matrix3x3t rotation_z(_type zradians)
    {
        const _type c = std::cos(zradians);
        const _type s = std::sin(zradians);

        return matrix3x3t::rows(
            c,  -s,  0,
            s,  c,   0,
            0,  0,   1
        );
    }

    static matrix3x3t rotation_yaw_pitch_roll(_type yaw, _type pitch, _type roll)
    {
        const _type cy = std::cos(yaw);
        const _type sy = std::sin(yaw);
        const _type cx = std::cos(pitch);
        const _type sx = std::sin(pitch);
        const _type cz = std::cos(roll);
        const _type sz = std::sin(roll);

        return matrix3x3t::rows(
            cz*cy + sz*sx*sy,  -sz*cy + cz*sx*sy, cx*sy,
            sz*cx,             cz*cx,             -sx,
            -cz*sy + sz*sx*cy, sz*sy + cz*sx*cy,  cx*cy
        );
    }

    static matrix3x3t rotation_vectors(const vector3t<_type>& src, const vector3t<_type>& target)
    {
        return _internal::rotation_from_vectors<matrix3x3t>(src, target);
    }
};

template <typename _type>
class matrix4x4t : public _internal::matrixnxnt<4, _type, matrix4x4t<_type>>
{
    typedef _internal::matrixnxnt<4, _type, matrix4x4t<_type>> parent;
public:
    static matrix4x4t columns(
        _type cr00, _type cr01, _type cr02, _type cr03, //column 1
        _type cr10, _type cr11, _type cr12, _type cr13, //column 2
        _type cr20, _type cr21, _type cr22, _type cr23, //column 3
        _type cr30, _type cr31, _type cr32, _type cr33  //column 4
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
        _type rc00, _type rc01, _type rc02, _type rc03, //row 1
        _type rc10, _type rc11, _type rc12, _type rc13, //row 2
        _type rc20, _type rc21, _type rc22, _type rc23, //row 3
        _type rc30, _type rc31, _type rc32, _type rc33  //row 4
        )
    {
        matrix4x4t ret;
        ret(0, 0) = rc00; ret(1, 0) = rc10; ret(2, 0) = rc20; ret(3, 0) = rc30;
        ret(0, 1) = rc01; ret(1, 1) = rc11; ret(2, 1) = rc21; ret(3, 1) = rc31;
        ret(0, 2) = rc02; ret(1, 2) = rc12; ret(2, 2) = rc22; ret(3, 2) = rc32;
        ret(0, 3) = rc03; ret(1, 3) = rc13; ret(2, 3) = rc23; ret(3, 3) = rc33;
        return ret;
    }

    static matrix4x4t from3x3(const matrix3x3t<_type>& m)
    {
        return matrix4x4t::columns(
            m(0, 0), m(1, 0), m(2, 0), 0,
            m(0, 1), m(1, 1), m(2, 1), 0,
            m(0, 2), m(1, 2), m(2, 2), 0,
            0,       0,       0,       1
        );
    }

    ////////////////////////////////////////////////////////
    // projection
    static matrix4x4t ortho_lh(_type width, _type height, _type near_dist, _type far_dist)
    {
        _type depth = far_dist - near_dist;
        return matrix4x4t::rows(
            2/width, 0,        0,          0,
            0,       2/height, 0,          0,
            0,       0,        1/depth,   -1/depth,
            0,       0,        0,          1);
    }

    static matrix4x4t ortho_rh(_type width, _type height, _type near_dist, _type far_dist)
    {
        return ortho_lh(width, height, near_dist, far_dist).change_handedness();
    }

    // off center
    static matrix4x4t ortho_lh(_type left, _type right, _type bottom, _type top, _type near_dist, _type far_dist)
    {
        _type width = right - left;
        _type height = top - bottom;

        matrix4x4t ret = ortho_lh(width, height, near_dist, far_dist);

        ret(0, 3) = -(left + right)/width;
        ret(1, 3) = -(top + bottom)/height;

        return ret;
    }

    static matrix4x4t ortho_rh(_type left, _type right, _type bottom, _type top, _type near_dist, _type far_dist)
    {
        return ortho_lh(left, right, bottom, top, near_dist, far_dist).change_handedness();
    }

    static matrix4x4t perspective_lh(_type width, _type height, _type near_dist, _type far_dist)
    {
        _type depth = far_dist - near_dist;
        return matrix4x4t::rows(
            (2*near_dist)/width, 0,             0,          0,
            0,            (2*near_dist)/height, 0,          0,
            0,            0,               far_dist/depth, -(far_dist*near_dist)/depth,
            0,            0,               1,          0);
    }

    static matrix4x4t perspective_rh(_type width, _type height, _type near_dist, _type far_dist)
    {
        return perspective_lh(width, height, near_dist, far_dist).change_handedness();
    }

    // off center
    static matrix4x4t perspective_lh(_type left, _type right, _type bottom, _type top, _type near_dist, _type far_dist)
    {
        _type width = right - left;
        _type height = top - bottom;

        matrix4x4t ret = perspective_lh(width, height, near_dist, far_dist);

        ret(0, 3) = -(left + right)/width;
        ret(1, 3) = -(top + bottom)/height;

        return ret;
    }

    static matrix4x4t perspective_rh(_type left, _type right, _type bottom, _type top, _type near_dist, _type far_dist)
    {
        return perspective_lh(left, right, bottom, top, near_dist, far_dist).change_handedness();
    }

    static matrix4x4t perspective_fov_lh(_type fovy, _type aspect, _type near_dist, _type far_dist)
    {
        _type yscale = _type(1)/std::tan(fovy/2); //cot(fovy/2)
		_type xscale = yscale/aspect;
        _type depth = far_dist - near_dist;

        return matrix4x4t::rows(
            xscale, 0,      0,          0,
            0,      yscale, 0,          0,
            0,      0,      far_dist/depth, -(far_dist*near_dist)/depth,
            0,      0,      1,          0);
    }

    static matrix4x4t perspective_fov_rh(_type fovy, _type aspect, _type near_dist, _type far_dist)
    {
        return perspective_fov_lh(fovy, aspect, near_dist, far_dist).change_handedness();
    }

    ////////////////////////////////////////////////////////
    // view
    static matrix4x4t look_towards(const vector3t<_type>& eye, const vector3t<_type>& dir, const vector3t<_type>& up)
    {
        vector3t<_type> front = normalized(dir);
        vector3t<_type> right = normalized(cross(up, front));
        vector3t<_type> up2 = cross(front, right); //since the original up is not to be trusted

        vector3t<_type> shift = vector3t<_type>::coord(
            -dot(right, eye),
            -dot(up2, eye),
            -dot(front, eye)
        );

        return basis_transform(shift, right, up2, front);
    }

    //static matrix4x4t look_towards_rh(const vector3t<_type>& eye, const vector3t<_type>& dir, const vector3t<_type>& up)
    //{
    //    matrix4x4t ret = look_towards_lh(eye, dir, up);
    //    flip_sign(ret.template column_vector<3>(3));
    //    return ret;
    //}

    static matrix4x4t look_at_lh(const vector3t<_type>& eye, const vector3t<_type>& at, const vector3t<_type>& up)
    {
        return look_towards(eye, at-eye, up);
    }

    static matrix4x4t look_at_rh(const vector3t<_type>& eye, const vector3t<_type>& at, const vector3t<_type>& up)
    {
        return look_towards(eye, eye-at, up);
    }

    ////////////////////////////////////////////////////////
    // transforms
    static matrix4x4t basis_transform(const vector3t<_type>& o, const vector3t<_type>& e1, const vector3t<_type>& e2, const vector3t<_type>& e3)
    {
        return matrix4x4t::rows(
            e1.x(), e1.y(), e1.z(), o.x(),
            e2.x(), e2.y(), e2.z(), o.y(),
            e3.x(), e3.y(), e3.z(), o.z(),
            0,      0,      0,      1
        );
    }

    static matrix4x4t translation(const vector3t<_type>& pos)
    {
        matrix4x4t ret = parent::identity();

        ret.modify_translation() = pos;

        return ret;
    }

    static matrix4x4t translation(_type x, _type y, _type z)
    {
        return translation(v(x, y, z));
    }

    static matrix4x4t scaling(_type sx, _type sy, _type sz)
    {
        return from3x3(matrix3x3t<_type>::scaling(scale));
    }

    static matrix4x4t scaling(const vector3t<_type>& scale)
    {
        return scaling(scale.x(), scale.y(), scale.z());
    }

    static matrix4x4t scaling_uniform(_type s)
    {
        return scaling(s, s, s);
    }

    static matrix4x4t rotation_axis(const vector3t<_type>& axis, _type radians)
    {
        return from3x3(matrix3x3t<_type>::rotation_axis(axis, radians));
    }

    static matrix4x4t rotation_x(_type xradians)
    {
        return from3x3(matrix3x3t<_type>::rotation_x(xradians));
    }

    static matrix4x4t rotation_y(_type yradians)
    {
        return from3x3(matrix3x3t<_type>::rotation_y(yradians));
    }

    static matrix4x4t rotation_z(_type zradians)
    {
        return from3x3(matrix3x3t<_type>::rotation_z(zradians));
    }

    static matrix4x4t rotation_yaw_pitch_roll(_type yaw, _type pitch, _type roll)
    {
        return from3x3(matrix3x3t<_type>::rotation_yaw_pitch_roll(yaw, pitch, roll));
    }

    static matrix4x4t rotation_vectors(const vector3t<_type>& src, const vector3t<_type>& target)
    {
        return from3x3(matrix3x3t<_type>::rotation_vectors(src, target));
    }

    ////////////////////////////////////////////////////////
    // functions

    vector3t<_type>& modify_translation()
    {
        return this->template column_vector<3>(3);
    }

protected:

    matrix4x4t& change_handedness()
    {
        flip_sign(this->column_vector(2));
        return *this;
    }
};

template <typename _type>
struct matrix_space<1,  _type>
{
    typedef matrix1x1t<_type> matrix;
};

template <typename _type>
struct matrix_space<2, _type>
{
    typedef matrix2x2t<_type> matrix;
};

template <typename _type>
struct matrix_space<3, _type>
{
    typedef matrix3x3t<_type> matrix;
};

template <typename _type>
struct matrix_space<4, _type>
{
    typedef matrix4x4t<_type> matrix;
};

} // namespace mathgp
