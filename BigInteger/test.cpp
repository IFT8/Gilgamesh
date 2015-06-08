/// Copyright (C) 2015
/// \file test.cpp
/// \brief Unit test for BigInteger
/// \author zec_iiii
/// \version 0.0.1
/// \date 2015-5-8

/*
	The MIT License
	Copyright (c) 2011 Mike Chambers
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

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
