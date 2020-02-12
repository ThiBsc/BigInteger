#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <map>
#include <cctype>
#include <iomanip>

#define B10P9 1000000000
#define MAX_B10P9 999999999

// get the highest part of a uint32
uint32_t hi(uint32_t x);
// get the lowest part of a uint32
uint32_t lo(uint32_t x);
// get the carry of an overflow when multiply a with b
uint32_t multiply(uint32_t a, uint32_t b, uint32_t *carry = nullptr);

/**
* BigInteger C++ implementation
*/
class BigInteger
{
public:
    BigInteger();
    BigInteger(int32_t value);
    BigInteger(std::string strvalue);
    ~BigInteger();

    /**
     * Elementary arithmetic
     */
    // bi would be always less than (*this)
    BigInteger add(const BigInteger& bi) const;
    // bi would be always less than (*this)
    BigInteger sub(const BigInteger& bi) const;
    // multiply (*this) with bi
    BigInteger mul(const BigInteger& bi) const;

	friend std::ostream& operator<<(std::ostream& stream, const BigInteger& bi){
        for (auto i = bi.b10.rbegin(); i != bi.b10.rend(); i++){
            stream << (*i) << std::setfill('0') << std::setw(9);
        }
        stream << bi.value;
        return stream;
    }


private:
	/**
	* Each value of b10 represents an integer in base 10^9
    * If we have 3 values in b10:
    * b10[0]*(10^9) + b10[1]*(10^ (9*2)) + b10[0]*(10^ (9*3))
	*/
	std::vector<uint32_t> b10;
	uint32_t value;
    bool isSigned;

};

#endif // BIGINTEGER_H
