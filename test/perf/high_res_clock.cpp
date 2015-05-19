//
// gd-proto
// Copyright (c) 2015 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// http://opensource.org/licenses/MIT
//
#include "high_res_clock.h"

#if defined(_MSC_VER)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace gdproto
{
    const long long FREQ = []() -> long long
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return frequency.QuadPart;
    }();

    high_res_clock::time_point high_res_clock::now()
    {
        LARGE_INTEGER t;
        QueryPerformanceCounter(&t);
        return time_point(duration((t.QuadPart * rep(period::den))/FREQ));
    }
}

#endif