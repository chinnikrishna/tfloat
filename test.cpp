#include <iostream>
#include <bitset>
#include "tfloat8.h"
#include <cmath>
using namespace std;
int main() {

    TFloat8_t test4(-5.75, 3);
    cout << test4 << endl;

    float test = TFloat8_t::toFloat(test4);
    cout << test << endl;
    return 0;

}