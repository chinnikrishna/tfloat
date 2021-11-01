#ifndef TFLOAT8_H_GUARD
#define TFLOAT8_H_GUARD
#include <iostream>
#include <cstdint>
/*
Implements a Custom Float with
1 - Sign bit
4 - Exponent bits
3 - Mantissa bits
So this is TFloat8_143
*/
struct TFloat8_t {
    uint8_t mTFloat8;
    // Constructors
    TFloat8_t();
    TFloat8_t(const float fpNum, uint8_t bias=0);
    TFloat8_t(const double fpNum, uint8_t bias=0);
    // Destructor
    ~TFloat8_t();

    // Assignment Operators
    // TODO: Template overload =
    TFloat8_t & operator = (const float & fpNum);
    TFloat8_t & operator = (const double & fpNum);

    // Comparision Operator
    bool operator == (const float & fpNum) const;
    bool operator != (const float & fpNum) const;
    bool operator < (const float & fpNum) const;
    bool operator > (const float & fpNum) const;
    bool operator <= (const float & fpNum) const;
    bool operator >= (const float & fpNum) const;

    // Conversion Operator
    operator float();
    operator double();

    // Math operators
    TFloat8_t operator + (const float & fpNum) const;
    TFloat8_t operator - (const float & fpNum) const;
    TFloat8_t operator * (const float & fpNum) const;
    TFloat8_t operator / (const float & fpNum) const;

    // Streaming operator
    friend std::ostream& operator << (std::ostream& stream, TFloat8_t fpNum);


};

#endif