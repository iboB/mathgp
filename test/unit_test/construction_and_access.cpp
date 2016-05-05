//                MathGP Library
//  Copyright (c) 2012-2016 Borislav Stanimirov
//   
//  See the LICENSE.txt file, included in this
//  distribution for details about the copyright
#include "mathgp_test.h"

#include <cstring>

using namespace std;
using namespace mathgp;

TESTCASE("ntuple_construct")
{
    CHECK(sizeof(vector1t<int>) == sizeof(int));
    CHECK(sizeof(vector2t<char>) == 2 * sizeof(char));
    CHECK(sizeof(vector3t<long double>) == 3 * sizeof(long double));
    CHECK(sizeof(vector4t<long long>) == 4 * sizeof(long long));
    
    CHECK(sizeof(matrix1x1t<long>) == sizeof(long));
    CHECK(sizeof(matrix2x2t<float>) == 2 * 2 * sizeof(float));
    CHECK(sizeof(matrix3x3t<short>) == 3 * 3 * sizeof(short));
    CHECK(sizeof(matrix4x4t<double>) == 4 * 4 * sizeof(double));

    CHECK(sizeof(complext<unsigned>) == 2 * sizeof(unsigned));
    CHECK(sizeof(quaterniont<float>) == 4 * sizeof(float));

    float f2[] = {1.f, 2.f};

    float2 v22 = vector2::from_ptr(f2);
    CHECK(memcmp(&v22, &f2, 2 * sizeof(float)) == 0);

    float2& rv2 = vector2::attach_to_ptr(f2);
    CHECK(static_cast<void*>(&rv2) == static_cast<void*>(f2));

    float fzero[] = 
        {0, 0, 0, 0, 
         0, 0, 0, 0, 
         0, 0, 0, 0, 
         0, 0, 0, 0 };
    point3 zero3 = point3::zero();
    CHECK(memcmp(&zero3, &fzero, 3 * sizeof(float)) == 0);

    matrix3 m3zero = matrix3::zero();
    CHECK(memcmp(&m3zero, &fzero, sizeof(matrix3)) == 0);

    matrix mzero = matrix::zero();
    CHECK(memcmp(&mzero, &fzero, sizeof(matrix)) == 0);

    float ffive[] = {5, 5, 5, 5};
    float4 v4 = float4::uniform(5);
    CHECK(memcmp(&v4, &ffive, 4 * sizeof(float)) == 0);

    matrix2x2t<float> m2_5 = matrix2x2t<float>::uniform(5);
    CHECK(memcmp(&m2_5, &ffive, sizeof(matrix2x2t<float>)) == 0);

    point4 v44 = v4; //auto generated copy constructor
    CHECK(memcmp(&v4, &v4, 4 * sizeof(float)) == 0);

    float f44[] = {1, 2, 3, 4};
    vector2* ar2 = vector2::attach_to_array(f44);
    CHECK(static_cast<void*>(ar2) == static_cast<void*>(f44));
    CHECK(static_cast<void*>(ar2 + 1) == static_cast<void*>(f44 + 2));

    matrix2& rm2 = matrix2::attach_to_ptr(f44);
    CHECK(static_cast<void*>(&rm2) == static_cast<void*>(ar2));
}

TESTCASE("vector_construct")
{
    vector1t<int> v1 = vector1t<int>::coord(7);
    int i = 7;
    CHECK(memcmp(&v1, &i, sizeof(int)) == 0);

    float fv[] = {1, 2, 3, 4};

    vector2 v2 = v(1.f, 2.f);    
    CHECK(memcmp(&v2, fv, 2 * sizeof(float)) == 0);

    float3 v3 = float3::coord(1, 2, 3);
    CHECK(memcmp(&v3, fv, sizeof(vector3)) == 0);

    point4 v4 = point4::coord(1, 2, 3, 4);
    CHECK(memcmp(&v4, fv, sizeof(point4)) == 0);

    vector3 v32 = vc(1, 2, 3);
    CHECK(memcmp(&v32, fv, sizeof(point3)) == 0);
}

TESTCASE("matrix_construct")
{
    float fm[] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };

    float2x2 m2 = float2x2::rows(
        1, 3,
        2, 4);    
    CHECK(memcmp(&m2, fm, sizeof(float2x2)) == 0);

    float2x2 m22 = float2x2::columns(
        1, 2,
        3, 4);
    CHECK(memcmp(&m22, fm, sizeof(float2x2)) == 0);

    matrix3 m3 = matrix3::rows(
        1, 4, 7,
        2, 5, 8,
        3, 6, 9);    
    CHECK(memcmp(&m3, fm, sizeof(matrix3)) == 0);

    matrix3 m33 = matrix3::columns(
        1, 2, 3,
        4, 5, 6,
        7, 8, 9);
    CHECK(memcmp(&m33, fm, sizeof(matrix3)) == 0);

    matrix4 m4 = matrix4::rows(
        1, 5, 9, 13,
        2, 6, 10, 14,
        3, 7, 11, 15,
        4, 8, 12, 16);    
    CHECK(memcmp(&m4, fm, sizeof(matrix4)) == 0);

    matrix4 m44 = matrix4::columns(
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16);
    CHECK(memcmp(&m44, fm, sizeof(matrix4)) == 0);
}

TESTCASE("other_construct")
{
    double d[] = {1, 2};
    complext<double> cd = complext<double>::values(1, 2);
    CHECK(memcmp(&cd, d, sizeof(complext<double>)) == 0);

    float f1[] = {5, 0};
    complex c1 = complex::real(5);
    CHECK(memcmp(&c1, f1, sizeof(complex)) == 0);

    float f2[] = {0, 17};
    complex c2 = complex::imaginary(17);
    CHECK(memcmp(&c2, f2, sizeof(complex)) == 0);

    float f3[] = {0, 0, 0, 1};
    complex ci = complex::identity();
    CHECK(memcmp(&ci, f3 + 2, sizeof(complex)) == 0);

    quaternion q = quaternion::identity();
    CHECK(memcmp(&q, f3, sizeof(quaternion)) == 0);
}

TESTCASE("compare")
{
    vector3 v1 = vector3::coord(1, 2, 3);
    vector3 v2 = vector3::coord(1, 2, 3);

    CHECK(v1 == v2);

    v1 = vector3::coord(5, 6, 7);
    
    CHECK(v1 != v2);
    
    v2 = v1;

    CHECK(v1 == v2);
}

TESTCASE("access")
{
}
