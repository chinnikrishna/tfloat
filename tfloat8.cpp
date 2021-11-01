#ifndef TFLOAT8_CPP_GUARD
#define TFLOAT8_CPP_GUARD
#include <iostream>
#include <bitset>
#include <cmath>
#include "tfloat8.h"
using namespace std;
// Constructor
TFloat8_t::TFloat8_t():mTFloat8(0) {}
TFloat8_t::TFloat8_t(const float fpNum, uint8_t bias) {
    // Reinterpret floating point as bits
    const uint32_t bits = *(uint32_t*) &fpNum; // TODO: Replace with bit_cast
    // Extract out sign bit
    uint8_t sign = (bits & 0x80000000) >> 31;
    // Extract out exponent bits
    uint8_t exp = (bits & 0x7F800000) >> 23;
    // Extract out mantissa bits
    uint32_t mant = (bits & 0x007FFFFF);
    // Max and Min exponent values we can generate
    int8_t maxExp = static_cast<int8_t>(pow(2, 4)) - 1 - static_cast<int8_t>(bias);
    int8_t minExp = (-1 * static_cast<int8_t>(bias)) + 1;
    // Create a signed version of exponent and subtract 127
    int8_t expComp = static_cast<int8_t>(exp) - static_cast<int8_t>(127);
    // Check if we can represent the exponent.
    // Issue a warning and return back to create an object with 0 stored.
    if (expComp < minExp) {
        cout << "Underflow, increase bias by " << abs(expComp - minExp) <<" , failed to convert" << endl;
        return;
    }
    if (expComp >= maxExp) {
        cout << "Overflow, decrease bias by " << abs(expComp - maxExp) <<" , failed to convert" << endl;
        return;
    }
    // Truncate mantissa to 3 bits
    uint8_t mantUsed = mant >> 20;
    // Subtract 127 from exp
    exp = exp - static_cast<uint8_t>(127);
    // Now construct TFloat8
    mTFloat8 = 0;
    mTFloat8 |= (sign << 7);
    mTFloat8 |= (exp << 3);
    mTFloat8 |= mantUsed;
    // TODO: Replace all magic numbers with defined constants
}

// Destructor
TFloat8_t::~TFloat8_t() {}

float TFloat8_t::toFloat(const TFloat8_t tfNum) {
    // Reinterpret Tfloat as bits
    const uint8_t bits = *(uint8_t*) &tfNum; // TODO: Replace with bit_cast
    // TODO: Add metadata to class for storing sign, exp, mant
    uint8_t sign = (bits & 0x80) >> 7;
    uint8_t exp = (bits & 0x78) >> 3;
    uint8_t mant = (bits& 0x07);
    uint16_t expUsed = exp + static_cast<uint16_t>(127);
    uint32_t fnum=0;
    fnum |= sign << 31;
    fnum |= expUsed << 23;
    fnum |= mant << 20;
    return reinterpret_cast<float &>(fnum);
}


// Streaming Operator
std::ostream& operator << (std::ostream& stream, TFloat8_t tfNum){
    stream << TFloat8_t::toFloat(tfNum);
    return stream;
}

#endif