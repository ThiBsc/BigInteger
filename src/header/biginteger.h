#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <cctype>

/**
* BigInteger C++ implementation
*/
class BigInteger
{
public:
    BigInteger();
    BigInteger(int value);
    BigInteger(long long value);
    BigInteger(std::string value, int radix = 10);
    ~BigInteger();

    static BigInteger ZERO;
    static BigInteger ONE;
    static BigInteger TEN;    

    /**
     * Elementary arithmetic
     */
    BigInteger add(const BigInteger& bi) const;
    BigInteger substract(const BigInteger& bi) const;
    BigInteger multiply(const BigInteger& bi) const;
    BigInteger divide(const BigInteger& bi) const;

    /**
     * Complex arithmetic
     */
    BigInteger pow(const BigInteger& bi) const;
    BigInteger modulus(const BigInteger& bi) const;

    /**
     * Modification & Checking
     */
    int bitLength() const;
    int compare(const BigInteger& bi) const;
    BigInteger negate() const;
    BigInteger absolute() const;
    bool isPositive() const;
    bool isNegative() const;
    void swap(BigInteger& bi);

    /**
     * Operator
     */
    BigInteger operator+(const BigInteger& bi);
    BigInteger operator-(const BigInteger& bi);
    BigInteger operator*(const BigInteger& bi);
    BigInteger operator/(const BigInteger& bi);
    BigInteger operator%(const BigInteger& bi);
    BigInteger& operator+=(const BigInteger& bi);
    BigInteger& operator-=(const BigInteger& bi);
    BigInteger& operator*=(const BigInteger& bi);
    BigInteger& operator/=(const BigInteger& bi);
    BigInteger& operator--(); // pre
    BigInteger operator--(int); // post
    BigInteger& operator++(); // pre
    BigInteger operator++(int); // post
    bool operator==(const BigInteger& bi);
    bool operator!=(const BigInteger& bi);
    bool operator<(const BigInteger& bi);
    bool operator>(const BigInteger& bi);
    bool operator<=(const BigInteger& bi);
    bool operator>=(const BigInteger& bi);
    friend std::ostream& operator<<(std::ostream& stream, const BigInteger& bi){
        stream << bi.toString();
        return stream;
    }    

    std::string toString(int radix = 10) const;

private:
    int m_radix;
    bool m_signed;
    std::string m_value;

};

#endif // BIGINTEGER_H