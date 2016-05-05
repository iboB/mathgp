//                MathGP Library
//  Copyright (c) 2012-2016 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright
#include "mathgp_test.h"

using namespace mathgp;

TESTCASE("vector_geometry")
{
    vector3 a = vector3::coord(0, 1, 0);

    CHECK(close(a.length(), 1.f, mathgp::constants<float>::EPSILON()));
    CHECK(a.length_sq() == 1.f);
    CHECK(a.manhattan_length() == 1.f);

    vector3 b = vector3::coord(1, 2, 3);

    CHECK(close(b.length(), 3.741657387f, mathgp::constants<float>::EPSILON()));
    CHECK(b.length_sq() == 14.f);
    CHECK(b.manhattan_length() == 6.f);

    CHECK(close(distance(a, b), 3.31662479f, mathgp::constants<float>::EPSILON()));
    CHECK(distance_sq(a, b) == 11.f);
    CHECK(manhattan_distance(a, b) == 5.f);

	a = vector3::coord(0, 1, 0);
	b = vector3::coord(1, 0, 0);

	CHECK(orthogonal(a, b));
	CHECK(!collinear(a, b));
	
	a = vector3::coord(1, 0, 0);
	b = vector3::coord(0, 1, 0);

	CHECK(orthogonal(a, b));
	CHECK(!collinear(a, b));

	a = vector3::coord(11.23f, 44.44f, 1.4323f);
	b = a.get_orthogonal();
	CHECK(orthogonal(a, b));
	CHECK(orthogonal(a, vector3::zero()));
	CHECK(orthogonal(vector3::zero(), b));

	b = 3*a;
	CHECK(collinear(a, b));
	CHECK(collinear(a, vector3::zero()));
	CHECK(collinear(vector3::zero(), b));
}

TESTCASE("matrix_algebra")
{
    matrix m1 = matrix::identity();
    CHECK(m1 == transpose(m1));
    CHECK(m1.determinant() == 1);
    CHECK(close(inverse(m1), m1));

    m1 = matrix::rows(
        1, 0, 0, 0,
        0, 2, 0, 0,
        0, 0, 3, 0,
        0, 0, 0, 4);
    CHECK(m1.determinant() == 24);

    m1 = matrix::rows(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    matrix m2 = matrix::columns(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    CHECK(m1.determinant() == 0);
    CHECK(m2.determinant() == 0);
    CHECK(m1 == transpose(m2));
    CHECK(transpose(m1) == m2);

    m1 = matrix::rows(
        1, 2, 3, 4,
        5, 5, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 86);
    CHECK(m1.determinant() == 1120);

    m2 = inverse(m1);
    CHECK(close(inverse(m2), m1, constants<float>::EPSILON_LOW()));
    CHECK(close(m2, m1.inverse()));
    CHECK(close(m2, m1));

    CHECK(close(m2, matrix::rows(
        -0.933929f,  0.5f, -0.073214f,  0.007143f,
         0.5f,      -1.f,   0.5f,       0.f,
         0.301786f,  0.5f, -0.280357f, -0.021429f,
         0.007143f,  0.f,  -0.021429f,  0.014286f)));
}

TESTCASE("quaternion_geometry")
{
    quaternion q1 = quaternion::xyzw(0.5f, 0.7f, 0.212f, 0.8f);
    quaternion q2 = quaternion::xyzw(0.12f, 0.33f, 0.4f, 0.5f);

    quaternion q3 = slerp(q1, q2, 0.55f);

    CHECK(close(q3, quaternion::xyzw(
        0.30942556881258626f, 0.527364923066248f, 0.33413672218578583f, 0.6741185090656765f)));
}

TESTCASE("scaling")
{
    matrix m = matrix::scaling_uniform(1);
    CHECK(m == matrix::identity());
}

TESTCASE("rotation")
{
    matrix rot;

    quaternion q = quaternion::identity();

    matrix qrot = matrix::rotation_quaternion(q);

    CHECK(qrot.is_identity());

    q = quaternion::rotation_axis(vector3::coord(1, 2, 3), 0.15f);
    qrot = matrix::rotation_quaternion(q);
    rot = matrix::rotation_axis(vector3::coord(1, 2, 3), 0.15f);

    CHECK(close(qrot, rot));

	q = quaternion::rotation_vectors(vector3::coord(1, 0, 0), vector3::coord(0, 1, 0));
	quaternion q2 = quaternion::rotation_axis(vector3::coord(0, 0, 1), constants<float>::PI_HALF());
    CHECK(close(q, q2));
}
