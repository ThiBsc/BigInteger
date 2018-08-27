#include "header/biginteger.h"

BigInteger::BigInteger()
    : m_radix(10)
    , m_signed(false)
    , m_value("0")
{
    
}

BigInteger::BigInteger(std::string value, int radix)
    : m_radix(radix)
    , m_signed(false)
{
    if (value.front() == '-'){
        m_signed = true;
        value.erase(0, 1);
    }
    if (radix == 10){
        m_value = value;
    } else {
        // convert to base 10 to use trivial algorithm
        // ...
        // m_value(converted_value);
    }
}

BigInteger::~BigInteger()
{

}

BigInteger BigInteger::add(const BigInteger& bi) const
{
    BigInteger addition;
    if (this->m_signed && !bi.m_signed){
        // (-a)+(+b)
        addition = bi.substract(negate());
    } else if (!this->m_signed && bi.m_signed){
        // (+a)+(-b)
        addition = substract(bi.negate());
    } else {
        // (+a)+(+b) or (-a)+(-b)
        std::string sum = this->m_value;
        std::string added = bi.m_value;
        int diffLength = std::abs(int(sum.length() - added.length()));
        if (sum.length() > added.length()){
            added.insert(0, diffLength, '0');
        } else {
            sum.insert(0, diffLength, '0');
        }
        std::reverse(sum.begin(), sum.end());
        std::reverse(added.begin(), added.end());
        char carry = '0';

        int index = 0;
        for (char& c : sum){
            c = (carry-'0') + (c-'0') + (added.at(index)-'0') + '0';
            if (c > '9'){
                c -= 10;
                carry = '1';
            } else {
                carry = '0';
            }
            index++;
        }
        if (carry > '0'){
            sum.append(1, carry);
        }
        std::reverse(sum.begin(), sum.end());
        addition = (this->m_signed ? BigInteger(sum).negate() : BigInteger(sum));
    }
    return addition;
}

BigInteger BigInteger::substract(const BigInteger& bi) const
{
    BigInteger substraction;
    if (this->m_signed && !bi.m_signed){
        // (-a)-(+b)
        substraction = add(bi.negate());
    } else if (!this->m_signed && bi.m_signed){
        // (+a)-(-b)
        substraction = add(bi.negate());
    } else {
        // (+a)-(+b) or (-a)-(-b)
        if (this->m_signed){
            substraction = add(bi.negate());
        } else {
            std::string sub;
            std::string removed;
            bool invert_sign = false;
            if (compare(bi) == -1){
                sub = bi.m_value;
                removed = this->m_value;
                invert_sign = true;
            } else {
                sub = this->m_value;
                removed = bi.m_value;
            }
            int diffLength = std::abs(int(sub.length() - removed.length()));
            if (sub.size() > removed.size()){
                removed.insert(0, diffLength, '0');
            } else {
                sub.insert(0, diffLength, '0');
            }
            std::reverse(sub.begin(), sub.end());
            std::reverse(removed.begin(), removed.end());

            int index = 0;
            for (char& c : sub){
                if (c < removed.at(index)){
                    c += 10;
                    sub[index+1]--;
                }
                c = (c-'0') - (removed.at(index)-'0') + '0';
                index++;
            }
            std::reverse(sub.begin(), sub.end());
            while (sub.front()=='0' && sub.length()!=1){
                sub.erase(0, 1);
            }
            substraction = (invert_sign ? BigInteger(sub).negate() : BigInteger(sub));
        }
    }    
    return substraction;
}

BigInteger BigInteger::multiply(const BigInteger& bi) const
{
    BigInteger multiplication;

    std::string mul = this->m_value;
    std::string multiplied = bi.m_value;
    std::reverse(mul.begin(), mul.end());
    std::reverse(multiplied.begin(), multiplied.end());
    int step = 0;
    char carry = '0';
    for (const char& c1 : mul){
        std::string cur_op;
        cur_op.insert(0, step, '0');
        for (const char& c2 : multiplied){
            unsigned char val = ((c1-'0') * (c2-'0')) + (carry-'0') + '0';
            carry = '0';
            if (val > '9'){
                while (val > '9'){
                    val -= 10;
                    carry++;
                }
            }
            cur_op.insert(0, 1, val);
        }
        if (carry > '0'){
            cur_op.insert(0, 1, carry);
            carry = '0';
        }
        multiplication += BigInteger(cur_op);
        step++;
    }
    bool positive = (this->m_signed && bi.m_signed) || (!this->m_signed && !bi.m_signed);
    if (!positive){
        multiplication = multiplication.negate();
    }

    return multiplication;
}

BigInteger BigInteger::divide(const BigInteger& bi) const
{
    return BigInteger("0");
}

BigInteger BigInteger::pow(const BigInteger& bi) const
{
    return BigInteger("0");
}

BigInteger BigInteger::modulus(const BigInteger& bi) const
{
    return BigInteger("0");
}

int BigInteger::compare(const BigInteger& bi) const
{
    int comparison;
    if (this->m_signed && !bi.m_signed){
        // -a, +b
        comparison = -1;
    } else if (!this->m_signed && bi.m_signed){
        // +a, -b
        comparison = 1;
    } else {
        // +a, +b or -a, -b
        if (this->m_value.length() < bi.m_value.length()){
            comparison = -1;
        } else if (this->m_value.length() > bi.m_value.length()){
            comparison = 1;
        } else {
            bool positive = !this->m_signed;
            if (this->m_value < bi.m_value){
                comparison = (positive ? -1 : 1);
            } else if (this->m_value > bi.m_value){
                comparison = (positive ? 1 : -1);;
            } else {
                comparison = 0;
            }
        }
    }
    return comparison;
}

BigInteger BigInteger::negate() const
{
    std::string value = this->m_value;
    return BigInteger((this->m_signed ? value : value.insert(0, 1, '-')));
}

void BigInteger::swap(BigInteger &bi)
{
	BigInteger tmp = (*this);
	(*this) = bi;
	bi = tmp;
}

BigInteger BigInteger::operator+(const BigInteger& bi)
{
    return this->add(bi);
}

BigInteger BigInteger::operator-(const BigInteger& bi)
{
    return this->substract(bi);
}

BigInteger BigInteger::operator*(const BigInteger& bi)
{
    return this->multiply(bi);
}

BigInteger& BigInteger::operator+=(const BigInteger& bi)
{
    (*this) = add(bi);
    return (*this);
}

BigInteger& BigInteger::operator-=(const BigInteger& bi)
{
    (*this) = substract(bi);
    return (*this);
}

BigInteger& BigInteger::operator*=(const BigInteger& bi)
{
    (*this) = multiply(bi);
    return (*this);
}

bool BigInteger::operator==(const BigInteger& bi)
{
    bool equal = (compare(bi) == 0);
    return equal;
}

bool BigInteger::operator<(const BigInteger& bi)
{
    bool less = (compare(bi) == -1);
    return less;
}

bool BigInteger::operator>(const BigInteger& bi)
{
    bool more = (compare(bi) == 1);
    return more;
}

bool BigInteger::operator<=(const BigInteger& bi)
{
    int cmp = compare(bi);
    return (cmp == -1) || (cmp && 0);
}

bool BigInteger::operator>=(const BigInteger& bi)
{
    int cmp = compare(bi);
    return (cmp == 0) || (cmp && 1);
}

std::string BigInteger::toString() const
{
    std::stringstream ss;
    if (m_signed){
        ss << '-';
    }
    ss << m_value;
    return ss.str();
}
