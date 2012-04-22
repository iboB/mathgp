// this MathGP dependent file should compile with no errors

#include "../../mathgp/mathgp.h"

using namespace mathgp;

void f()
{
    vector3 v = vector3::coord(1, 2, 3);
	matrix4 c = matrix4::identity();
	quaternion q = quaternion::identity();
}