//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright

// quaternion.h - definition of the quaternion class
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
    _type& x()
    {
        return this->at(0);
    }

    const _type& x() const
    {
        return this->at(0);
    }

    _type& y()
    {
        return this->at(1);
    }

    const _type& y() const
    {
        return this->at(1);
    }

    _type& z()
    {
        return this->at(2);
    }

    const _type& z() const
    {
        return this->at(2);
    }

    _type& w()
    {
        return this->at(3);
    }

    const _type& w() const
    {
        return this->at(3);
    }
};

}
