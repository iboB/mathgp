//                MathGP Library
//  Copyright (c) 2012-2016 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright
#include "mathgp_test.h"

using namespace mathgp;

class nrvo_test
{
public:
    static size_t copies;

    nrvo_test(int d) 
        : dummy(d)
    {}

    nrvo_test(const nrvo_test& b)
        : dummy(b.dummy)
    {
        ++copies;
    }

    int dummy;

    static nrvo_test seven()
    {
        return nrvo_test(7);
    }
};

size_t nrvo_test::copies = 0;

TESTCASE("nrvo")
{
    nrvo_test t = nrvo_test::seven();
    
    if (nrvo_test::copies != 0)
    {
        puts("WARNING: This build configuration (or your compiler) doesn't support named return "
        "value optimizations. MathGP will suffer big performance penalties because "
        "of that");
    }
}

TESTCASE("mclose")
{
    float a = 10;
    CHECK(close(a, a, constants<float>::EPSILON_HIGH()));

    float b = a - constants<float>::EPSILON();

    CHECK(close(a, b, constants<float>::EPSILON_LOW()));
    CHECK(close(b, a, constants<float>::EPSILON_LOW()));
}

TESTCASE("funcs")
{
    CHECK(sq(5) == 25);
    CHECK(sq(8.f) == 64.f);

    int n = 5;
    flip_sign(n);
    CHECK(n == -5);

    float f = 11;
    flip_sign(f);
    CHECK(f == -11.f);

    CHECK(close(lerp(4.f, 7.f, 0.3333333f), 5.f, constants<float>::EPSILON()));

    CHECK(close(rad_to_deg(constants<float>::PI_HALF()), 90.f, constants<float>::EPSILON()));
    CHECK(close(deg_to_rad(90.f), constants<float>::PI_HALF(), constants<float>::EPSILON()));

    CHECK(close(round(4.5), 5., constants<double>::EPSILON()));
    CHECK(close(round(2.3), 2., constants<double>::EPSILON()));
    CHECK(close(round(11.83), 12., constants<double>::EPSILON()));

    CHECK(clamp(1, 2, 3) == 2);
    CHECK(clamp(11, 2, 3) == 3);
    CHECK(clamp(3, 2, 5) == 3);
}
