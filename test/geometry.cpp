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

void quaternion_geometry()
{
    quaternion q1 = quaternion::xyzw(0.5f, 0.7f, 0.212f, 0.8f);
    quaternion q2 = quaternion::xyzw(0.12f, 0.33f, 0.4f, 0.5f);

    quaternion q3 = slerp(q1, q2, 0.55f);

    QUAT_CHECK_CLOSE(q3, quaternion::xyzw(
        0.30942556881258626f, 0.527364923066248f, 0.33413672218578583f, 0.6741185090656765f));
}

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

    suite->add(BOOST_TEST_CASE(quaternion_geometry));
    suite->add(BOOST_TEST_CASE(rotation));

    return suite;
}
