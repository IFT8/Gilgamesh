/// Copyright (C) 2015
/// \file test.cpp
/// \brief Unit test for BigInteger
/// \author zec_iiii
/// \version 0.0.1
/// \date 2015-5-8

#include "BigInteger.h"
using namespace std;

int main() {
    unsigned a = 0x0, b = 0x0;
    cout << std::hex << a << " + " << b << " = " << BigInteger(a) + BigInteger(b) << endl;
    cout << "answer:0" << endl;

    a = 0xffffffff;
    b = 0x1;
    cout << std::hex << a << " + " << b << " = " << BigInteger(a) + BigInteger(b) << endl;
    cout << "answer:1 0" << endl;

    a = 0xffffffff;
    b = 0xffffffff;
    cout << std::hex << a << " + " << b << " = " << BigInteger(a) + BigInteger(b) << endl;
    cout << "answer:1 fffffffe" << endl;

    return 0;
}
