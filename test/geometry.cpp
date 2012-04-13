//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright

#include "precompiled.h"
#include "mathgp_test.h"

using namespace boost::unit_test;
using namespace std;
using namespace mathgp;

void rotation()
{
    matrix rot;

    quaternion q = quaternion::identity();

    matrix qrot = matrix::rotation_quaternion(q);

    BOOST_CHECK(qrot.is_identity());

    q = quaternion::rotation_axis(vector3::coord(1, 2, 3), 0.15f);
    qrot = matrix::rotation_quaternion(q);
    rot = matrix::rotation_axis(vector3::coord(1, 2, 3), 0.15f);

    MAT4_CHECK_CLOSE(qrot, rot);
}

test_suite* geometry()
{
    test_suite* suite = BOOST_TEST_SUITE("geometry");

    suite->add(BOOST_TEST_CASE(rotation));

    return suite;
}
