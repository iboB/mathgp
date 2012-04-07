//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright
#pragma once

namespace mathgp
{

template <typename _type>
_type sq(const _type& a)
{
    return a*a;
}

template <typename _type>
void flip_sign(_type& a)
{
    a = -a;
}

template <typename _type, typename _scalar>
inline _type lerp(const _type& from, const _type& to, const _scalar ratio)
{
    return from + ratio * (to - from);
}

} // namespace mathgp
