//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright

#include <boost/test/unit_test.hpp>

#define MATHGP_DISABLE_SWIZZLE
#define MATHGP_PREFERRED_TYPE float

#include <mathgp/mathgp.h>

using namespace boost::unit_test;
using namespace std;
using namespace mathgp;

test_suite* specific_3d()
{
    test_suite* suite = BOOST_TEST_SUITE("specific_3d");

    return suite;
}