//
// gd-proto
// Copyright (c) 2015 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// http://opensource.org/licenses/MIT
//
// MSVC doesn't support a the high resolution timer from chrono
// (well it does, but it's "high" resolution is about a millisecond)
// Thus we're forced to use this silly class when we're on msvc
#pragma once

#include <chrono>

namespace gdproto
{
#if defined(_MSC_VER)
    struct high_res_clock
    {
        typedef long long rep;
        typedef std::nano period;
        typedef std::chrono::duration<rep, period> duration;
        typedef std::chrono::time_point<high_res_clock> time_point;
        static const bool is_steady = true;

        static time_point now();
    };
#else
    typedef std::chrono::high_resolution_clock high_res_clock;
#endif
}