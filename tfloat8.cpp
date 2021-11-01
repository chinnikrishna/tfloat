#ifndef TFLOAT8_CPP_GUARD
#define TFLOAT8_CPP_GUARD
#include <iostream>
#include <cmath>
#include "tfloat8.h"
using namespace std;
// Constructor
TFloat8_t::TFloat8_t():mTFloat8(0) {}
TFloat8_t::TFloat8_t(const float fpNum, uint8_t bias) {
    // Reinterpret floating point as bits
    const uint32_t bits = *(uint32_t*) &fpNum;
    // Extract out sign bit
    uint8_t sign = (bits & 0x80000000) >> 31;
    // Extract out exponent bits
    uint8_t exp = (bits & 0x7F800000) >> 23;

    int8_t expComp = static_cast<int8_t>(exp) - static_cast<int8_t>(127);
    // Extract out mantissa bits
    uint16_t mant = (bits & 0x007FFFFF);
    // Check if we can represent fpNum exponent with passed bias
    int8_t maxExp = static_cast<int8_t>(pow(2, 4)) - 1 - static_cast<int8_t>(bias);
    int8_t minExp = (-1 * bias) + 1;

    if (expComp < minExp) {
        cout << "Underflow, increase bias by " << abs(expComp - minExp) <<" , failed to convert" << endl;
        cout << hex << float(expComp) << endl;
        cout << hex << float(minExp) << endl;
        return;
    }
    if (expComp >= maxExp) {
        cout << "Overflow, decrease bias by " << abs(expComp - minExp) <<" , failed to convert" << endl;
        return;
    }

}


// Destructor
TFloat8_t::~TFloat8_t() {}

// Streaming Operator
std::ostream& operator << (std::ostream& stream, TFloat8_t tfNum){
    stream << float(tfNum.mTFloat8);
    return stream;
}

#endif