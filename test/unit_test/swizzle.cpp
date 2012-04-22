//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright

#include "precompiled.h"

using namespace boost::unit_test;
using namespace std;
using namespace mathgp;

void swizzle_const()
{
    const vector4 v = vc(1, 2, 3, 4);

    BOOST_CHECK_EQUAL(v.xy(), vc(1, 2));
    BOOST_CHECK_EQUAL(v.yz(), vc(2, 3));
    BOOST_CHECK_EQUAL(v.zw(), vc(3, 4));
    BOOST_CHECK_EQUAL(v.xyz(), vc(1, 2, 3));
    BOOST_CHECK_EQUAL(v.yzw(), vc(2, 3, 4));
    BOOST_CHECK_EQUAL(v.xyzw(), vc(1, 2, 3, 4));

    BOOST_CHECK_EQUAL(v.wyzx(), vc(4, 2, 3, 1));
    BOOST_CHECK_EQUAL(v.xxxx(), vc(1, 1, 1, 1));
    BOOST_CHECK_EQUAL(v.zzx(), vc(3, 3, 1));
}

void swizzle_read()
{
    vector4 v = vc(1, 2, 3, 4);

    BOOST_CHECK_EQUAL(v.xy(), vc(1, 2));
    //BOOST_CHECK_EQUAL(v.yz(), vc(2, 3));
    //BOOST_CHECK_EQUAL(v.zw(), vc(3, 4));
    //BOOST_CHECK_EQUAL(v.xyz(), vc(1, 2, 3));
    //BOOST_CHECK_EQUAL(v.yzw(), vc(2, 3, 4));
    //BOOST_CHECK_EQUAL(v.xyzw(), vc(1, 2, 3, 4));

    //BOOST_CHECK_EQUAL(v.wyzx(), vc(4, 2, 3, 1));
    //BOOST_CHECK_EQUAL(v.xxxx(), vc(1, 1, 1, 1));
    //BOOST_CHECK_EQUAL(v.zzx(), vc(3, 3, 1));
}

test_suite* swizzle()
{
    test_suite* suite = BOOST_TEST_SUITE("swizzle");

    suite->add(BOOST_TEST_CASE(swizzle_const));
    suite->add(BOOST_TEST_CASE(swizzle_read));

    return suite;
}
