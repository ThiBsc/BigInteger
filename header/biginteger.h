#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <cmath>
#include <algorithm>
#include <ostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <iomanip>

/**
* BigInteger C++ implementation
*/
class BigInteger
{
public:
    BigInteger();
    BigInteger(int value);
    BigInteger(std::string value);
    ~BigInteger();

    /**
     * Elementary arithmetic
     */
    // bi would be always less than (*this)
    BigInteger addition(const BigInteger& bi) const;
    // bi would be always less than (*this)
    BigInteger substract(const BigInteger& bi) const;
    // https://stackoverflow.com/questions/1815367/catch-and-compute-overflow-during-multiplication-of-two-large-integers
    // test http://coliru.stacked-crooked.com/a/2af4af1f9dff611d
    BigInteger multiply(const BigInteger& bi) const;

	friend std::ostream& operator<<(std::ostream& stream, const BigInteger& bi){
        for (auto i = bi.b10.rbegin(); i != bi.b10.rend(); i++){
            stream << (*i) << std::setfill('0') << std::setw(9);
        }
        stream << bi.value;
        return stream;
    }


public:
	/**
	* Each value of size represents an integer in base 10^9
    * If we have 3 values in size:
    * b10[0]*(10^9) + b10[1]*(10^ (9*2)) + b10[0]*(10^ (9*3))
	*/
	std::vector<uint32_t> b10;
	uint32_t value;
    bool isSigned;

};

#endif // BIGINTEGER_H
