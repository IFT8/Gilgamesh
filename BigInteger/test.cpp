/// Copyright (C) 2015
/// \file test.cpp
/// \brief Unit test for BigInteger
/// \author zec_iiii
/// \version 0.0.1
/// \date 2015-5-8

#include "BigInteger.h"
using namespace std;

int main() {
    // a=0, b=0
    unsigned a = 0x0, b = 0x0;
    cout << std::hex << a << " + " << b << " = " << BigInteger(a) + BigInteger(b) << endl;
    cout << "answer:0" << endl;
    cout << std::hex << a << " * " << b << " = " << BigInteger(a) * BigInteger(b) << endl;
    cout << "answer:0" << endl;

    // carry
    a = 0xffffffff;
    b = 0x1;
    cout << std::hex << a << " + " << b << " = " << BigInteger(a) + BigInteger(b) << endl;
    cout << "answer:1 0" << endl;
    cout << std::hex << a << " * " << b << " = " << BigInteger(a) * BigInteger(b) << endl;
    cout << "answer:0xffffffff" << endl;

    a = 0xffffffff;
    b = 0xffffffff;
    cout << std::hex << a << " + " << b << " = " << BigInteger(a) + BigInteger(b) << endl;
    cout << "answer:1 fffffffe" << endl;
    cout << std::hex << a << " * " << b << " = " << BigInteger(a) * BigInteger(b) << endl;
    cout << "answer:fffffffe 1" << endl;

    b = a + b;
    // a.size < b.size
    cout << std::hex << a << " + " << b << " = " << BigInteger(a) + BigInteger(b) << endl;
    cout << "answer:2 fffffffd" << endl;

    // b.size > a.size
    cout << std::hex << b << " + " << a << " = " << BigInteger(b) + BigInteger(a) << endl;
    cout << "answer:2 fffffffd" << endl;

    return 0;
}
