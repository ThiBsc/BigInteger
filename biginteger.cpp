#include "header/biginteger.h"

BigInteger::BigInteger()
	: value(0)
	, isSigned(false)
{
    
}

BigInteger::BigInteger(int32_t value)
    : value(value)
	, isSigned(value < 0)
{
	if ( this->value > 999999999){
		this->value -= 1000000000;

		if (this->b10.empty()){
			this->b10.emplace_back(1);
		} else {
			this->b10.back() += 1;
		}
	}
}
#include <iostream>
BigInteger::BigInteger(std::string value)
    : value(0)
	, isSigned(value.front() == '-')
{
	if (isSigned){
		value.erase(value.begin());
	}

	// Offset: How many ^9 we have
	int offset = 0;
	while (!value.empty()){
		// (10^9)-1 = "999999999" -> len = 9
		int pos = value.size() - 9;
		pos = (pos < 0 ? 0 : pos);
		std::string val = value.substr(pos);
		value.erase(pos);

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

BigInteger BigInteger::addition(const BigInteger& bi) const
{
	BigInteger add;

	add.value = (value + bi.value);
	add.b10 = b10;

	if ( add.value > 999999999){
		add.value -= 1000000000;

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

		if ( (*it) > 999999999){
			(*it) -= 1000000000;

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

BigInteger BigInteger::substract(const BigInteger& bi) const
{
	BigInteger sub;

	sub.value = value;
	sub.b10 = b10;

	std::vector<uint32_t> subDOWN = bi.b10;

	// sub > bi, (easier to compute)
	int offset = subDOWN.size()-1;

	for (int o=offset; o>=0; o--){
		
		//std::cout << "offset " << offset << " value " << sub.b10[o] << " | " << subDOWN[o] << std::endl;
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

BigInteger BigInteger::multiply(const BigInteger& bi) const
{
	
}
