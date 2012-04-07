//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright

#include <boost/test/unit_test.hpp>

#define MATHGP_DISABLE_SWIZZLE
#define MATHGP_PREFERRED_TYPE float

#include <mathgp/mathgp.h>
#include <mathgp/stdext.h>

using namespace boost::unit_test;
using namespace std;
using namespace mathgp;

void ntuple_arithmetic()
{
}

void vector_arithmetic()
{
    vector3 v1 = vector3::uniform(1);
    vector3 v6 = 6.f * v1;

    BOOST_CHECK_EQUAL(v6, vector3::coord(6, 6, 6));    
}

void matrix_arithmetic()
{
    matrix mi = matrix::identity();

    matrix a = matrix::rows(
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16);

    matrix ai = a * mi;
    BOOST_CHECK_EQUAL(a, ai);

    ai = mi * a;
    BOOST_CHECK_EQUAL(a, ai);

    ai*=mi;
    BOOST_CHECK_EQUAL(a, ai);

    matrix b = matrix::rows(
        6, 4, 23, 11,
        16, 11, 1, 2,
        1, 1, 4, 6,
        55, 43, 21, -3
        );

    matrix c = a*b;
    BOOST_CHECK_EQUAL(c, 
        matrix::rows(
            261, 201, 121, 21,
            573, 437, 317, 85,
            885, 673, 513, 149, 
            1197, 909, 709, 213));
}

test_suite* arithmetic()
{
    test_suite* suite = BOOST_TEST_SUITE("arithmetic");

    suite->add(BOOST_TEST_CASE(ntuple_arithmetic));
    suite->add(BOOST_TEST_CASE(vector_arithmetic));
    suite->add(BOOST_TEST_CASE(matrix_arithmetic));    

    return suite;
}
