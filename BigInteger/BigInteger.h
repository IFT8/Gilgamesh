/// Copyright (C) 2015
/// \file BigInteger.h
/// \brief Class definition of BigInteger
/// \author zec_iiii
/// \version 0.0.1
/// \date 2015-5-8

#ifndef __BIGINTEGER_H__
#define __BIGINTEGER_H__

#include <iostream>
#include <vector>

const unsigned int CAPACITY = 10000;
/// \class BigInteger
/// \brief A class to process computation between big integers that cannot be hold by built-in types.
/// The class use base 2^32, which improves the performance and space utility of computation.
/// This class has only simple functionalities by now. When I have more requirements someday, I will improve it.
class BigInteger{
public:
    /// Constructor.
    BigInteger() {
        content.reserve(CAPACITY);
    }

    /// Constructor with an unsigned for initialization.
    BigInteger(unsigned a) {
        content.reserve(CAPACITY);
        content.push_back(a);
    }

    /// Copy-constructor.
    BigInteger(BigInteger& a) {
        content.reserve(CAPACITY);
        this->content = a.content;
        this->content.resize(a.content.size());
    }

    /// Assignment operation.
    BigInteger& operator=(const BigInteger& b);

    /// \brief To process addition between BigInteger.
    /// \param[in] a
    /// The reference to left operator of addition expression.
    /// \param[in] b
    /// The reference to right operator of addition expression.
    /// \return An object of BigInteger which holds the result.
    friend BigInteger operator+(const BigInteger& a, const BigInteger& b);

    /// \brief To process multiplication between BigInteger.
    /// \param[in] a
    /// The reference to left operator of multiplication expression.
    /// \param[in] b
    /// The reference to right operator of multiplication expression.
    /// \return An object of BigInteger which holds the result.
    friend BigInteger operator*(const BigInteger& a, const BigInteger& b);


    /// \brief Output the value to standard output device.
    /// \warning Output is in base 16.
    friend std::ostream& operator<<(std::ostream& out, const BigInteger& a);

private:
    std::vector<unsigned> content;
};

#endif //__BIGINTEGER_H__
