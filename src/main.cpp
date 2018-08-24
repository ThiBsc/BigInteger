#include <iostream>
#include <cassert>
#include "header/biginteger.h"

using namespace std;

int main(int argc, char const *argv[])
{
    // Samples
    BigInteger a("12"), b("13");
    
    cout << a << "+" << b << " = " << a.add(b) << endl;
    cout << a << "-" << b << " = " << a.substract(b) << endl;
    cout << a << "*" << b << " = " << a.multiply(b) << endl;
    cout << a << "<" << b << " = " << (a<b) << endl;
    cout << a << ">" << b << " = " << (a>b) << endl;
    cout << a << "=" << b << " : " << (a==b) << endl;

    // More
    assert(BigInteger("-2").add(BigInteger("3")) == BigInteger("1")); // (-2)+(3)
    assert(BigInteger("10").substract(BigInteger("-3")) == BigInteger("13")); // (10)-(-3)
    assert(BigInteger("123").multiply(BigInteger("456")) == BigInteger("56088")); // (123)*(456)
    assert(BigInteger("-123").multiply(BigInteger("456")) == BigInteger("-56088")); // (-123)*(456)

    return 0;
}
