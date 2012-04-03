#include <iostream>

#include <mathgp/mathgp.h>

using namespace std;
using namespace mathgp;

int main()
{
    auto v2 = vector2t<float>::coord(1, 2);

    cout << v2.yxxy() << endl;
}