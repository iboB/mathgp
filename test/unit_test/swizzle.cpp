//                MathGP Library
//  Copyright (c) 2012-2016 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright
#include "mathgp_test.h"

using namespace std;
using namespace mathgp;

TESTCASE("swizzle_const")
{
    const vector4 v = vc(1, 2, 3, 4);

    CHECK(v.xy() == vc(1, 2));
    CHECK(v.yz() == vc(2, 3));
    CHECK(v.zw() == vc(3, 4));
    CHECK(v.xyz() == vc(1, 2, 3));
    CHECK(v.yzw() == vc(2, 3, 4));
    CHECK(v.xyzw() == vc(1, 2, 3, 4));

    CHECK(v.wyzx() == vc(4, 2, 3, 1));
    CHECK(v.xxxx() == vc(1, 1, 1, 1));
    CHECK(v.zzx() == vc(3, 3, 1));
}

void swizzle_read()
{
    vector4 v = vc(1, 2, 3, 4);

    CHECK(v.xy() == vc(1, 2));
    //BOOST_CHECK_EQUAL(v.yz(), vc(2, 3));
    //BOOST_CHECK_EQUAL(v.zw(), vc(3, 4));
    //BOOST_CHECK_EQUAL(v.xyz(), vc(1, 2, 3));
    //BOOST_CHECK_EQUAL(v.yzw(), vc(2, 3, 4));
    //BOOST_CHECK_EQUAL(v.xyzw(), vc(1, 2, 3, 4));

    //BOOST_CHECK_EQUAL(v.wyzx(), vc(4, 2, 3, 1));
    //BOOST_CHECK_EQUAL(v.xxxx(), vc(1, 1, 1, 1));
    //BOOST_CHECK_EQUAL(v.zzx(), vc(3, 3, 1));
}
