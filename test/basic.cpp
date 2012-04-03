#include <iostream>

#include <yamgp/yamgp.h>

using namespace std;
using namespace yamgp;

int main()
{
    auto v2 = vector2t<float>::coord(1, 2);

    cout << v2 << endl;
}