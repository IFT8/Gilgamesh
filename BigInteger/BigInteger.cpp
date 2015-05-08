/// Copyright (C) 2015
/// \file BigInteger.cpp
/// \brief Class implementation of BigInteger
/// \author zec_iiii
/// \version 0.0.1
/// \date 2015-5-8

#include "BigInteger.h"
using namespace std;

BigInteger operator+(const BigInteger& a, const BigInteger& b) {
    vector<unsigned int>::size_type max = min(a.content.size(), b.content.size());
    BigInteger result;
    unsigned int carry = 0;
    for (vector<unsigned int>::size_type i = 0; i < max; i++) {
        unsigned int temp = a.content[i]+b.content[i]+carry;
        if (temp < a.content[i] || temp < b.content[i]) {
            carry = 1;
        }
        else {
            carry = 0;
        }
        result.content.push_back(temp);
    }
    if (a.content.size() < b.content.size()) {
        for (vector<unsigned int>::size_type i = a.content.size(); i < b.content.size(); i++) {
            unsigned int temp = b.content[i]+carry;
            if (temp < b.content[i] || temp < carry) {
                carry = 1;
            }
            else {
                carry = 0;
            }
            result.content.push_back(temp);
        }
    }
    else if (a.content.size() > b.content.size()) {
        for (vector<unsigned int>::size_type i = b.content.size(); i < a.content.size(); i++) {
            unsigned int temp = a.content[i]+carry;
            if (temp < b.content[i] || temp < carry) {
                carry = 1;
            }
            else {
                carry = 0;
            }
            result.content.push_back(temp);
        }
    }
    if (carry == 1) {
        result.content.push_back(carry);
    }
    return result;
}

BigInteger operator*(const BigInteger& a, const BigInteger& b) {
    BigInteger result(0);
    unsigned long long carry = 0;
    for (vector<unsigned int>::size_type i = 0; i < a.content.size(); i++) {
        unsigned long long tempa = static_cast<unsigned long long>(a.content[i]);
        BigInteger temp_result;
        for (vector<unsigned int>::size_type k = 0; k < i; k++) {
            temp_result.content.push_back(0);
        }
        for (vector<unsigned int>::size_type j = 0; j < b.content.size(); j++) {
            unsigned long long tempb = static_cast<unsigned long long>(b.content[j]);
            tempb *= tempa;
            tempb += carry;
            temp_result.content.push_back(static_cast<unsigned int>(tempb & 0xffffffff));
            carry = tempb >> 32;
        }
        if (carry != 0) {
            temp_result.content.push_back(static_cast<unsigned int>(carry));
        }
        result = result + temp_result;
    }
    return result;
}

BigInteger& BigInteger::operator=(const BigInteger& b) {
    this->content = b.content;
    this->content.resize(b.content.size());
    return *this;
}

ostream& operator<<(ostream& out, const BigInteger& a) {
    for (int i = static_cast<int>(a.content.size()-1); i >= 0; i--) {
        out << std::hex << a.content[i] << ' ';
    }
    return out;
}
