//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright

#include "precompiled.h"

using namespace boost::unit_test;
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

size_t nrvo_test::copies;

void nrvo()
{
    nrvo_test t = nrvo_test::seven();
    
    BOOST_WARN_MESSAGE(nrvo_test::copies == 0, 
        "This build configuration (or your compiler) doesn't support named return "
        "value optimizations. MathGP will suffer big performance penalties because "
        "of that");
}

void mclose()
{
    float a = 10;
    BOOST_CHECK(close(a, a, constants<float>::EPSILON_HIGH()));

    float b = a - constants<float>::EPSILON();

    BOOST_CHECK(close(a, b, constants<float>::EPSILON_LOW()));
    BOOST_CHECK(close(b, a, constants<float>::EPSILON_LOW()));
}

void funcs()
{
    BOOST_CHECK_EQUAL(sq(5), 25);
    BOOST_CHECK_EQUAL(sq(8.f), 64.f);

    int n = 5;
    flip_sign(n);
    BOOST_CHECK_EQUAL(n, -5);

    float f = 11;
    flip_sign(f);
    BOOST_CHECK_EQUAL(f, -11.f);

    BOOST_CHECK_CLOSE(lerp(4.f, 7.f, 0.3333333f), 5.f, constants<float>::EPSILON());

    BOOST_CHECK_CLOSE(rad_to_deg(constants<float>::PI_HALF()), 90.f, constants<float>::EPSILON());
    BOOST_CHECK_CLOSE(deg_to_rad(90.f), constants<float>::PI_HALF(), constants<float>::EPSILON());

    BOOST_CHECK_CLOSE(round(4.5), 5., constants<double>::EPSILON());
    BOOST_CHECK_CLOSE(round(2.3), 2., constants<double>::EPSILON());
    BOOST_CHECK_CLOSE(round(11.83), 12., constants<double>::EPSILON());

    BOOST_CHECK_EQUAL(clamp(1, 2, 3), 2);
    BOOST_CHECK_EQUAL(clamp(11, 2, 3), 3);
    BOOST_CHECK_EQUAL(clamp(3, 2, 5), 3);
}

test_suite* prerequisites()
{
    test_suite* suite = BOOST_TEST_SUITE("prerequisites");

    suite->add(BOOST_TEST_CASE(nrvo));
    suite->add(BOOST_TEST_CASE(mclose));
    suite->add(BOOST_TEST_CASE(funcs));

    return suite;
}