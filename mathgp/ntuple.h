//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright
#pragma once

#include "defines.h"

namespace mathgp
{

namespace _internal
{

template <size_t _n, typename _type, typename _this_type>
class ntuple
{
public:
    typedef _type value_type;
    typedef size_t size_type;

    static const size_type value_count = _n;

    typedef void mathgp_type; // for sfinae

    ////////////////////////////////////////////////////////
    // named constructors
    static _this_type copy(value_type scalar)
    {
        _this_type ret;

        //could use memset, but it's probably slower...
        //"for" should be optimized at compile time.
        for(size_type i=0; i<value_count; ++i)
        {
            ret.at(i) = scalar;
        }

        return ret;
    }

    static _this_type zero()
    {
        return copy(value_type(0));
    }

    static _this_type from_ptr(const value_type* ptr)
    {
        _this_type ret;

        //could use memcpy, but it's probably slower...
        //for should be optimized at compile time.        
        MATHGP_EACH_OF(ret) = ptr[i];
        
        return ret;
    }

    ////////////////////////////////////////////////////////
    // attach

    static _this_type& attach_to_ptr(value_type* ptr)
    {
        return *reinterpret_cast<_this_type*>(ptr);
    }

    static const _this_type& attach_to_ptr(const value_type* ptr)
    {
        return *reinterpret_cast<const _this_type*>(ptr);
    }

    static _this_type* attach_to_array(value_type* ar)
    {
        return reinterpret_cast<_this_type*>(ar);
    }

    static const _this_type* attach_to_array(const value_type* ar)
    {
        return reinterpret_cast<const _this_type*>(ar);
    }

    ////////////////////////////////////////////////////////
    // access

    value_type* as_array()
    {
        return values;
    }

    const value_type* as_array() const
    {
        return values;
    }

    value_type& at(size_type i)
    {
        return values[i];
    }

    const value_type& at(size_type i) const
    {
        return values[i];
    }

    value_type& operator[](size_type i)
    {
        return at(i);
    }

    const value_type& operator[](size_type i) const
    {
        return at(i);
    }

    ////////////////////////////////////////////////////////
    // std

    typedef value_type* iterator;
    typedef const value_type* const_iterator;

    iterator* begin()
    {
        return as_array();
    }

    iterator* end()
    {
        return as_array() + value_count;
    }

    const_iterator* begin() const
    {
        return as_array();
    }

    const_iterator* end() const
    {
        return as_array() + value_count;
    }

    ////////////////////////////////////////////////////////
    // arithmetic

    const _this_type& operator+() const
    {
        return as_this_type();
    }

    _this_type operator-() const
    {
        _this_type ret;

        MATHGP_EACH_VAL = -at(i);

        return ret;
    }

    _this_type& operator+=(const _this_type& b)
    {
        MATHGP_EACH_VAL += b.at(i);

        return as_this_type();
    }

    _this_type& operator-=(const _this_type& b)
    {
        MATHGP_EACH_VAL -= b.at(i);

        return as_this_type();
    }

    _this_type& operator*=(const value_type& scalar)
    {
        MATHGP_EACH_VAL *= scalar;

        return as_this_type();
    }

    _this_type& operator/=(const value_type& scalar)
    {
        MATHGP_EACH_VAL /= scalar;

        return as_this_type();
    }

protected:
    value_type values[value_count];

    _this_type& as_this_type()
    {
        return *reinterpret_cast<_this_type*>(this);
    }

    const _this_type& as_this_type() const
    {
        return *reinterpret_cast<const _this_type*>(this);
    }

    ntuple() {};
};

template <size_t _n, typename _type, typename _this_type>
_this_type operator+(const ntuple<_n, _type, _this_type>& a,
                     const ntuple<_n, _type, _this_type>& b)
{
    _this_type ret;

    MATHGP_EACH_OF(ret) = a.at(i) + b.at(i);

    return ret;
}

template <size_t _n, typename _type, typename _this_type>
_this_type operator-(const ntuple<_n, _type, _this_type>& a,
                     const ntuple<_n, _type, _this_type>& b)
{
    _this_type ret;

    MATHGP_EACH_OF(ret) = a.at(i) - b.at(i);

    return ret;
}

template <size_t _n, typename _type, typename _this_type>
_this_type operator*(const ntuple<_n, _type, _this_type>& a,
                     const _type& scalar)
{
    _this_type ret;

    MATHGP_EACH_OF(ret) = a.at(i) * scalar;

    return ret;
}

template <size_t _n, typename _type, typename _this_type>
_this_type operator*(const _type& scalar,
                     const ntuple<_n, _type, _this_type>& b)
{
    _this_type ret;

    MATHGP_EACH_OF(ret) = scalar * a.at(i);

    return ret;
}

template <size_t _n, typename _type, typename _this_type>
_this_type operator/(const ntuple<_n, _type, _this_type>& a,
                     const _type& scalar)
{
    _this_type ret;

    MATHGP_EACH_OF(ret) = a.at(i) / scalar;

    return ret;
}

template <size_t _n, typename _type, typename _this_type>
bool operator==(const ntuple<_n, _type, _this_type>& a,
                const ntuple<_n, _type, _this_type>& b)
{
    for(size_t i=0; i<_this_type::value_count; ++i)
    {
        if(a.at(i) != b.at(i))
            return false;
    }

    return true;
}

template <size_t _n, typename _type, typename _this_type>
bool operator!=(const ntuple<_n, _type, _this_type>& a,
                const ntuple<_n, _type, _this_type>& b)
{
    return !operator==(a, b);
}

template <size_t _n, typename _type, typename _this_type>
_this_type rcp(const _type& scalar,
               const ntuple<_n, _type, _this_type>& b)
{
    _this_type ret;

    MATHGP_EACH_OF(ret) = scalar / b.at(i);

    return ret;
}

template <size_t _n, typename _type, typename _this_type>
_this_type abs(const ntuple<_n, _type, _this_type>& a)
{
    _this_type ret;

    MATHGP_EACH_OF(ret) = std::abs(a.at(i));

    return ret;
}

} // namespace _internal

} // namespace mathgp


