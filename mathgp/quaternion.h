//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright
#pragma once

#include "ntuple.h"

namespace mathgp
{

template <typename _type>
class quaterniont : public _internal::ntuple<4, _type, quaterniont<_type>>
{
public:
    ////////////////////////////////////////////////////////
    // named constructors
    static quaterniont values(_type x, _type y, _type z, _type w)
    {
        quaterniont q;

        q.x() = x;
        q.y() = y;
        q.z() = z;
        q.w() = w;

        return q;
    }

    static quaterniont identity()
    {
        return values(0, 0, 0, 1);
    }

    ////////////////////////////////////////////////////////
    // access
    value_type& x()
    {
        return at(0);
    }

    const value_type& x() const
    {
        return at(0);
    }

    value_type& y()
    {
        return at(1);
    }

    const value_type& y() const
    {
        return at(1);
    }

    value_type& z()
    {
        return at(2);
    }

    const value_type& z() const
    {
        return at(2);
    }

    value_type& w()
    {
        return at(3);
    }

    const value_type& w() const
    {
        return at(3);
    }
};

}