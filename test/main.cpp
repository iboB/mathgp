//                MathGP Library
//     Copyright (c) 2012 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this 
//  distribution for details about the copyright

#include <boost/test/unit_test.hpp>

using namespace boost::unit_test;

test_suite* prerequisites();

test_suite* construction();

test_suite* arithmetic();

test_suite* swizzle();

test_suite* geometry();

test_suite* gpu_specific();

test_suite* perf();

test_suite* init_unit_test_suite(int argc, char* argv[])
{
    test_suite* main_test = BOOST_TEST_SUITE( "MathGP" );

    main_test->add(prerequisites());

    return main_test;
}

