#include "header/biginteger.h"
#include <iostream>

uint32_t hi(uint32_t x)
{
	return x >> 16;
}

uint32_t lo(uint32_t x)
{
	return ((1 << 16) - 1) & x;
}

uint32_t multiply(uint32_t a, uint32_t b, uint32_t *carry)
{
    // https://stackoverflow.com/questions/1815367/catch-and-compute-overflow-during-multiplication-of-two-large-integers
    // test http://coliru.stacked-crooked.com/a/2af4af1f9dff611d
	// actually uint16_t would do, but the casting is annoying
    uint32_t s0, s1, s2, s3; 

    uint32_t x = lo(a) * lo(b);
    s0 = lo(x);

    x = hi(a) * lo(b) + hi(x);
    s1 = lo(x);
    s2 = hi(x);

    x = s1 + lo(a) * hi(b);
    s1 = lo(x);

    x = s2 + hi(a) * hi(b) + hi(x);
    s2 = lo(x);
    s3 = hi(x);

    uint32_t result = (s1 << 16 | s0);
    if (carry){
        (*carry) = (s3 << 16 | s2);
    }
	
    return result;
}

BigInteger::BigInteger()
	: value(0)
	, isSigned(false)
{
    
}

BigInteger::BigInteger(int32_t value)
    : value(std::abs(value))
	, isSigned(value < 0)
{
	if ( this->value > MAX_B10P9){
		this->value -= B10P9;

		if (this->b10.empty()){
			this->b10.emplace_back(1);
		} else {
			this->b10.back() += 1;
		}
	}
}

BigInteger::BigInteger(std::string strvalue)
    : value(0)
	, isSigned(strvalue.front() == '-')
{
	if (isSigned){
		strvalue.erase(strvalue.begin());
	}

	// Offset: How many ^9 we have
	int offset = 0;
	while (!strvalue.empty()){
		// (10^9)-1 = "999999999" -> len = 9
		int pos = strvalue.size() - 9;
		pos = (pos < 0 ? 0 : pos);
		std::string val = strvalue.substr(pos);
		strvalue.erase(pos);

		unsigned long ul = std::stoul(val);
		if (offset == 0){
			this->value = ul;
		} else {
			b10.emplace_back(ul);
		}
		offset++;
	}
}

BigInteger::~BigInteger()
{

}

BigInteger BigInteger::add(const BigInteger& bi) const
{
	BigInteger add;

	add.value = (value + bi.value);
	add.b10 = b10;

	if ( add.value > MAX_B10P9){
		add.value -= B10P9;

		if (add.b10.empty()){
			add.b10.insert(add.b10.cbegin(), 1);
		} else {
			add.b10.front() += 1;
		}
	}

	std::vector<uint32_t> sumUP = bi.b10;

	auto it = add.b10.begin();
	for (const uint32_t& sum : sumUP){
		(*it) += sum;

		if ( (*it) > MAX_B10P9){
			(*it) -= B10P9;

			if (it < add.b10.end()){
				(*it) += 1;
			} else {
				add.b10.insert(add.b10.cbegin(), 1);
			}
		}
		it++;
	}

	return add;
}

BigInteger BigInteger::sub(const BigInteger& bi) const
{
	BigInteger sub;

	sub.value = value;
	sub.b10 = b10;

	std::vector<uint32_t> subDOWN = bi.b10;

	// sub > bi, (easier to compute)
	int offset = subDOWN.size()-1;

	for (int o=offset; o>=0; o--){		
		/**
		 * When a > b
		 * a - b = |b - a|
		 */
		if ( sub.b10[o] >= subDOWN[o] ){
			sub.b10[o] -= subDOWN[o];
		} else {
			int take_carry = ((subDOWN[o] - sub.b10[o]) + 5) / 10;
			sub.b10[o+1] -= take_carry;
			sub.b10[o] = ((take_carry * 10) + sub.b10[o]) - subDOWN[o];
		}
	}
	if ( sub.value >= bi.value ){
		sub.value -= bi.value;
	} else {
		int take_carry = ((sub.value - bi.value) + 5) / 10;
		sub.b10[0] -= take_carry;
		sub.value = ((take_carry * 10) + sub.b10[0]) - bi.value;
	}

	sub.b10.erase(std::remove(sub.b10.begin(), sub.b10.end(), 0), sub.b10.end());

	return sub;
}

BigInteger BigInteger::mul(const BigInteger& bi) const
{
	BigInteger mul;

	uint iterA = b10.size()+1,  iterB = bi.b10.size()+1;
	// <pow, val>
	std::map<uint, uint> sum;

	for (uint a=0; a<iterA; a++){
		uint32_t va = (a == 0 ? value : b10[a-1]);
		for (uint b=0; b<iterB; b++){
			uint32_t vb = (b == 0 ? bi.value : bi.b10[b-1]);
			uint32_t result, carry = 0;
			result = multiply(va, vb, &carry);

			uint32_t ocarry = carry;
			
			if (result > MAX_B10P9){
				uint32_t result_carry = (result/B10P9);
				result -= (result_carry*B10P9);
				carry += result_carry;
			}
			
			// to convert the result from 2^32 to 10^9
			for (uint32_t i=0; i<ocarry; i++){
				result += (UINT32_MAX - (uint32_t(4)*B10P9))+1;
				carry += 3;
				if (result > MAX_B10P9){
					uint32_t result_carry = (result/B10P9);
					result -= (result_carry*B10P9);
					carry++;
				}
			}

			sum[a+b] += result;
			if ( sum[a+b] > MAX_B10P9){
				sum[a+b] -= B10P9;
				carry++;
			}

			if (carry > 0){
				sum[a+b+1] += carry;
				if ( sum[a+b+1] > MAX_B10P9){
					sum[a+b+1] -= B10P9;
					sum[a+b+2] += 1;
				}
			}
		}
	}

	for (uint i=0; i<sum.size(); i++){
		if (i == 0){
			mul.value = sum[i];
		} else {
			mul.b10.emplace_back(sum[i]);
		}
	}

    
	return mul;
}

