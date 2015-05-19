#include <mathgp/mathgp.h>
#include <mathgp/stdext.h>
#include <iostream>
#include <vector>

#include "high_res_clock.h"

using namespace mathgp;
using namespace std;
using namespace gdproto;

struct simple_matrix
{
    float m[4][4];
};

struct simple_vec3
{
    float v[3];
};

void mult(const float a[4][4], const float v[3], float out[3])
{
    // matrix is columns
    float w = a[0][3] * v[0] + a[1][3] * v[1] + a[2][3] * v[2] + a[3][3];

    out[0] = (a[0][0] * v[0] + a[1][0] * v[1] + a[2][0] * v[2] + a[3][0]) / w;
    out[1] = (a[0][1] * v[0] + a[1][1] * v[1] + a[2][1] * v[2] + a[3][1]) / w;
    out[2] = (a[0][2] * v[0] + a[1][2] * v[1] + a[2][2] * v[2] + a[3][2]) / w;    
}

float rnd()
{
    float r = float(rand()) / RAND_MAX;
    r *= 10;
    return r;
}

const size_t A_LOT = 10000000;

int main()
{
    vector<simple_matrix> simple_matrices(A_LOT);
    vector<simple_vec3> simple_vectors(A_LOT);

    auto mathgp_matrices = matrix::attach_to_array(simple_matrices.front().m[0]);
    auto mathgp_vectors = vector3::attach_to_array(simple_vectors.front().v);

    // fill values
    for (size_t i = 0; i < A_LOT; ++i)
    {
        for (float& a : mathgp_matrices[i])
        {
            a = rnd();
        }

        for (float& v : mathgp_vectors[i])
        {
            v = rnd();
        }
    }

    vector<simple_vec3> simple_results(A_LOT);
    auto mathgp_attached_results = vector3::attach_to_array(simple_results.front().v);
    vector<vector3> mathgp_results(A_LOT);

    auto start = high_res_clock::now();
    for (size_t i = 0; i < A_LOT; ++i)
    {
        mult(simple_matrices[i].m, simple_vectors[i].v, simple_results[i].v);
    }
    auto simple_time = high_res_clock::now() - start;
    cout << "Simple: " << double(std::chrono::duration_cast<std::chrono::microseconds>(simple_time).count()) / 1000 << "ms" << endl;

    start = high_res_clock::now();
    for (size_t i = 0; i < A_LOT; ++i)
    {
        mathgp_results[i] = transform_coord(mathgp_vectors[i], mathgp_matrices[i]);
    }
    auto mathgp_time = high_res_clock::now() - start;
    cout << "Mathgp: " << double(std::chrono::duration_cast<std::chrono::microseconds>(mathgp_time).count()) / 1000 << "ms" << endl;

    for (size_t i = 0; i < A_LOT; ++i)
    {
        if (mathgp_attached_results[i] != mathgp_results[i])
        {
            cerr << "sanity check failed!!!" << endl;
            return -1;
        }
    }

    return 0;
}